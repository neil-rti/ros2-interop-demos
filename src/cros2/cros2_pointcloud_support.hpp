/** ==================================================================
 * cros2_pointcloud_support.hpp
 * Class for interfacing a native Connext DDS application with the 
 *  ROS 2 sensor_msgs::msg::dds_::PointCloud2_ data type.
 * This program uses the C++11 option of RTIDDSGen, using the type
 *  support source code generated by the command line:
 *   rtiddsgen -language C++11 <arch> cros2_types.idl
 **/

#ifndef __CROS2_POINTCLOUD_SUPPORT_HPP__
#define __CROS2_POINTCLOUD_SUPPORT_HPP__
#include "cros2_common.hpp"             // common includes and defs
#include "sensor_msgs/msg/PointCloud2Plugin.hpp"

// enum of data format types
enum ptc2_data_fmt {
    PTCLOUD2_FMT_XYZ_RGB8_FLOAT32 = 0,
    PTCLOUD2_FMT_UNDEF
};

/** ----------------------------------------------------------------
 * cros2pointcloud class
 * This class supports ROS2 PointCloud2 data type
 * ------------------------------------------------------------- **/
class cros2pointcloud
{
public:
    cros2pointcloud(const std::string cloudName, uint32_t opt_en, dds::domain::DomainParticipant participant, 
        int(*rcv_fptr)(dds::sub::DataReader<sensor_msgs::msg::dds_::PointCloud2_>) = NULL);
    ~cros2pointcloud();

    sensor_msgs::msg::dds_::PointCloud2_ *get_pub_sample(void) { return &pub_sample; }
    void publish(void);
    float *get_send_data_buffer(void) { return reinterpret_cast<float *>(pub_sample.data().data()); }
    void datarcv_waitset(int32_t secs, uint32_t nsecs) { waitset.dispatch(dds::core::Duration(secs, nsecs)); }

    // pub sample element access
    void pub_sample_config_fields(ptc2_data_fmt myFormat);
    void pub_sample_isdense_set(bool isDense) { pub_sample.is_dense(isDense); }
    void pub_sample_isbigendian_set(bool isBig) { pub_sample.is_bigendian(isBig); }
    void pub_sample_header_frameid_set(const std::string newId) { pub_sample.header().frame_id(newId); }
    void pub_sample_size_xy_set(uint32_t newX, uint32_t newY) {
        pub_sample.width(newX);
        pub_sample.height(newY);
        pub_sample.point_step(bytesPerPoint);
        pub_sample.row_step(bytesPerPoint * newX);
        pub_sample.data().resize(bytesPerPoint * newX * newY);
    }
    uint32_t pub_sample_height_get(void) { return pub_sample.height(); }
    uint32_t pub_sample_width_get(void) { return pub_sample.width(); }

    int data_rcv_count_get(void) { return data_rcv_count; }

private:
    // DDS Topic, DataWriter, DataReader, read data handler, sample
    dds::topic::Topic<sensor_msgs::msg::dds_::PointCloud2_> data_topic;
    dds::pub::DataWriter<sensor_msgs::msg::dds_::PointCloud2_> data_wr;
    dds::sub::DataReader<sensor_msgs::msg::dds_::PointCloud2_> data_rd;
    int rcv_dataProc(dds::sub::DataReader<sensor_msgs::msg::dds_::PointCloud2_> & reader);
    sensor_msgs::msg::dds_::PointCloud2_ pub_sample;

    // misc
    dds::core::cond::WaitSet waitset;
    int data_rcv_count;
    uint32_t bytesPerPoint;         // number of bytes needed per PointCloud data point.

};
#endif  // ndef __CROS2_POINTCLOUD_SUPPORT_HPP__