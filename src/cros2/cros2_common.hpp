/** ==================================================================
 * cros2_common.hpp
 * Common types and defs for Connext/ROS2 interface classes
 **/

#ifndef __CROS2_COMMON_HPP__
#define __CROS2_COMMON_HPP__
#include <dds/pub/ddspub.hpp>
#include <dds/sub/ddssub.hpp>
#include <dds/core/ddscore.hpp>
#include <dds/domain/ddsdomain.hpp>     // for sub to ignore pubs from same participant
#include <rti/util/util.hpp>            // for sleep()


// bitfield enumeration to enable components of image
enum cros2_comp_enable {
    CROS2_PUB_ON,
    CROS2_SUB_ON
};

// prototypes
void tstamp_get(timespec *tStamp);

#endif  // ndef __CROS2_COMMON_HPP__
