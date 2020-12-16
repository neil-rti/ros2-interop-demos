cmake_minimum_required(VERSION 3.3.2)
project (ros2_interop_demos)

if(DEFINED ENV{NDDSHOME})
  set(NDDSHOME $ENV{NDDSHOME})
else()
  message(FATAL_ERROR "NDDSHOME (env var) is not set")
endif()

if(DEFINED ENV{ROS_DATA_TYPES_DIR})
  set(ROS_DATA_TYPES_DIR $ENV{ROS_DATA_TYPES_DIR})
else()
  message(FATAL_ERROR "ROS_DATA_TYPES_DIR (env var) is not set")
endif()

set(CMAKE_MODULE_PATH ${NDDSHOME}/resource/cmake)

find_package(RTIConnextDDS EXACT "6.0.1" REQUIRED)

# for the OpenCV demo
#find_package( OpenCV REQUIRED )
#include_directories( ${OpenCV_INCLUDE_DIRS} )

find_library(ROS_IDL_LIBRARY NAMES RosDataTypes HINTS "${ROS_DATA_TYPES_DIR}/build")

# - Point to the source dirs and files ----------
include_directories(
    "src/cros2" 
    ${ROS_DATA_TYPES_DIR}/build 
    ${CONNEXTDDS_INCLUDE_DIRS}
)

# - Executables to build -----------------------------------------------------
add_executable(rviz_all 
    src/demos/rviz_all/rviz_all_demo.cxx 
	src/cros2/cros2_pointcloud_support.cxx 
	src/cros2/cros2_occupancygrid_support.cxx
	src/cros2/cros2_image_support.cxx
	src/cros2/cros2_posestamped_support.cxx
	src/cros2/cros2_posearray_support.cxx
	src/cros2/cros2_marker_support.cxx
	src/cros2/cros2_markerarray_support.cxx
	src/cros2/cros2_odometry_support.cxx
	src/cros2/cros2_path_support.cxx
	src/cros2/cros2_gridcells_support.cxx
	src/cros2/cros2_fluidpressure_support.cxx
	src/cros2/cros2_illuminance_support.cxx
	src/cros2/cros2_temperature_support.cxx
	src/cros2/cros2_relativehumidity_support.cxx
	src/cros2/cros2_polygonstamped_support.cxx
	src/cros2/cros2_common.cxx
)
target_link_libraries(rviz_all PUBLIC RTIConnextDDS::cpp2_api ${ROS_IDL_LIBRARY})

add_executable(bmp_view 
  	src/demos/bmp_view/bmp_view_demo.cxx 
	src/cros2/cros2_pointcloud_support.cxx 
	src/cros2/cros2_occupancygrid_support.cxx
	src/cros2/cros2_image_support.cxx
	src/cros2/cros2_common.cxx
)
target_link_libraries(bmp_view PUBLIC RTIConnextDDS::cpp2_api ${ROS_IDL_LIBRARY})

add_executable(turtle_shapes 
  	src/demos/turtleshapes/turtle_shapes.cxx 
	src/cros2/cros2_turtlesim_support.cxx 
	src/shapes/shapesdemo_support.cxx
  	src/typesupport/ShapeType.cxx 
  	src/typesupport/ShapeTypePlugin.cxx 
	src/cros2/cros2_common.cxx
)
target_include_directories(turtle_shapes PUBLIC src/shapes src/typesupport)
target_link_libraries(turtle_shapes PUBLIC RTIConnextDDS::cpp2_api ${ROS_IDL_LIBRARY})

# wrap_bench is a latency testing app for wrap_app or ROS2 equivalent
add_executable(wrap_bench
  	src/demos/bench/tester/wrap_bench_main.cxx
	src/cros2/cros2_pointcloud_support.cxx 
	src/cros2/cros2_common.cxx
)
target_link_libraries(wrap_bench PUBLIC RTIConnextDDS::cpp2_api ${ROS_IDL_LIBRARY})

# wrap_app is a native DDS replacement for an equivalent ROS2 app
add_executable(wrap_app
  	src/demos/bench/app/wrap_app_main.cxx
	src/cros2/cros2_pointcloud_support.cxx 
	src/cros2/cros2_common.cxx
)
target_link_libraries(wrap_app PUBLIC RTIConnextDDS::cpp2_api ${ROS_IDL_LIBRARY})

# blast_pub is a variable-rate publisher of ROS2 topics
add_executable(blast_pub
  	src/demos/bench/tester/blast_pub_main.cxx
	src/cros2/cros2_pointcloud_support.cxx 
	src/cros2/cros2_common.cxx
)
target_link_libraries(blast_pub PUBLIC RTIConnextDDS::cpp2_api ${ROS_IDL_LIBRARY})

# blast_sub is a subscriber/counter of ROS2 topics
add_executable(blast_sub
  	src/demos/bench/tester/blast_sub_main.cxx
	src/cros2/cros2_pointcloud_support.cxx 
	src/cros2/cros2_common.cxx
)
target_link_libraries(blast_sub PUBLIC RTIConnextDDS::cpp2_api ${ROS_IDL_LIBRARY})

# pointcam converts camera video into PointCloud2 data type
#add_executable( pointcam 
#  src/demos/opencv/pointcam/pointcam.cpp
#  src/demos/opencv/pointcam/pic_frame_motion_depth.cxx
#  src/cros2/cros2_pointcloud_support.cxx 
#	src/cros2/cros2_common.cxx
#)
#target_link_libraries(pointcam PUBLIC RTIConnextDDS::cpp2_api ${OpenCV_LIBS} ${ROS_IDL_LIBRARY})
