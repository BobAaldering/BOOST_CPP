# Tutorial 'Boost your C++!'

In this tutorial an explanation is given about various libraries that can actually give your C++ program a boost!

The 'Boost' library is used to add various functionalities to your C++ program.
You will be guided how to download the 'Boost' features, and make them available to your program, if not the executable.

In addition, various 'Boost' libraries are also developed, with examples of actually working programs.

## Download the Boost library's

To make the facilities of the 'Boost' library available, you must first download it.
For example, you can use a Linux terminal for this. This is useful if you are using WSL, where you build and debugged your C++ program in Linux.

To download the 'Boost' libraries run the following `apt-get` command:
```shell
sudo apt-get install libboost-all-dev
```

After the installation of this library is complete it is ready to be used in your C++ program!

## Add everything to your executable with CMake

If your installation of the 'Boost' library was successful, unfortunately it cannot yet be used directly in your program/executable file. To make this available we use CMake. This is a multi-platform system for build automation, originally also written in C++. It is similar to the Unix `make` program, but CMake only generates standard build files.

### The start of your `CMakeLists.txt`

In CMake, you first want to determine a number of standards, such as the version of CMake. You also name your project, in this case `TOPIC_1`. In this case, the executable will also have this name, which is named `add_executable(TOPIC_1)`. With the help of `target_sources(...)` you can indicate which files should be compiled, and then added to your executable. For example, if you just want to add `main.cpp` this statement will look like this: `target_sources(${target} PRIVATE main.cpp)`. To add additional files in this, do this as follows: `target_sources(${target} PRIVATE main.cpp class.cpp communicate.cpp)`. Here `class.cpp` and `communicate.cpp` are new files, for example from newly created classes.

Initially, your CMake will now look like this:
```cmake
cmake_minimum_required(VERSION 3.21) # The minimum CMake version used.
project(TOPIC_1) # Name of the current project.

add_executable(TOPIC_1) # Define a name for your executable.

set(target TOPIC_1) # Create a name for your target.

# Here, you can add the files you want to add to your executable.
target_sources(${target}
        PRIVATE
        main.cpp
        )
```

### Trigger warnings for the compilers

Then of course you want to be sure that your C++ code does not contain errors. Your compiler provides a number of extra checks for this, which can solve unpleasant problems in the program. For example, for `GNU` compilers, the following flags are `-Werror`, `-Wall` or `-pedantic`. Of course, more flags are also available for this. You can also let the compiler optimize the generated code with `-O3` for release mode.
If you use the `MSVC` compiler you cannot pass the same flags as a `GNU` compiler. For example, to activate all warnings in `MSVC` you need to do `/Wall`. For optimization use `/O2` for release or for example `/RTC1` for debug.

In CMake, it is of course also necessary that you name the C++ version that you are using. This project uses `C++23`. If your own compiler does not support this, you can change this statement to: `target_compile_features(${target} PRIVATE cxx_std_17)`. Any extensions of your compiler are disabled with `set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF)`.

Now you can add the CMake code below:
```cmake
target_compile_features(${target} PRIVATE cxx_std_23) # We are using the newest language standards, so C++23.
set_target_properties(${target} PROPERTIES CXX_EXTENSIONS OFF) # Turn of compiler specific language extensions.

# Set the options for GNU-linke compilers:
target_compile_options(${target} PRIVATE
        # Set all warnings for all the build types.
        $<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:-Wall -Wextra -Wpedantic -Werror -fno-omit-frame-pointer>
        # Optimisation for 'Release' mode.
        $<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Release>>:-O3>
        # Optimisation in 'Debug'.
        $<$<AND:$<CXX_COMPILER_ID:GNU,Clang,AppleClang>,$<CONFIG:Debug>>:-Og -g>
        )

# Set options for MSVC
target_compile_options(${target} PRIVATE
        # set warnings for all build types
        $<$<CXX_COMPILER_ID:MSVC>:/Wall>
        # debug optimisation in Debug
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/O2>
        # O3 optimisation in Release
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/RTC1 /Od /Zi>
        )
```

If you have become curious about the above syntax, please refer to the following [link](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html).
Generator expressions are used. Generator expressions are evaluated during build system generation to produce information specific to each build configuration.

### Enabling the 'Address Sanitizer'

To ensure that your program does not suffer from, for example, memory leaks, an 'Address Sanitizer' is used. This is a dynamic analysis, where your program is executed when your program is actually running. The 'Address Sanitizer' will check for the following points:
* Use after free (dangling pointer dereference)
* Heap buffer overflow
* Stack buffer overflow
* Global buffer overflow
* Use after return
* Use after scope
* Initialization order bugs
* Memory leaks

If you're using Linux (including WSL) and Mac, you don't need to do anything for the installation. This is because they are already part of `Clang` or `GCC`.
Installing them on Windows systems can be problematic. It is therefore recommended to use WSL in Windows.

Given below is the CMake code to activate the 'Address Sanitizer'. It will first check if the ASan library (Address Sanitizer) is available. Then ASan is activated for your target, so the executable.

```cmake
# Try to find the path of your 'Address Sanitizer'.
execute_process(COMMAND "${CMAKE_CXX_COMPILER}" -print-file-name=libasan.so
        OUTPUT_VARIABLE LIBASAN_PATH
        RESULT_VARIABLE ASAN_RESULT
        OUTPUT_STRIP_TRAILING_WHITESPACE)

set(HAS_ASAN FALSE)

# Check if the path of the 'Address Sanitizer' is found.
if (USE_ASAN AND (${ASAN_RESULT} EQUAL 0) AND (NOT ${LIBASAN_PATH} STREQUAL ""))
    message("libasan found @${LIBASAN_PATH}") # Show the path of the sanitizer.
    message("To disable the address sanitizer set USE_ASAN to OFF.\n") # Show how to turn off the address sanitizer.
    set(HAS_ASAN TRUE) # Now, your sanitizer is enabled.
endif ()

if (HAS_ASAN AND USE_ASAN)
    target_compile_options(${target} PRIVATE -fsanitize=address) # Set the target compile options for the sanitizer.
    target_link_options(${target} PRIVATE -fsanitize=address) # The link options for the sanitizer.
endif ()
```

### Adding 'Boost'

Now comes the most important part: making the correct `Boost` components available to your executable. First, a number of variables are activated. Feel free to change it yourself. If you do not want to use `multithreading`, you can indicate this by writing `OFF` at the correct variable.
After this, it will search for the `Boost` library with `find_package(...)`. In this case, the search is for version with minimum `1.70.0`. With newer versions this can easily be changed.
When the `Boost` library is found you can indicate which parts you want to add. For [program options](https://www.boost.org/doc/libs/1_77_0/doc/html/program_options.html), for example, this is `target_link_libraries(TOPIC_1 Boost::program_options)`.

```cmake
# Here, you can enable all the required 'Boost' components:
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_DEBUG_LIBS ON)
set(Boost_USE_RELEASE_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.70.0 COMPONENTS program_options system thread) # Try to find your 'Boost' package, right now, we are using 'Boost 1.70.0'.

# Check if the 'Boost' library/packages are found.
if(Boost_FOUND)
    message("Boost library found!") # Show a message that the 'Boost' library is found.
    target_link_libraries(TOPIC_1 Boost::program_options Boost::system Boost::thread) # Here, you are linking all the libraries available the 'Boost' library.
endif()
```

If you see the full CMake code used to enable compiling see the [CMakeLists.txt](CMakeLists.txt).

