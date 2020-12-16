/** ==================================================================
 * cros2_illuminance_support.hpp
 * Class for interfacing a native Connext DDS application with the 
 *  ROS 2 sensor_msgs::msg::dds_::illuminance_ data type.
 * This program uses the C++11 option of RTIDDSGen, using the type
 *  support source code generated by the command line:
 *   rtiddsgen -language C++11 <arch> cros2_types.idl
 **/

#ifndef __CROS2_ILLUMINANCE_SUPPORT_HPP__
#define __CROS2_ILLUMINANCE_SUPPORT_HPP__
#include "cros2_common.hpp"             // common includes and defs
#include "sensor_msgs/msg/IlluminancePlugin.hpp"

/** ----------------------------------------------------------------
 * cros2illuminance class
 * This class supports ROS2 illuminance
 * ------------------------------------------------------------- **/
class cros2illuminance
{
public:
    cros2illuminance(const std::string illuminanceName, uint32_t opt_en, dds::domain::DomainParticipant participant,
        int(*rcv_fptr)(dds::sub::DataReader<sensor_msgs::msg::dds_::Illuminance_>) = NULL);
    ~cros2illuminance();


    void publish(void);
    sensor_msgs::msg::dds_::Illuminance_ *pub_sample_get_ptr(void) { return &pub_sample; }

    // illuminance data sample accessors
    void pub_sample_header_tstamp_set(int32_t newSec, uint32_t newNanosec) { 
        pub_sample.header().stamp().sec(newSec); 
        pub_sample.header().stamp().nanosec(newNanosec);
    }
    void pub_sample_header_frameid_set(const std::string newId) { pub_sample.header().frame_id(newId); }
    void pub_sample_illuminance_set(double newIlluminance) { pub_sample.illuminance(newIlluminance); }
    void pub_sample_variance_set(double newVariance) { pub_sample.variance(newVariance); }
    int data_rcv_count_get(void) { return data_rcv_count; }

private:
    // DDS receive data handler
    int rcv_dataProc(dds::sub::DataReader<sensor_msgs::msg::dds_::Illuminance_> & reader);

    // DDS Topic, DataWriter, DataReader, Sample(for publish)
    dds::topic::Topic<sensor_msgs::msg::dds_::Illuminance_> data_topic;
    dds::pub::DataWriter<sensor_msgs::msg::dds_::Illuminance_> data_wr;
    dds::sub::DataReader<sensor_msgs::msg::dds_::Illuminance_> data_rd;
    sensor_msgs::msg::dds_::Illuminance_ pub_sample;

    // misc
    dds::core::cond::WaitSet waitset;
    int data_rcv_count;
};
#endif  // ndef __CROS2_ILLUMINANCE_SUPPORT_HPP__