//
// Created by Marc Haubenstock on 2019-07-22.
//

#ifndef VISUAL_ODOMETRY_FRAME_H
#define VISUAL_ODOMETRY_FRAME_H

#include <image.h>
#include <types.h>
#include <vector>
#include <string>
#include "layer.h"

using namespace std;

namespace frame {

    struct Frame {
        vector<layer::Layer> intensity;
        Image depth;
    };

    struct Loaded_Frames{
        vector<Frame> reference_frames;
        vector<Frame> target_frames;
        vector<image_data> max_depths;
    };

    Loaded_Frames load_frames(const vector<string>& reference_image_paths,
                              const vector<string>& reference_depth_paths,
                              const vector<string>& target_image_paths,
                              const vector<string>& target_depth_paths,
                              image_data depth_factor,
                              float direction,
                              ImageFilter filter_x,
                              ImageFilter filter_y,
                              bool standardize,
                              uint8_t pyramid_levels,
                              float sigma);

}

#endif //VISUAL_ODOMETRY_FRAME_H
