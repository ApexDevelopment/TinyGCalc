# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 4.0

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\build

# Include any dependencies generated for this target.
include CMakeFiles/tinygcalc.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/tinygcalc.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/tinygcalc.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/tinygcalc.dir/flags.make

CMakeFiles/tinygcalc.dir/codegen:
.PHONY : CMakeFiles/tinygcalc.dir/codegen

CMakeFiles/tinygcalc.dir/src/main.c.obj: CMakeFiles/tinygcalc.dir/flags.make
CMakeFiles/tinygcalc.dir/src/main.c.obj: CMakeFiles/tinygcalc.dir/includes_C.rsp
CMakeFiles/tinygcalc.dir/src/main.c.obj: C:/Users/Micah/Documents/MEGA/Coding/TinyGCalc/src/main.c
CMakeFiles/tinygcalc.dir/src/main.c.obj: CMakeFiles/tinygcalc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/tinygcalc.dir/src/main.c.obj"
	C:\Tools\mingw-w64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/tinygcalc.dir/src/main.c.obj -MF CMakeFiles\tinygcalc.dir\src\main.c.obj.d -o CMakeFiles\tinygcalc.dir\src\main.c.obj -c C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\src\main.c

CMakeFiles/tinygcalc.dir/src/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/tinygcalc.dir/src/main.c.i"
	C:\Tools\mingw-w64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\src\main.c > CMakeFiles\tinygcalc.dir\src\main.c.i

CMakeFiles/tinygcalc.dir/src/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/tinygcalc.dir/src/main.c.s"
	C:\Tools\mingw-w64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\src\main.c -o CMakeFiles\tinygcalc.dir\src\main.c.s

CMakeFiles/tinygcalc.dir/src/core/plotter.c.obj: CMakeFiles/tinygcalc.dir/flags.make
CMakeFiles/tinygcalc.dir/src/core/plotter.c.obj: CMakeFiles/tinygcalc.dir/includes_C.rsp
CMakeFiles/tinygcalc.dir/src/core/plotter.c.obj: C:/Users/Micah/Documents/MEGA/Coding/TinyGCalc/src/core/plotter.c
CMakeFiles/tinygcalc.dir/src/core/plotter.c.obj: CMakeFiles/tinygcalc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/tinygcalc.dir/src/core/plotter.c.obj"
	C:\Tools\mingw-w64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/tinygcalc.dir/src/core/plotter.c.obj -MF CMakeFiles\tinygcalc.dir\src\core\plotter.c.obj.d -o CMakeFiles\tinygcalc.dir\src\core\plotter.c.obj -c C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\src\core\plotter.c

CMakeFiles/tinygcalc.dir/src/core/plotter.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/tinygcalc.dir/src/core/plotter.c.i"
	C:\Tools\mingw-w64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\src\core\plotter.c > CMakeFiles\tinygcalc.dir\src\core\plotter.c.i

CMakeFiles/tinygcalc.dir/src/core/plotter.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/tinygcalc.dir/src/core/plotter.c.s"
	C:\Tools\mingw-w64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\src\core\plotter.c -o CMakeFiles\tinygcalc.dir\src\core\plotter.c.s

CMakeFiles/tinygcalc.dir/lib/tinyexpr/tinyexpr.c.obj: CMakeFiles/tinygcalc.dir/flags.make
CMakeFiles/tinygcalc.dir/lib/tinyexpr/tinyexpr.c.obj: CMakeFiles/tinygcalc.dir/includes_C.rsp
CMakeFiles/tinygcalc.dir/lib/tinyexpr/tinyexpr.c.obj: C:/Users/Micah/Documents/MEGA/Coding/TinyGCalc/lib/tinyexpr/tinyexpr.c
CMakeFiles/tinygcalc.dir/lib/tinyexpr/tinyexpr.c.obj: CMakeFiles/tinygcalc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object CMakeFiles/tinygcalc.dir/lib/tinyexpr/tinyexpr.c.obj"
	C:\Tools\mingw-w64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/tinygcalc.dir/lib/tinyexpr/tinyexpr.c.obj -MF CMakeFiles\tinygcalc.dir\lib\tinyexpr\tinyexpr.c.obj.d -o CMakeFiles\tinygcalc.dir\lib\tinyexpr\tinyexpr.c.obj -c C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\lib\tinyexpr\tinyexpr.c

CMakeFiles/tinygcalc.dir/lib/tinyexpr/tinyexpr.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/tinygcalc.dir/lib/tinyexpr/tinyexpr.c.i"
	C:\Tools\mingw-w64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\lib\tinyexpr\tinyexpr.c > CMakeFiles\tinygcalc.dir\lib\tinyexpr\tinyexpr.c.i

CMakeFiles/tinygcalc.dir/lib/tinyexpr/tinyexpr.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/tinygcalc.dir/lib/tinyexpr/tinyexpr.c.s"
	C:\Tools\mingw-w64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\lib\tinyexpr\tinyexpr.c -o CMakeFiles\tinygcalc.dir\lib\tinyexpr\tinyexpr.c.s

