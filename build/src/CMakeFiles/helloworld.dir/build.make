# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/tubbadu/code/Kirigami/ktoggle

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/tubbadu/code/Kirigami/ktoggle/build

# Include any dependencies generated for this target.
include src/CMakeFiles/helloworld.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/CMakeFiles/helloworld.dir/compiler_depend.make

# Include the progress variables for this target.
include src/CMakeFiles/helloworld.dir/progress.make

# Include the compile flags for this target's objects.
include src/CMakeFiles/helloworld.dir/flags.make

src/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp: /home/tubbadu/code/Kirigami/ktoggle/src/resources.qrc
src/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp: src/CMakeFiles/helloworld_autogen.dir/AutoRcc_resources_EWIEGA46WW_Info.json
src/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp: /home/tubbadu/code/Kirigami/ktoggle/src/contents/ui/main.qml
src/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp: /usr/lib64/qt5/bin/rcc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/tubbadu/code/Kirigami/ktoggle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic RCC for resources.qrc"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/cmake -E cmake_autorcc /home/tubbadu/code/Kirigami/ktoggle/build/src/CMakeFiles/helloworld_autogen.dir/AutoRcc_resources_EWIEGA46WW_Info.json Debug

src/CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.o: src/CMakeFiles/helloworld.dir/flags.make
src/CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.o: src/helloworld_autogen/mocs_compilation.cpp
src/CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.o: src/CMakeFiles/helloworld.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tubbadu/code/Kirigami/ktoggle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.o"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.o -MF CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.o.d -o CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.o -c /home/tubbadu/code/Kirigami/ktoggle/build/src/helloworld_autogen/mocs_compilation.cpp

src/CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.i"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tubbadu/code/Kirigami/ktoggle/build/src/helloworld_autogen/mocs_compilation.cpp > CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.i

src/CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.s"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tubbadu/code/Kirigami/ktoggle/build/src/helloworld_autogen/mocs_compilation.cpp -o CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.s

src/CMakeFiles/helloworld.dir/main.cpp.o: src/CMakeFiles/helloworld.dir/flags.make
src/CMakeFiles/helloworld.dir/main.cpp.o: /home/tubbadu/code/Kirigami/ktoggle/src/main.cpp
src/CMakeFiles/helloworld.dir/main.cpp.o: src/CMakeFiles/helloworld.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tubbadu/code/Kirigami/ktoggle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/CMakeFiles/helloworld.dir/main.cpp.o"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/helloworld.dir/main.cpp.o -MF CMakeFiles/helloworld.dir/main.cpp.o.d -o CMakeFiles/helloworld.dir/main.cpp.o -c /home/tubbadu/code/Kirigami/ktoggle/src/main.cpp

src/CMakeFiles/helloworld.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/helloworld.dir/main.cpp.i"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tubbadu/code/Kirigami/ktoggle/src/main.cpp > CMakeFiles/helloworld.dir/main.cpp.i

src/CMakeFiles/helloworld.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/helloworld.dir/main.cpp.s"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tubbadu/code/Kirigami/ktoggle/src/main.cpp -o CMakeFiles/helloworld.dir/main.cpp.s

src/CMakeFiles/helloworld.dir/launcher.cpp.o: src/CMakeFiles/helloworld.dir/flags.make
src/CMakeFiles/helloworld.dir/launcher.cpp.o: /home/tubbadu/code/Kirigami/ktoggle/src/launcher.cpp
src/CMakeFiles/helloworld.dir/launcher.cpp.o: src/CMakeFiles/helloworld.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tubbadu/code/Kirigami/ktoggle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/CMakeFiles/helloworld.dir/launcher.cpp.o"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/helloworld.dir/launcher.cpp.o -MF CMakeFiles/helloworld.dir/launcher.cpp.o.d -o CMakeFiles/helloworld.dir/launcher.cpp.o -c /home/tubbadu/code/Kirigami/ktoggle/src/launcher.cpp

src/CMakeFiles/helloworld.dir/launcher.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/helloworld.dir/launcher.cpp.i"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tubbadu/code/Kirigami/ktoggle/src/launcher.cpp > CMakeFiles/helloworld.dir/launcher.cpp.i

