/** ==================================================================
 * pic_frame_motion_depth.hpp
 * Class for finding the video frame areas with changing intensity
 **/
#include "pic_frame_motion_depth.hpp"

 /*ci
  * \brief picFrameMotion class constructor
  *
  * \details
  * Instantiate and init the class
  *
  * \param[in]    res_x         frame pixel count in X
  * \param[in]    res_y         frame pixel count in Y
  */
picFrameMotion::picFrameMotion(int16_t res_x, int16_t res_y)
{
    // allocate and init the data arrays based on the XY size
    frame_x = res_x;
    frame_y = res_y;
    grids_x = res_x / 10;
    grids_y = res_y / 10;
    lfsr = 0x8675309e;
    co_now = 1;
    co_roll = 19;
    frame_int_average = new uint32_t[(grids_x * grids_y)];
    rolling_int_average = new uint32_t[(grids_x * grids_y)]();
    new_frame_delta = new uint32_t[(grids_x * grids_y)];
}

void picFrameMotion::FrameProcess(cv::Mat frame)
{
    // calc the frame average intensities (by 10x10 pixel grid)
    int fIdx = 0;
    for (int y = 0; y < frame_y; y+=10) {
        for (int x = 0; x < frame_x ; x+=10) {
            // sum the pixels in each grid
            cv::Mat subGrid = frame(cv::Range(y, y+9), cv::Range(x, x+9));
            cv::Scalar gridSum = cv::mean(subGrid);
            frame_int_average[fIdx] = (uint32_t)(gridSum[0] + gridSum[1] + gridSum[2]);
            fIdx++;
        }
    }
#if 1
    // calc the abs diff between this frame's grid intensities, and the rolling average
    for (int i = 0; i < (grids_x * grids_y); i++) {
        new_frame_delta[i] = abs((int)frame_int_average[i] - (int)rolling_int_average[i]);
        //printf("%2x ", new_frame_delta[i]);
        if ((i % grids_x) == 0) {
            //printf("\n");
        }
    }
    //printf("-----\n");
#endif

    // sum this frame's intensities into the rolling average
    for (int i = 0; i < (grids_x * grids_y); i++) {
        rolling_int_average[i] = ((rolling_int_average[i] * co_roll) + (frame_int_average[i] * co_now)) / (co_roll + co_now);
    }
    return;
}

float picFrameMotion::getPointDepth(int16_t x, int16_t y)
{
    int fsel = (x / 10) + ((y / 10) * grids_x);
    uint32_t fdelta = new_frame_delta[fsel];
    //return ((((float)fdelta) / 76.5f) - 5.0f);
    return ((((float)fdelta) / 36.5f) - 5.0f);
}


// destructor
picFrameMotion::~picFrameMotion() {}