CMakeFiles/tinygcalc.dir/src/platform/mock/hal_display.c.obj: CMakeFiles/tinygcalc.dir/flags.make
CMakeFiles/tinygcalc.dir/src/platform/mock/hal_display.c.obj: CMakeFiles/tinygcalc.dir/includes_C.rsp
CMakeFiles/tinygcalc.dir/src/platform/mock/hal_display.c.obj: C:/Users/Micah/Documents/MEGA/Coding/TinyGCalc/src/platform/mock/hal_display.c
CMakeFiles/tinygcalc.dir/src/platform/mock/hal_display.c.obj: CMakeFiles/tinygcalc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building C object CMakeFiles/tinygcalc.dir/src/platform/mock/hal_display.c.obj"
	C:\Tools\mingw-w64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/tinygcalc.dir/src/platform/mock/hal_display.c.obj -MF CMakeFiles\tinygcalc.dir\src\platform\mock\hal_display.c.obj.d -o CMakeFiles\tinygcalc.dir\src\platform\mock\hal_display.c.obj -c C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\src\platform\mock\hal_display.c

CMakeFiles/tinygcalc.dir/src/platform/mock/hal_display.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/tinygcalc.dir/src/platform/mock/hal_display.c.i"
	C:\Tools\mingw-w64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\src\platform\mock\hal_display.c > CMakeFiles\tinygcalc.dir\src\platform\mock\hal_display.c.i

CMakeFiles/tinygcalc.dir/src/platform/mock/hal_display.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/tinygcalc.dir/src/platform/mock/hal_display.c.s"
	C:\Tools\mingw-w64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\src\platform\mock\hal_display.c -o CMakeFiles\tinygcalc.dir\src\platform\mock\hal_display.c.s

CMakeFiles/tinygcalc.dir/src/platform/mock/hal_input.c.obj: CMakeFiles/tinygcalc.dir/flags.make
CMakeFiles/tinygcalc.dir/src/platform/mock/hal_input.c.obj: CMakeFiles/tinygcalc.dir/includes_C.rsp
CMakeFiles/tinygcalc.dir/src/platform/mock/hal_input.c.obj: C:/Users/Micah/Documents/MEGA/Coding/TinyGCalc/src/platform/mock/hal_input.c
CMakeFiles/tinygcalc.dir/src/platform/mock/hal_input.c.obj: CMakeFiles/tinygcalc.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building C object CMakeFiles/tinygcalc.dir/src/platform/mock/hal_input.c.obj"
	C:\Tools\mingw-w64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/tinygcalc.dir/src/platform/mock/hal_input.c.obj -MF CMakeFiles\tinygcalc.dir\src\platform\mock\hal_input.c.obj.d -o CMakeFiles\tinygcalc.dir\src\platform\mock\hal_input.c.obj -c C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\src\platform\mock\hal_input.c

CMakeFiles/tinygcalc.dir/src/platform/mock/hal_input.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/tinygcalc.dir/src/platform/mock/hal_input.c.i"
	C:\Tools\mingw-w64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\src\platform\mock\hal_input.c > CMakeFiles\tinygcalc.dir\src\platform\mock\hal_input.c.i

CMakeFiles/tinygcalc.dir/src/platform/mock/hal_input.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/tinygcalc.dir/src/platform/mock/hal_input.c.s"
	C:\Tools\mingw-w64\bin\gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\src\platform\mock\hal_input.c -o CMakeFiles\tinygcalc.dir\src\platform\mock\hal_input.c.s

# Object files for target tinygcalc
tinygcalc_OBJECTS = \
"CMakeFiles/tinygcalc.dir/src/main.c.obj" \
"CMakeFiles/tinygcalc.dir/src/core/plotter.c.obj" \
"CMakeFiles/tinygcalc.dir/lib/tinyexpr/tinyexpr.c.obj" \
"CMakeFiles/tinygcalc.dir/src/platform/mock/hal_display.c.obj" \
"CMakeFiles/tinygcalc.dir/src/platform/mock/hal_input.c.obj"

# External object files for target tinygcalc
tinygcalc_EXTERNAL_OBJECTS =

tinygcalc.exe: CMakeFiles/tinygcalc.dir/src/main.c.obj
tinygcalc.exe: CMakeFiles/tinygcalc.dir/src/core/plotter.c.obj
tinygcalc.exe: CMakeFiles/tinygcalc.dir/lib/tinyexpr/tinyexpr.c.obj
tinygcalc.exe: CMakeFiles/tinygcalc.dir/src/platform/mock/hal_display.c.obj
tinygcalc.exe: CMakeFiles/tinygcalc.dir/src/platform/mock/hal_input.c.obj
tinygcalc.exe: CMakeFiles/tinygcalc.dir/build.make
tinygcalc.exe: CMakeFiles/tinygcalc.dir/linkLibs.rsp
tinygcalc.exe: CMakeFiles/tinygcalc.dir/objects1.rsp
tinygcalc.exe: CMakeFiles/tinygcalc.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking C executable tinygcalc.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\tinygcalc.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/tinygcalc.dir/build: tinygcalc.exe
.PHONY : CMakeFiles/tinygcalc.dir/build

CMakeFiles/tinygcalc.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\tinygcalc.dir\cmake_clean.cmake
.PHONY : CMakeFiles/tinygcalc.dir/clean

CMakeFiles/tinygcalc.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\build C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\build C:\Users\Micah\Documents\MEGA\Coding\TinyGCalc\build\CMakeFiles\tinygcalc.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/tinygcalc.dir/depend