src/CMakeFiles/helloworld.dir/launcher.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/helloworld.dir/launcher.cpp.s"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tubbadu/code/Kirigami/ktoggle/src/launcher.cpp -o CMakeFiles/helloworld.dir/launcher.cpp.s

src/CMakeFiles/helloworld.dir/TrayIcon.cpp.o: src/CMakeFiles/helloworld.dir/flags.make
src/CMakeFiles/helloworld.dir/TrayIcon.cpp.o: /home/tubbadu/code/Kirigami/ktoggle/src/TrayIcon.cpp
src/CMakeFiles/helloworld.dir/TrayIcon.cpp.o: src/CMakeFiles/helloworld.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tubbadu/code/Kirigami/ktoggle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/CMakeFiles/helloworld.dir/TrayIcon.cpp.o"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/helloworld.dir/TrayIcon.cpp.o -MF CMakeFiles/helloworld.dir/TrayIcon.cpp.o.d -o CMakeFiles/helloworld.dir/TrayIcon.cpp.o -c /home/tubbadu/code/Kirigami/ktoggle/src/TrayIcon.cpp

src/CMakeFiles/helloworld.dir/TrayIcon.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/helloworld.dir/TrayIcon.cpp.i"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tubbadu/code/Kirigami/ktoggle/src/TrayIcon.cpp > CMakeFiles/helloworld.dir/TrayIcon.cpp.i

src/CMakeFiles/helloworld.dir/TrayIcon.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/helloworld.dir/TrayIcon.cpp.s"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tubbadu/code/Kirigami/ktoggle/src/TrayIcon.cpp -o CMakeFiles/helloworld.dir/TrayIcon.cpp.s

src/CMakeFiles/helloworld.dir/Embedder.cpp.o: src/CMakeFiles/helloworld.dir/flags.make
src/CMakeFiles/helloworld.dir/Embedder.cpp.o: /home/tubbadu/code/Kirigami/ktoggle/src/Embedder.cpp
src/CMakeFiles/helloworld.dir/Embedder.cpp.o: src/CMakeFiles/helloworld.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tubbadu/code/Kirigami/ktoggle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/CMakeFiles/helloworld.dir/Embedder.cpp.o"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/helloworld.dir/Embedder.cpp.o -MF CMakeFiles/helloworld.dir/Embedder.cpp.o.d -o CMakeFiles/helloworld.dir/Embedder.cpp.o -c /home/tubbadu/code/Kirigami/ktoggle/src/Embedder.cpp

src/CMakeFiles/helloworld.dir/Embedder.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/helloworld.dir/Embedder.cpp.i"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tubbadu/code/Kirigami/ktoggle/src/Embedder.cpp > CMakeFiles/helloworld.dir/Embedder.cpp.i

src/CMakeFiles/helloworld.dir/Embedder.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/helloworld.dir/Embedder.cpp.s"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tubbadu/code/Kirigami/ktoggle/src/Embedder.cpp -o CMakeFiles/helloworld.dir/Embedder.cpp.s

src/CMakeFiles/helloworld.dir/MainWindow.cpp.o: src/CMakeFiles/helloworld.dir/flags.make
src/CMakeFiles/helloworld.dir/MainWindow.cpp.o: /home/tubbadu/code/Kirigami/ktoggle/src/MainWindow.cpp
src/CMakeFiles/helloworld.dir/MainWindow.cpp.o: src/CMakeFiles/helloworld.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tubbadu/code/Kirigami/ktoggle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/CMakeFiles/helloworld.dir/MainWindow.cpp.o"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/helloworld.dir/MainWindow.cpp.o -MF CMakeFiles/helloworld.dir/MainWindow.cpp.o.d -o CMakeFiles/helloworld.dir/MainWindow.cpp.o -c /home/tubbadu/code/Kirigami/ktoggle/src/MainWindow.cpp

src/CMakeFiles/helloworld.dir/MainWindow.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/helloworld.dir/MainWindow.cpp.i"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tubbadu/code/Kirigami/ktoggle/src/MainWindow.cpp > CMakeFiles/helloworld.dir/MainWindow.cpp.i

