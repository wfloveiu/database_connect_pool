# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /home/wufang/Tinywebserver/Mysql_learning

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/wufang/Tinywebserver/Mysql_learning/build

# Include any dependencies generated for this target.
include CMakeFiles/test.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.dir/flags.make

CMakeFiles/test.dir/src/ConnectionPool.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/ConnectionPool.cpp.o: ../src/ConnectionPool.cpp
CMakeFiles/test.dir/src/ConnectionPool.cpp.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wufang/Tinywebserver/Mysql_learning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test.dir/src/ConnectionPool.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/ConnectionPool.cpp.o -MF CMakeFiles/test.dir/src/ConnectionPool.cpp.o.d -o CMakeFiles/test.dir/src/ConnectionPool.cpp.o -c /home/wufang/Tinywebserver/Mysql_learning/src/ConnectionPool.cpp

CMakeFiles/test.dir/src/ConnectionPool.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/ConnectionPool.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wufang/Tinywebserver/Mysql_learning/src/ConnectionPool.cpp > CMakeFiles/test.dir/src/ConnectionPool.cpp.i

CMakeFiles/test.dir/src/ConnectionPool.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/ConnectionPool.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wufang/Tinywebserver/Mysql_learning/src/ConnectionPool.cpp -o CMakeFiles/test.dir/src/ConnectionPool.cpp.s

CMakeFiles/test.dir/src/MysqlConn.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/MysqlConn.cpp.o: ../src/MysqlConn.cpp
CMakeFiles/test.dir/src/MysqlConn.cpp.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wufang/Tinywebserver/Mysql_learning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test.dir/src/MysqlConn.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/MysqlConn.cpp.o -MF CMakeFiles/test.dir/src/MysqlConn.cpp.o.d -o CMakeFiles/test.dir/src/MysqlConn.cpp.o -c /home/wufang/Tinywebserver/Mysql_learning/src/MysqlConn.cpp

CMakeFiles/test.dir/src/MysqlConn.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/MysqlConn.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wufang/Tinywebserver/Mysql_learning/src/MysqlConn.cpp > CMakeFiles/test.dir/src/MysqlConn.cpp.i

CMakeFiles/test.dir/src/MysqlConn.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/MysqlConn.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wufang/Tinywebserver/Mysql_learning/src/MysqlConn.cpp -o CMakeFiles/test.dir/src/MysqlConn.cpp.s

CMakeFiles/test.dir/src/main.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/test.dir/src/main.cpp.o: CMakeFiles/test.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/wufang/Tinywebserver/Mysql_learning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/test.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test.dir/src/main.cpp.o -MF CMakeFiles/test.dir/src/main.cpp.o.d -o CMakeFiles/test.dir/src/main.cpp.o -c /home/wufang/Tinywebserver/Mysql_learning/src/main.cpp

CMakeFiles/test.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/wufang/Tinywebserver/Mysql_learning/src/main.cpp > CMakeFiles/test.dir/src/main.cpp.i

CMakeFiles/test.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/wufang/Tinywebserver/Mysql_learning/src/main.cpp -o CMakeFiles/test.dir/src/main.cpp.s

# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/src/ConnectionPool.cpp.o" \
"CMakeFiles/test.dir/src/MysqlConn.cpp.o" \
"CMakeFiles/test.dir/src/main.cpp.o"

# External object files for target test
test_EXTERNAL_OBJECTS =

../bin/test: CMakeFiles/test.dir/src/ConnectionPool.cpp.o
../bin/test: CMakeFiles/test.dir/src/MysqlConn.cpp.o
../bin/test: CMakeFiles/test.dir/src/main.cpp.o
../bin/test: CMakeFiles/test.dir/build.make
../bin/test: CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/wufang/Tinywebserver/Mysql_learning/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable ../bin/test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.dir/build: ../bin/test
.PHONY : CMakeFiles/test.dir/build

CMakeFiles/test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.dir/clean

CMakeFiles/test.dir/depend:
	cd /home/wufang/Tinywebserver/Mysql_learning/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/wufang/Tinywebserver/Mysql_learning /home/wufang/Tinywebserver/Mysql_learning /home/wufang/Tinywebserver/Mysql_learning/build /home/wufang/Tinywebserver/Mysql_learning/build /home/wufang/Tinywebserver/Mysql_learning/build/CMakeFiles/test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.dir/depend

