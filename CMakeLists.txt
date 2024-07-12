cmake_minimum_required(VERSION 3.3.2)
project (ros2_interop_demos)

if(DEFINED ENV{NDDSHOME})
  set(NDDSHOME $ENV{NDDSHOME})
else()
  message(FATAL_ERROR "NDDSHOME (env var) is not set")
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/resources/cmake)
find_package(RTIConnextDDS REQUIRED)

# - Point to the source dirs and files ----------
include_directories(
    "src/generated"
    ${CONNEXTDDS_INCLUDE_DIRS}
)

# Set paths
set(PATH_CODEGEN ${CMAKE_CURRENT_SOURCE_DIR}/src/generated)
# Set files generated from code gen
set(FILES_CODEGEN
  ${PATH_CODEGEN}/turtle_shape_types.cxx
  ${PATH_CODEGEN}/turtle_shape_typesPlugin.cxx
  ${PATH_CODEGEN}/rviz_demo_types.cxx
  ${PATH_CODEGEN}/rviz_demo_typesPlugin.cxx
  )
# Run Codegen to generate the source code files for the types
include(ConnextDdsCodegen)
connextdds_rtiddsgen_run(
  IDL_FILE ${PATH_CODEGEN}/turtle_shape_types.idl 
  OUTPUT_DIRECTORY ${PATH_CODEGEN}
  LANG C++11
  UNBOUNDED
)
connextdds_rtiddsgen_run(
  IDL_FILE ${PATH_CODEGEN}/rviz_demo_types.idl
  OUTPUT_DIRECTORY ${PATH_CODEGEN}
  LANG C++11
  UNBOUNDED
)
  
add_custom_target(codegen_sources
  DEPENDS ${FILES_CODEGEN})

# - Executables to build -----------------------------------------------------
# turtle_shapes: use Shapes Demo to drive ROS2 TurtleSim demo.
add_executable(turtle_shapes 
  src/turtle_shapes_app/turtle_shapes.cxx 
  src/turtle_shapes_app/cros2_turtlesim_support.cxx 
  src/turtle_shapes_app/shapesdemo_support.cxx
  src/generated/turtle_shape_types.cxx
  src/generated/turtle_shape_typesPlugin.cxx
)
target_link_libraries(turtle_shapes PUBLIC RTIConnextDDS::cpp2_api)

# rviz_demo: produces data for most of the visualizers in ROS2 RViz
add_executable(rviz_demo 
  src/rviz_demo/rviz_demo.cxx 
  src/generated/rviz_demo_types.cxx
  src/generated/rviz_demo_typesPlugin.cxx
)
target_link_libraries(rviz_demo PUBLIC RTIConnextDDS::cpp2_api)
