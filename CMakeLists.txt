cmake_minimum_required(VERSION 3.21) # The minimum CMake version used.
project(WEATHER_APP) # Name of the current project.

add_executable(WEATHER_APP) # Define a name for your executable.

set(target WEATHER_APP) # Create a name for your target.

# Here, you can add the files you want to add to your executable.
target_sources(${target}
        PRIVATE
        main.cpp
        option_parser.cpp
        weather_client_info.cpp
        weather_data_json.cpp
        weather_json_parser.cpp
        )

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

# Enable the 'Address Sanitizer'.
option(USE_ASAN "Use address sanitizer if available" OFF) # Fancy message. It shows how to turn of the 'Address Sanitizer'.

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
    target_link_libraries(WEATHER_APP Boost::program_options Boost::system Boost::thread) # Here, you are linking all the libraries available the 'Boost' library.
endif()

find_package(OpenSSL REQUIRED) # Try to find your 'OpenSSL' package.

# Check if the 'OpenSSL' library/packages are found.
if (OpenSSL_FOUND)
    message("OpenSSL library found!") # Show a message that the 'OpenSSL' library is found.
    target_link_libraries(WEATHER_APP ${OPENSSL_LIBRARIES}) # Here, you are linking all the libraries available the 'OpenSSL' library.
endif()