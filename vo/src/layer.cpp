//
// Created by Marc Haubenstock on 2019-07-22.
//

#include "layer.h"



layer::Layer layer::from_image(const CImg<image_data>& c_image, uint8_t layer, bool standardize, ImageFilter filter_x,
                               ImageFilter filter_y) {

    //TODO: @Perf - We standardize the same image multiple times
    auto gx = Image::from_CImg(standardize, filter_x, c_image);
    auto gy = Image::from_CImg(standardize, filter_y, c_image);
    auto image = Image::from_CImg(standardize, ImageFilter::NoFilter, c_image);
    layer::Layer new_layer{
        image,
        gx,
        gy,
        layer
    };

    return new_layer;
}

layer::Depth_Coordiantes layer::generate_depth_coordinates(uint8_t layer_index, int x, int y) {

    int new_x = 0;
    int new_y = 0;

    //TODO

    layer::Depth_Coordiantes depth_coordiantes {
        new_x,
        new_y
    };

    return depth_coordiantes;
}
