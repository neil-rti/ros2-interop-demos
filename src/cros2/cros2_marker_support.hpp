/** ==================================================================
 * cros2_marker_support.hpp
 * Class for interfacing a native Connext DDS application with the 
 *  ROS 2 visualization_msgs::msg::dds_::Marker_ data type.
 * This program uses the C++11 option of RTIDDSGen, using the type
 *  support source code generated by the command line:
 *   rtiddsgen -language C++11 <arch> cros2_types.idl
 **/

#ifndef __CROS2_MARKER_SUPPORT_HPP__
#define __CROS2_MARKER_SUPPORT_HPP__
#include "cros2_common.hpp"             // common includes and defs
#include "visualization_msgs/msg/MarkerPlugin.hpp"

/** ----------------------------------------------------------------
 * cros2marker class
 * This class supports ROS2 marker
 * ------------------------------------------------------------- **/
class cros2marker
{
public:
    cros2marker(const std::string markerName, uint32_t opt_en, dds::domain::DomainParticipant participant,
        int(*rcv_fptr)(dds::sub::DataReader<visualization_msgs::msg::dds_::Marker_>) = NULL);
    ~cros2marker();

    void publish(void);
    visualization_msgs::msg::dds_::Marker_ *sample_to_pub(void) { return &pub_sample; }

    // marker data sample accessors
    void pub_sample_header_tstamp_set(int32_t newSec, uint32_t newNanosec) { 
        pub_sample.header().stamp().sec(newSec); 
        pub_sample.header().stamp().nanosec(newNanosec);
    }
    void pub_sample_header_frameid_set(const std::string newId) { pub_sample.header().frame_id(newId); }
    void pub_sample_pose_position_set(float x, float y, float z) {
        pub_sample.pose().position().x(x);
        pub_sample.pose().position().y(y);
        pub_sample.pose().position().z(z);
    }
    void pub_sample_pose_orientation_set(float x, float y, float z, float w) {
        pub_sample.pose().orientation().x(x);
        pub_sample.pose().orientation().y(y);
        pub_sample.pose().orientation().z(z);
        pub_sample.pose().orientation().w(w);
    }
    void pub_sample_ns_set(const std::string newNs) { pub_sample.ns(newNs); }
    void pub_sample_id_set(int32_t newId) { pub_sample.id(newId); }
    void pub_sample_type_set(int32_t newType) { pub_sample.type(newType); }
    void pub_sample_action_set(int32_t newAction) { pub_sample.action(newAction); }
    void pub_sample_scale_set(double x, double y, double z) { 
        pub_sample.scale().x(x);
        pub_sample.scale().y(y);
        pub_sample.scale().z(z);
    }
    void pub_sample_color_set(float r, float g, float b, float a) {
        pub_sample.color().r(r);
        pub_sample.color().g(g);
        pub_sample.color().b(b);
        pub_sample.color().a(a);
    }
    void pub_sample_lifetime_set(int32_t sec, uint32_t nsec) {
        pub_sample.lifetime().sec(sec);
        pub_sample.lifetime().nanosec(nsec);
    }
    void pub_sample_frame_locked_set(bool toLock) { pub_sample.frame_locked(toLock); }
    void pub_sample_text_set(const std::string newText) { pub_sample.text(newText); }
    void pub_sample_mesh_resource_set(const std::string newMesh) { pub_sample.mesh_resource(newMesh); }
    void pub_sample_mesh_use_embedded_materials_set(bool toUse) { pub_sample.mesh_use_embedded_materials(toUse); }

    geometry_msgs::msg::dds_::Point_ *pub_sample_points_get_ptr(void) { return pub_sample.points().data(); }
    std_msgs::msg::dds_::ColorRGBA_ *pub_sample_colors_get_ptr(void) { return pub_sample.colors().data(); }

    int data_rcv_count_get(void) { return data_rcv_count; }

private:
    // DDS receive data handler
    int rcv_dataProc(dds::sub::DataReader<visualization_msgs::msg::dds_::Marker_> & reader);

    // DDS Topic, DataWriter, DataReader, Sample(for publish)
    dds::topic::Topic<visualization_msgs::msg::dds_::Marker_> data_topic;
    dds::pub::DataWriter<visualization_msgs::msg::dds_::Marker_> data_wr;
    dds::sub::DataReader<visualization_msgs::msg::dds_::Marker_> data_rd;
    visualization_msgs::msg::dds_::Marker_ pub_sample;

    // misc
    dds::core::cond::WaitSet waitset;
    int data_rcv_count;
};
#endif  // ndef __CROS2_MARKER_SUPPORT_HPP__