//
// Created by Marc Haubenstock on 2019-07-22.
//

#ifndef VISUAL_ODOMETRY_LAYER_H
#define VISUAL_ODOMETRY_LAYER_H

#include <image.h>

namespace layer {

    struct Layer {
        Image intensity;
        Image gradient_x;
        Image gradient_y;
        int8_t layer_index;
    };

}



#endif //VISUAL_ODOMETRY_LAYER_H
