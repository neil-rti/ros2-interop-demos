/** ==================================================================
 * cros2_image_support.hpp
 * Class for interfacing a native Connext DDS application with the 
 *  ROS 2 sensor_msgs::msg::dds_::Image_ data type.
 * This program uses the C++11 option of RTIDDSGen, using the type
 *  support source code generated by the command line:
 *   rtiddsgen -language C++11 cros2_types.idl
 **/

#ifndef __CROS2_IMAGE_SUPPORT_HPP__
#define __CROS2_IMAGE_SUPPORT_HPP__
#include "cros2_common.hpp"             // common includes and defs
#include "sensor_msgs/msg/ImagePlugin.hpp"

/** ----------------------------------------------------------------
 * cros2image class
 * This class supports ROS2 turtlesim with methods that are not 
 *  tied to a specific turtle:
 *  Spawn, Kill, Clear, Reset, Parameters and Logging
 * See 'turtleinst' class for specific-turtle methods.
 * ------------------------------------------------------------- **/
class cros2image
{
public:
    cros2image(const std::string imageName, uint32_t opt_en, dds::domain::DomainParticipant participant,
        int(*rcv_fptr)(dds::sub::DataReader<sensor_msgs::msg::dds_::Image_>) = NULL);
    ~cros2image();

    void publish(void);
    sensor_msgs::msg::dds_::Image_ *sample_to_pub(void) { return &pub_sample; }
    uint8_t *getDataPtr(void) { return pub_sample.data().data(); }
    void publish_scaled(uint8_t *imgBuf, uint32_t xRes, uint32_t yRes);

    // DDS pub sample element access
    void pub_sample_size_xy_set(uint32_t newX, uint32_t newY) {
        pub_sample.width(newX);
        pub_sample.height(newY);
        pub_sample.step(3 * newX);
        pub_sample.data().resize(newX * newY * 3);
    }
    void pub_sample_encoding_set(const std::string newEnc) { pub_sample.encoding(newEnc); }
    void pub_sample_isbigendian_set(bool isBig) { pub_sample.is_bigendian(isBig); }
    void pub_sample_header_frameid_set(const std::string newId) { pub_sample.header().frame_id(newId); }

    uint32_t pub_sample_width_get(void) { return pub_sample.width(); }
    uint32_t pub_sample_height_get(void) { return pub_sample.height(); }
    int data_rcv_count_get(void) { return data_rcv_count; }

private:

    // DDS Topic, DataWriter, DataReader, Data handler, and pub sample
    dds::topic::Topic<sensor_msgs::msg::dds_::Image_> data_topic;
    dds::pub::DataWriter<sensor_msgs::msg::dds_::Image_> data_wr;
    dds::sub::DataReader<sensor_msgs::msg::dds_::Image_> data_rd;
    int rcv_dataProc(dds::sub::DataReader<sensor_msgs::msg::dds_::Image_> & reader);
    sensor_msgs::msg::dds_::Image_ pub_sample;

    // misc
    dds::core::cond::WaitSet waitset;
    int data_rcv_count;
};
#endif  // ndef __CROS2_IMAGE_SUPPORT_HPP__