src/CMakeFiles/helloworld.dir/MainWindow.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/helloworld.dir/MainWindow.cpp.s"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tubbadu/code/Kirigami/ktoggle/src/MainWindow.cpp -o CMakeFiles/helloworld.dir/MainWindow.cpp.s

src/CMakeFiles/helloworld.dir/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp.o: src/CMakeFiles/helloworld.dir/flags.make
src/CMakeFiles/helloworld.dir/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp.o: src/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp
src/CMakeFiles/helloworld.dir/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp.o: src/CMakeFiles/helloworld.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/tubbadu/code/Kirigami/ktoggle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/CMakeFiles/helloworld.dir/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp.o"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/CMakeFiles/helloworld.dir/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp.o -MF CMakeFiles/helloworld.dir/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp.o.d -o CMakeFiles/helloworld.dir/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp.o -c /home/tubbadu/code/Kirigami/ktoggle/build/src/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp

src/CMakeFiles/helloworld.dir/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/helloworld.dir/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp.i"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/tubbadu/code/Kirigami/ktoggle/build/src/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp > CMakeFiles/helloworld.dir/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp.i

src/CMakeFiles/helloworld.dir/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/helloworld.dir/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp.s"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/tubbadu/code/Kirigami/ktoggle/build/src/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp -o CMakeFiles/helloworld.dir/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp.s

# Object files for target helloworld
helloworld_OBJECTS = \
"CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.o" \
"CMakeFiles/helloworld.dir/main.cpp.o" \
"CMakeFiles/helloworld.dir/launcher.cpp.o" \
"CMakeFiles/helloworld.dir/TrayIcon.cpp.o" \
"CMakeFiles/helloworld.dir/Embedder.cpp.o" \
"CMakeFiles/helloworld.dir/MainWindow.cpp.o" \
"CMakeFiles/helloworld.dir/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp.o"

# External object files for target helloworld
helloworld_EXTERNAL_OBJECTS =

bin/helloworld: src/CMakeFiles/helloworld.dir/helloworld_autogen/mocs_compilation.cpp.o
bin/helloworld: src/CMakeFiles/helloworld.dir/main.cpp.o
bin/helloworld: src/CMakeFiles/helloworld.dir/launcher.cpp.o
bin/helloworld: src/CMakeFiles/helloworld.dir/TrayIcon.cpp.o
bin/helloworld: src/CMakeFiles/helloworld.dir/Embedder.cpp.o
bin/helloworld: src/CMakeFiles/helloworld.dir/MainWindow.cpp.o
bin/helloworld: src/CMakeFiles/helloworld.dir/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp.o
bin/helloworld: src/CMakeFiles/helloworld.dir/build.make
bin/helloworld: lib/libSingleApplication.a
bin/helloworld: /usr/lib64/libX11.so
bin/helloworld: src/CMakeFiles/helloworld.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/tubbadu/code/Kirigami/ktoggle/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Linking CXX executable ../bin/helloworld"
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/helloworld.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/CMakeFiles/helloworld.dir/build: bin/helloworld
.PHONY : src/CMakeFiles/helloworld.dir/build

src/CMakeFiles/helloworld.dir/clean:
	cd /home/tubbadu/code/Kirigami/ktoggle/build/src && $(CMAKE_COMMAND) -P CMakeFiles/helloworld.dir/cmake_clean.cmake
.PHONY : src/CMakeFiles/helloworld.dir/clean

src/CMakeFiles/helloworld.dir/depend: src/helloworld_autogen/EWIEGA46WW/qrc_resources.cpp
	cd /home/tubbadu/code/Kirigami/ktoggle/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/tubbadu/code/Kirigami/ktoggle /home/tubbadu/code/Kirigami/ktoggle/src /home/tubbadu/code/Kirigami/ktoggle/build /home/tubbadu/code/Kirigami/ktoggle/build/src /home/tubbadu/code/Kirigami/ktoggle/build/src/CMakeFiles/helloworld.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/CMakeFiles/helloworld.dir/depend

