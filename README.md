# ros2-interop-demos
Demonstration apps to show ROS2 interoperability with native DDS apps, using the RTI [ros-data-types](https://github.com/neil-rti/ros-data-types) library for ROS2 data type support.


## Building the examples: 
This uses CMAKE to create the makefile or Visual Studio build files. 
To build, do the following: 
 1. PREREQUISITE: clone and build the RTI [ros-data-types](https://github.com/neil-rti/ros-data-types) library, and set its location using the `ROS_DATA_TYPES_DIR` environment variable, as in:
    ```
      Linux:    export ROS_DATA_TYPES_DIR=~/my-build-location/ros-data-types
      Windows:  set ROS_DATA_TYPES_DIR=C:\\my-build-location\\ros-data-types
    ```
 
 2. From this directory, create and cd to a build directory 
    `mkdir build`  
    `cd build`
  
 3. Ensure that the environment variable NDDSHOME is set to your Connext installation location. 
    This can be done easily by running the `"rti_setenv_*"` script or batch file, 
    located in `<Connext-Install-Dir>/resources/scripts/`
    
 4. Use CMake to create the makefile or Visual Studio .sln fileset.
    For example:
    ```
      Linux:    cmake -G "Unix Makefiles" ..
      Windows:  cmake -G "Visual Studio 15 2017" -A x64 ..
    ```
    NOTE: if you have multiple Connext targets installed on your host system, it may
    be better to specify the intended target selection on the CMake command line, using
    the -DCONNEXTDDS_ARCH=(intended architecture) switch, as in:
    ```
      cmake -DCONNEXTDDS_ARCH=x64Linux3gcc5.4.0 -G "Unix Makefiles" ..
    ```
    NOTE: to build for Debug or Release, pass the -DCMAKE_BUILD_TYPE=Release (or Debug (default)) switch to CMake:
    
 5. Build the example. 
    ```
      Linux:    make
      Windows:  devenv ros2_interop_demos.sln
    ```

## Running the examples: 
### **bmp_view** 
This example reads a series of image files (bitmap format, 24bpp) and exports them as ROS2 compatible data topics, which can be rendered in RViz2:
 * **PointCloud2**: randomly selects pixels from the input image, converts these to PointCloud2 data type wherein X(in)=X(out), Y(in)=Z(out), and color(in) is used to set Y(out).
 * **Image**: a scaled-down version of the input image is published as an Image topic.
 * **OccupancyGrid**: a scaled-down version of the input image is published as a Map, using a 99-0 grayscale for colors.
 
The example should be run from the root folder of this example suite to provide a USER_QOS_PROFILES.xml file, and to set the relative path to the image files correctly.  
Rendering in RViz2 will produce:
![RViz render](bmp_view_rviz.jpg)



### **rviz_all** 
This example is a catch-all for RViz interoperability, with a large number of RViz visualization data types to be published.  


### **turtle_shapes**  
This example will subscribe to Circle or Square data from RTI Shapes Demo, and spawn a turtle in the ROS2 TurtleSim demo for each.  
 * **Square** shapes will position the turtle using a ROS2 Service call for absolute positioning.
 * **Circle** shapes will position the turtle using a ROS2 Message for forward motion and turn angle, with feedback of the turtle's location used to create an error signal for a PID controller.  This PID controller has default tuning and may need to be adjusted to accurately position the turtle in your environment.
 ** **Triangle** shapes may be subscribed-to in Shapes Demo to see the reported position of the Circle turtles.  
 
![TurtleShapes](turtle_shapes.jpg)

[more to come; this is a starter README]
