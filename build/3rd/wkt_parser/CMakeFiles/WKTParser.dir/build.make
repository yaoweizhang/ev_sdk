# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /usr/local/ev_sdk

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /usr/local/ev_sdk/build

# Include any dependencies generated for this target.
include 3rd/wkt_parser/CMakeFiles/WKTParser.dir/depend.make

# Include the progress variables for this target.
include 3rd/wkt_parser/CMakeFiles/WKTParser.dir/progress.make

# Include the compile flags for this target's objects.
include 3rd/wkt_parser/CMakeFiles/WKTParser.dir/flags.make

3rd/wkt_parser/CMakeFiles/WKTParser.dir/src/WKTParser.cpp.o: 3rd/wkt_parser/CMakeFiles/WKTParser.dir/flags.make
3rd/wkt_parser/CMakeFiles/WKTParser.dir/src/WKTParser.cpp.o: ../3rd/wkt_parser/src/WKTParser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/usr/local/ev_sdk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object 3rd/wkt_parser/CMakeFiles/WKTParser.dir/src/WKTParser.cpp.o"
	cd /usr/local/ev_sdk/build/3rd/wkt_parser && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/WKTParser.dir/src/WKTParser.cpp.o -c /usr/local/ev_sdk/3rd/wkt_parser/src/WKTParser.cpp

3rd/wkt_parser/CMakeFiles/WKTParser.dir/src/WKTParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/WKTParser.dir/src/WKTParser.cpp.i"
	cd /usr/local/ev_sdk/build/3rd/wkt_parser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /usr/local/ev_sdk/3rd/wkt_parser/src/WKTParser.cpp > CMakeFiles/WKTParser.dir/src/WKTParser.cpp.i

3rd/wkt_parser/CMakeFiles/WKTParser.dir/src/WKTParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/WKTParser.dir/src/WKTParser.cpp.s"
	cd /usr/local/ev_sdk/build/3rd/wkt_parser && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /usr/local/ev_sdk/3rd/wkt_parser/src/WKTParser.cpp -o CMakeFiles/WKTParser.dir/src/WKTParser.cpp.s

# Object files for target WKTParser
WKTParser_OBJECTS = \
"CMakeFiles/WKTParser.dir/src/WKTParser.cpp.o"

# External object files for target WKTParser
WKTParser_EXTERNAL_OBJECTS =

3rd/wkt_parser/libWKTParser.so: 3rd/wkt_parser/CMakeFiles/WKTParser.dir/src/WKTParser.cpp.o
3rd/wkt_parser/libWKTParser.so: 3rd/wkt_parser/CMakeFiles/WKTParser.dir/build.make
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_gapi.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_stitching.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_aruco.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_bgsegm.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_bioinspired.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_ccalib.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_dnn_objdetect.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_dnn_superres.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_dpm.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_face.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_freetype.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_fuzzy.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_hdf.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_hfs.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_img_hash.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_line_descriptor.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_quality.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_reg.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_rgbd.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_saliency.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_sfm.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_stereo.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_structured_light.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_superres.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_surface_matching.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_tracking.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_videostab.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_xfeatures2d.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_xobjdetect.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_xphoto.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_highgui.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_shape.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_datasets.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_plot.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_text.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_dnn.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_ml.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_phase_unwrapping.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_optflow.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_ximgproc.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_video.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_videoio.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_imgcodecs.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_objdetect.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_calib3d.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_features2d.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_flann.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_photo.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_imgproc.so.4.1.2
3rd/wkt_parser/libWKTParser.so: /usr/local/lib/libopencv_core.so.4.1.2
3rd/wkt_parser/libWKTParser.so: 3rd/wkt_parser/CMakeFiles/WKTParser.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/usr/local/ev_sdk/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX shared library libWKTParser.so"
	cd /usr/local/ev_sdk/build/3rd/wkt_parser && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/WKTParser.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
3rd/wkt_parser/CMakeFiles/WKTParser.dir/build: 3rd/wkt_parser/libWKTParser.so

.PHONY : 3rd/wkt_parser/CMakeFiles/WKTParser.dir/build

3rd/wkt_parser/CMakeFiles/WKTParser.dir/clean:
	cd /usr/local/ev_sdk/build/3rd/wkt_parser && $(CMAKE_COMMAND) -P CMakeFiles/WKTParser.dir/cmake_clean.cmake
.PHONY : 3rd/wkt_parser/CMakeFiles/WKTParser.dir/clean

3rd/wkt_parser/CMakeFiles/WKTParser.dir/depend:
	cd /usr/local/ev_sdk/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /usr/local/ev_sdk /usr/local/ev_sdk/3rd/wkt_parser /usr/local/ev_sdk/build /usr/local/ev_sdk/build/3rd/wkt_parser /usr/local/ev_sdk/build/3rd/wkt_parser/CMakeFiles/WKTParser.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : 3rd/wkt_parser/CMakeFiles/WKTParser.dir/depend

