# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_COMMAND = /media/wangbin/36005E93005E59C7/CLion-2019.2/clion-2019.2/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /media/wangbin/36005E93005E59C7/CLion-2019.2/clion-2019.2/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /media/wangbin/36005E93005E59C7/face_tracker_detector

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /media/wangbin/36005E93005E59C7/face_tracker_detector/cmake-build-debug

# Include any dependencies generated for this target.
include src/exe/CMakeFiles/annotate_main.dir/depend.make

# Include the progress variables for this target.
include src/exe/CMakeFiles/annotate_main.dir/progress.make

# Include the compile flags for this target's objects.
include src/exe/CMakeFiles/annotate_main.dir/flags.make

src/exe/CMakeFiles/annotate_main.dir/annotate_main.cpp.o: src/exe/CMakeFiles/annotate_main.dir/flags.make
src/exe/CMakeFiles/annotate_main.dir/annotate_main.cpp.o: ../src/exe/annotate_main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/media/wangbin/36005E93005E59C7/face_tracker_detector/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/exe/CMakeFiles/annotate_main.dir/annotate_main.cpp.o"
	cd /media/wangbin/36005E93005E59C7/face_tracker_detector/cmake-build-debug/src/exe && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/annotate_main.dir/annotate_main.cpp.o -c /media/wangbin/36005E93005E59C7/face_tracker_detector/src/exe/annotate_main.cpp

src/exe/CMakeFiles/annotate_main.dir/annotate_main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/annotate_main.dir/annotate_main.cpp.i"
	cd /media/wangbin/36005E93005E59C7/face_tracker_detector/cmake-build-debug/src/exe && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /media/wangbin/36005E93005E59C7/face_tracker_detector/src/exe/annotate_main.cpp > CMakeFiles/annotate_main.dir/annotate_main.cpp.i

src/exe/CMakeFiles/annotate_main.dir/annotate_main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/annotate_main.dir/annotate_main.cpp.s"
	cd /media/wangbin/36005E93005E59C7/face_tracker_detector/cmake-build-debug/src/exe && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /media/wangbin/36005E93005E59C7/face_tracker_detector/src/exe/annotate_main.cpp -o CMakeFiles/annotate_main.dir/annotate_main.cpp.s

# Object files for target annotate_main
annotate_main_OBJECTS = \
"CMakeFiles/annotate_main.dir/annotate_main.cpp.o"

# External object files for target annotate_main
annotate_main_EXTERNAL_OBJECTS =

src/exe/annotate_main: src/exe/CMakeFiles/annotate_main.dir/annotate_main.cpp.o
src/exe/annotate_main: src/exe/CMakeFiles/annotate_main.dir/build.make
src/exe/annotate_main: libft_base.so
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_stitching.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_aruco.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_bgsegm.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_bioinspired.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_ccalib.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_cvv.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_dnn_objdetect.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_dpm.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_face.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_freetype.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_fuzzy.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_hdf.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_hfs.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_img_hash.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_line_descriptor.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_quality.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_reg.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_rgbd.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_saliency.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_stereo.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_structured_light.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_phase_unwrapping.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_superres.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_optflow.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_surface_matching.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_tracking.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_datasets.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_plot.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_text.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_dnn.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_videostab.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_video.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_viz.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_xfeatures2d.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_ml.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_shape.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_ximgproc.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_xobjdetect.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_objdetect.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_calib3d.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_features2d.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_flann.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_highgui.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_videoio.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_imgcodecs.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_xphoto.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_photo.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_imgproc.so.4.1.0
src/exe/annotate_main: /usr/local/opencv/lib/libopencv_core.so.4.1.0
src/exe/annotate_main: src/exe/CMakeFiles/annotate_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/media/wangbin/36005E93005E59C7/face_tracker_detector/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable annotate_main"
	cd /media/wangbin/36005E93005E59C7/face_tracker_detector/cmake-build-debug/src/exe && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/annotate_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/exe/CMakeFiles/annotate_main.dir/build: src/exe/annotate_main

.PHONY : src/exe/CMakeFiles/annotate_main.dir/build

src/exe/CMakeFiles/annotate_main.dir/clean:
	cd /media/wangbin/36005E93005E59C7/face_tracker_detector/cmake-build-debug/src/exe && $(CMAKE_COMMAND) -P CMakeFiles/annotate_main.dir/cmake_clean.cmake
.PHONY : src/exe/CMakeFiles/annotate_main.dir/clean

src/exe/CMakeFiles/annotate_main.dir/depend:
	cd /media/wangbin/36005E93005E59C7/face_tracker_detector/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /media/wangbin/36005E93005E59C7/face_tracker_detector /media/wangbin/36005E93005E59C7/face_tracker_detector/src/exe /media/wangbin/36005E93005E59C7/face_tracker_detector/cmake-build-debug /media/wangbin/36005E93005E59C7/face_tracker_detector/cmake-build-debug/src/exe /media/wangbin/36005E93005E59C7/face_tracker_detector/cmake-build-debug/src/exe/CMakeFiles/annotate_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/exe/CMakeFiles/annotate_main.dir/depend

