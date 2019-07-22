#include <iostream>
#include <string>
#include <sstream>
#include <string_view>
#include "image.h"
#include "io.h"
#include "CImg.h"
#include "layer.h"

using namespace cimg_library;

constexpr std::string_view get_data_path() {return "/Users/marchaubenstock/Workspace/C++/ImageLib/data/";}
constexpr std::string_view get_external_data_path() {return "/Volumes/Sandisk/Diplomarbeit_Resources/VO_Bench/rgbd_dataset_freiburg1_desk2/";}

int image(){

    std::string lena = "lena.png";
    std::string depth = "depth.png";

    std::stringstream ss_lena;
    ss_lena << get_data_path() << lena;
    auto image_path_lena = ss_lena.str();
    auto image_path_lena_c_str = image_path_lena.c_str();

    std::stringstream ss_depth;
    ss_depth << get_data_path() << depth;
    auto image_path_depth = ss_depth.str();
    auto image_path_depth_c_str = image_path_depth.c_str();

    CImg<unsigned char> image(image_path_lena_c_str);
    CImg<short> image_depth(image_path_depth_c_str);
    CImg<unsigned char> gray = Image::CImg_RGB_to_Gray(0.33, 0.33, 0.33, image);

    auto my_image = Image::from_CImg(true,ImageFilter::SobelY, gray);
    auto my_depth_image = Image::from_CImg(true,ImageFilter::NoFilter, image_depth);

    auto disp_image = Image::to_CImg_U8(my_image);
    auto disp_depth_image = Image::to_CImg_U8(my_depth_image);

    CImgDisplay main_disp(image_depth,"Original"),draw_disp(disp_depth_image,"Converted");


    while (!main_disp.is_closed() && !draw_disp.is_closed()) {
        main_disp.wait();
    }

    return EXIT_SUCCESS;

}

int files(){
    auto path = get_external_data_path();
    std::stringstream image_ss;
    std::stringstream depth_ss;
    image_ss << path << "rgb/";
    depth_ss << path << "depth/";
    auto intenstiy_folder_path = image_ss.str();
    auto depth_folder_path = depth_ss.str();

    try {
        //auto files = IO::get_file_list_in_dir(intenstiy_folder_path, "png");
        auto res = IO::generate_runtime_intensity_depth_lists(intenstiy_folder_path, depth_folder_path, "1305031526.671473", "png", 1, 2, 0.03);

        return EXIT_SUCCESS;
    }
    catch(const std::runtime_error& e) {
        std::cerr << e.what();
        return EXIT_FAILURE;
    }

}

int main() {
    //return files();
    return image();
}

