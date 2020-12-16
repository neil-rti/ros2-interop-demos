/** ==================================================================
 * pic_frame_motion_depth.hpp
 * Class for finding the video frame areas with changing intensity
 **/
#ifndef __PIC_FRAME_MOTION_DEPTH_HPP__
#define __PIC_FRAME_MOTION_DEPTH_HPP__
#include <opencv2/opencv.hpp>

/** ----------------------------------------------------------------
 * picFrameMotion class
 * This class keeps a rolling average of picture intensity within
 *  10x10 pixel grids, and uses these to determine where the picture
 *  content is changing from frame to frame -- 
 *  To set the depth (to indicate motion) and to direct the 
 *  randomized sampling (putting more samples in changing areas)
 * ------------------------------------------------------------- **/
class picFrameMotion
{
public:
    picFrameMotion(int16_t res_x, int16_t res_y);
    ~picFrameMotion();

    void FrameProcess(cv::Mat frame);
    float getPointDepth(int16_t x, int16_t y);

private:
    int16_t     frame_x;                // size in pixels of the frame(x)
    int16_t     frame_y;                // size in pixels of the frame(y)
    int16_t     grids_x;                // number of motion grids (x)
    int16_t     grids_y;                // number of motion grids (y)
    int32_t     co_now;                 // multiplier for the newest frame
    int32_t     co_roll;                // multiplier for the rolling average
    uint32_t    lfsr;                   // pseudorandom number
    uint32_t*   frame_int_average;      // array of 10x10 pixel grid cells for frame intensity
    uint32_t*   rolling_int_average;    // rolling average of the grid cell intensity
    uint32_t*   new_frame_delta;        // diff from new to rolling

};
#endif  // ndef __PIC_FRAME_MOTION_DEPTH_HPP__