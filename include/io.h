//
// Created by Marc Haubenstock on 2019-07-15.
//

#ifndef VISUAL_ODOMETRY_IO_H
#define VISUAL_ODOMETRY_IO_H

#include <string_view>
#include <string>
#include <sstream>
#include <vector>
#include <sys/types.h>
#include <dirent.h>
#include <iomanip>
#include <algorithm>

using namespace std;

namespace IO {

    struct loaded_images {
        vector<double> intensity_timestamps;
        vector<double> depth_timestamps;
    };

    //(intensity and depth file names)
    loaded_images generate_runtime_intensity_depth_lists(string_view intensity_folder_path, string_view depth_folder_path, string_view start_file_name, string_view extension, int step_count, int frame_count, float max_diff_milliseconds);
    vector<double> get_file_list_in_dir(string_view dir_path);
    double associate_file_name(string_view folder_path, double time_stamp, float max_diff);

}

#endif //VISUAL_ODOMETRY_IO_H
