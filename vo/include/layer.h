//
// Created by Marc Haubenstock on 2019-07-22.
//

#ifndef VISUAL_ODOMETRY_LAYER_H
#define VISUAL_ODOMETRY_LAYER_H

#include <image.h>
#include "CImg.h"

namespace layer {

    struct Layer {
        Image intensity;
        Image gradient_x;
        Image gradient_y;
        uint8_t layer_index;
    };

    struct Depth_Coordiantes {
        int x;
        int y;
    };

    Layer from_image(const CImg<image_data>& image, uint8_t layer, bool standardize, ImageFilter filter_x, ImageFilter filter_y);
    Depth_Coordiantes generate_depth_coordinates(uint8_t layer_index, int x, int y);
}



#endif //VISUAL_ODOMETRY_LAYER_H
