//
// Created by Marc Haubenstock on 2019-07-15.
//

#include "io.h"

namespace {
    // Apple prefixes files with "._" on non-APFS
    bool is_valid_file_MACOS(string_view file_name) {
        auto has_invalid_prefix = file_name[0] == '.';
        return !has_invalid_prefix;
    }

    string float_to_str_with_precision(float value, int precision){
        stringstream ss;
        ss << fixed << setprecision(precision) << value;
        return ss.str();
    }

    // from_chars for float does not work on macOS
    double str_to_double(const string& string){
        return stod(string, nullptr);
    }
}

IO::loaded_images IO::generate_runtime_intensity_depth_lists(string_view intensity_folder_path, string_view depth_folder_path,
                                                             string_view start_file_name, string_view extension, int step_count,
                                                             int frame_count, float max_diff_milliseconds) {
    assert(frame_count%step_count == 0);

    if(extension[0] == '.'){
        stringstream err_msg;
        err_msg << "Give image extensions without the '.' character i.e. png, jpg";
        throw runtime_error(err_msg.str());
    }

    auto size = frame_count/step_count;
    double start_timestamp = str_to_double(start_file_name.data());
    loaded_images result;
    result.intensity_timestamps.reserve(size);
    result.depth_timestamps.reserve(size);

    auto intensity_file_timestamps = get_file_list_in_dir(intensity_folder_path, extension);
    auto depth_file_timestamps = get_file_list_in_dir(depth_folder_path, extension);

    sort(intensity_file_timestamps.begin(), intensity_file_timestamps.end());
    sort(depth_file_timestamps.begin(), depth_file_timestamps.end());

    // find index of start_file_name
    int start_idx = -1;
    for(int i = 0; i < intensity_file_timestamps.size(); i++){
        auto val = intensity_file_timestamps[i];
        if(val == start_timestamp){
            start_idx = i;
            break;
        }
    }

    if(start_idx == -1){
        stringstream err_msg;
        err_msg << "Could not find: " << start_file_name;
        throw runtime_error(err_msg.str());
    }

    // populate result with relevant timestamp subset
    for(int i = start_idx; i < size; i++)
        result.intensity_timestamps.emplace_back(intensity_file_timestamps[i]);

    // find matching depth timestamps
    for(auto const& ts: result.intensity_timestamps){
        double depth_ts = associate_file_name(depth_file_timestamps, ts, max_diff_milliseconds);
        if(depth_ts == -1){
            stringstream err_msg;
            err_msg << "Could not find a matching depth timestamp for : " << ts;
            throw runtime_error(err_msg.str());
        }
        result.depth_timestamps.emplace_back(depth_ts);
    }


    return result;
}

vector<double> IO::get_file_list_in_dir(string_view dir_path, string_view extension) {
    vector<double> files;
    stringstream err_msg;
    // +1 for the '.' character
    int extension_length = extension.length() + 1;

    #if defined(__APPLE__) || defined(__linux__)
        // http://www.martinbroadhurst.com/list-the-files-in-a-directory-in-c.html
        // Only for for POSIX systems
        DIR* dirp = opendir(dir_path.data());
        if(dirp != nullptr) {
            struct dirent * dp;
            while ((dp = readdir(dirp)) != nullptr) {
                auto file_name = dp->d_name;
                if (dp->d_type == DT_REG && is_valid_file_MACOS(file_name)){
                    string name = string(file_name);
                    auto length_without_extension =  name.size() - extension_length;
                    files.emplace_back(str_to_double(name.substr(0,length_without_extension)));
                }
            }
            closedir(dirp);
        }
        else {
            err_msg << "Could not open directory: " << dir_path;
            throw runtime_error(err_msg.str());
        }
    #endif

    #if defined(_WIN64)
        err_msg << "IO::get_file_list_in_dir(..) not implemented for windows backend";
        throw runtime_error(err_msg.str());
    #endif


    return files;
}

double IO::associate_file_name(const vector<double>& depth_timestamps, double time_stamp, float max_diff) {
    double prev_diff = 100.0;
    double best_match = -1.0;

    for(auto const& depth_ts: depth_timestamps){
        auto diff = fabs(depth_ts - time_stamp);
        if(diff < prev_diff){
            prev_diff = diff;
            best_match = depth_ts;
        }
        else{
            break;
        }
    }

    auto result = prev_diff <= max_diff ? best_match : -1.0;
    return result;
}
