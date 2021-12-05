# Tutorial 'Boost your C++!'

## Introduction

In this tutorial an explanation is given about various libraries that can actually give your C++ program a boost!

The `Boost` library is used to add various functionalities to your C++ program.
You will be guided how to download the `Boost` features, and make them available to your program, if not the executable.

In addition, various `Boost` libraries are also developed, with examples of actually working programs.

### General goal of this tutorial

The purpose of this tutorial is a general introduction to the facilities of `Boost`. A simple weather application is made for this. You can pass a number of arguments to the program, which are represented by a number of flags. A number of positional arguments must also be given, which in this case is the code of a country, together with a place of residence.
Then these command line arguments are parsed using those `option_parser` facilities of `Boost`.
Then, based on the code of the given country and place of residence, an attempt is made to retrieve the weather information.
This is done by means of a client that contacts a server via an HTTPS connection. SSL is also automatically used here. In this case, this server is '[OpenWeatherMap](https://openweathermap.org/appid)', which returns a JSON object following the correct call. Within `Boost` `asio` is used here.
Then this JSON object has to be parsed. Various functions of `Boost` are also used for this. In this case it is `property_tree - json_parser`.
Finally, the information from the JSON object is shown in the standard output. The information that is displayed is of course dependent on the arguments that are given to the program.

This tutorial will therefore go through exactly how this program is generated, and which functions are used within `Boost`. The following goals are thus achieved:

* Setting up the `CMakeLists.txt` for this project. Compiler warnings are set, and all packages are added to the executable at compile time.
* Creating an option parser in C++. This ensures that the arguments passed to your program are correctly parsed towards its existing arguments.
* Creating a client, that contacts the server (with an HTTPS request). An HTTPS GET request is made to the server. To then receive a response that contains the information about the weather.
* Decoding the HTTPS GET request from the server. You only want to have the body of that message. In addition, this body is given in JSON. This must also be parsed.
* Displaying the requested objects, which is decoded JSON format, in the standard output of the respective program.

After going through this tutorial it is therefore certain that the user knows how to create a program that can use `Boost`. You start by making all the appends in your `CMakeLists.txt`, and end up with a fully working program.
The following facilities of `Boost` are therefore used:
* boost - program options
* boost - asio
* boost - asio/ssl
* boost - property tree/json_parser
* boost - any

**An extra point:** to increase the readability of this tutorial, short 'notification' has been used at some points in code snippets with explanations, which can be recognized by `/* ~~~ ... ~~~ */ `. A notice has been given here instead of the '...'. For example, reference can be made to source files of the code, or include files.

## First step, creating your `CMakeLists.txt`

In this first step of the project, an explanation is given on how to build everything for your program. CMake is used, which ensures that all requested functions are added to your executable, so that your program can be compiled properly.

### Download the Boost library's

To make the facilities of the 'Boost' library available, you must first download it.
For example, you can use a Linux terminal for this. This is useful if you are using WSL, where you build and debugged your C++ program in Linux.

To download the 'Boost' libraries run the following `apt-get` command:
```shell
sudo apt-get install libboost-all-dev
```

After the installation of this library is complete it is ready to be used in your C++ program!

### Add everything to your executable with CMake

If your installation of the 'Boost' library was successful, unfortunately it cannot yet be used directly in your program/executable file. To make this available we use CMake. This is a multi-platform system for build automation, originally also written in C++. It is similar to the Unix `make` program, but CMake only generates standard build files.

#### The start of your `CMakeLists.txt`

In CMake, you first want to determine a number of standards, such as the version of CMake. You also name your project, in this case `WEATHER_APP`. In this case, the executable will also have this name, which is named `add_executable(TOPIC_1)`. With the help of `target_sources(...)` you can indicate which files should be compiled, and then added to your executable. For example, if you just want to add `main.cpp` this statement will look like this: `target_sources(${target} PRIVATE main.cpp)`. To add additional files in this, do this as follows: `target_sources(${target} PRIVATE main.cpp class.cpp communicate.cpp)`. Here `class.cpp` and `communicate.cpp` are new files, for example from newly created classes. If you are using separate folders for all include and source files, it is necessary to name where all include files can be found. This is done with: `include_directories(./inc)`. The folder with all *.h files is called 'inc'. You must now also name the folder of your source files within the `target_sources(...)`. In this case, this folder is 'src'.

Initially, your CMake will now look like this:

```cmake
cmake_minimum_required(VERSION 3.21) # The minimum CMake version used.
project(WEATHER_APP) # Name of the current project.

add_executable(WEATHER_APP) # Define a name for your executable.

set(target WEATHER_APP) # Create a name for your target.

# Here, you can add the files you want to add to your executable.
target_sources(${target}
        PRIVATE
        # All the files that you want to include come here, it are mostly *.cpp files. For example:
        main.cpp
        ./src/weather_json_parser.cpp # Here, all the *.cpp files are stored in a 'src' folder.
        )

include_directories(./inc) # Instruct the compiler where to look for the given header files within this project.
```

#### Trigger warnings for the compilers

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
        # Optimisation for 'Release' mode.
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Release>>:/O2>
        # Optimisation in 'Debug'.
        $<$<AND:$<CXX_COMPILER_ID:MSVC>,$<CONFIG:Debug>>:/RTC1 /Od /Zi>
        )
```

If you have become curious about the above syntax, please refer to the following [link](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html).
Generator expressions are used. Generator expressions are evaluated during build system generation to produce information specific to each build configuration.

#### Enabling the 'Address Sanitizer'

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

#### Adding 'Boost'

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
    target_link_libraries(WEATHER_APP Boost::program_options Boost::system Boost::thread) # Here, you are linking all the libraries available the 'Boost' library.
endif()
```

#### Adding 'OpenSSL'

`OpenSSL` is an open source implementation of the SSL/TLS protocol. The core library, which is written in the C programming language, implements the basic cryptographic functions and provides various auxiliary functions. This makes it possible to make various requests via HTTPS. This makes it possible to make various requests via HTTPS. This is because the application uses an HTTPS request to retrieve the data from a server over the internet.

To make the facilities of the 'OpenSSL' library available, you must first download it.
For example, you can use a Linux terminal for this. This is useful if you are using WSL, where you build and debugged your C++ program in Linux.

To download the `OpenSSL` libraries run the following `apt-get` command:
```shell
sudo apt-get install libssl-dev
```

To add these facilities to your `CMakeLists.txt`, first you just need to find the `OpenSSL` package in the `CMakeLists.txt`. This is done by calling the function `find_package(...)`. All elements of this package/library are required for this. Then you go see if this is found, to add it to your executable. This is done using `target_link_libraries(WEATHER_APP ${OPENSSL_LIBRARIES})`, remember that `OPENSSL_LIBRARIES` represents all libraries of the `OpenSSL` facility.

```cmake
find_package(OpenSSL REQUIRED) # Try to find your 'OpenSSL' package.

# Check if the 'OpenSSL' library/packages are found.
if (OpenSSL_FOUND)
    message("OpenSSL library found!") # Show a message that the 'OpenSSL' library is found.
    target_link_libraries(WEATHER_APP ${OPENSSL_LIBRARIES}) # Here, you are linking all the libraries available the 'OpenSSL' library.
endif()
```

If you see the full CMake code used to enable compiling see the [CMakeLists.txt](CMakeLists.txt).


## Second step, creating an `option_parser`

Now we can finally get our hands dirty with a piece of C++ code! We start with the basics, which should actually be given immediately when starting the program. Those are the program arguments in this case. For this we create an option parser, which parses all the arguments that are passed to your program. This is of course parsed for all elements respectively present in the written program.

### Create a separate class, with fields and a constructor

We use a class to provide various functionalities for the option parser. Use is made of the facilities that `Boost` offers for this. Here you need to include a file with `#include <boost/program_options.hpp>`. Of course, several `std` header files are also added. As a result of all fields, a constructor must also be generated for this class. This constructor has as arguments `arguments_count` and `arguments_value`. What is used to pass the program arguments of the main function. This is assigned in the constructor to its respective fields of the class. The example below gives a class along with some fields and the constructor. The comment `/* ~~~ ... ~~~ */` is accompanied by an abbreviated explanation of the code present, in order to keep the snippets short and clear.

```c++
// All the necessary include-files for this class:
#include <boost/program_options.hpp> // Include the 'Boost' facilities, in this case 'program_option.hpp'.

#include <iomanip> // Include the  'standard' facilities, in this case 'iomanip'.
#include <iostream> // Include the  'standard' facilities, in this case 'iostream'.

// This is the 'option_parser' class, which provides several methods for adding options including flags, and positional arguments. It also supports a configurable 'help' option.
class option_parser {
public:
    option_parser(int arguments_count, char* arguments_value[]); // The constructor of your class. It takes the number of arguments passed to the program, with its values. 

    /* ~~~ Here come all the other methods ~~~ */
    
private:
    boost::program_options::options_description m_options_description; // A field for all de descriptions of the options. It uses a special collection under the hood for storing all the given options.
    boost::program_options::positional_options_description m_positional_description; // A field for all de descriptions of the positional arguments. It uses a special collection under the hood for storing all the given positional arguments.
    /* ~~~ some more fields ~~~ */
    char** m_arguments_value; // Pointer to character arrays to program arguments. Yes, maybe strange, but this is the only way of writing it.
    int m_arguments_count; // The number of arguments parsed to the program.
};

/* ~~~ The constructor: ~~~ */

// The constructor of your class. It takes the number of arguments passed to the program, with its values.
option_parser::option_parser(int arguments_count, char* arguments_value[]) :
    m_options_description{}, // Default initialization.
    m_positional_description{},
    /* ~~~ some more fields ~~~ */
    m_arguments_value{arguments_value}, // Initialize this field with the values of the arguments passed to the program.
    m_arguments_count{arguments_count} // Initialize this field with the number of arguments passed to the program.
{}
```

#### Configurable help functionality

To make the application more user-friendly it is good practise to add a help functionality. This way the user knows which arguments can be passed to your program, in order to be able to display it correctly. A method is created for this called `with_help`. As arguments, you can pass the configuration of your help functionality to this. This means that it is configurable. In addition, you can also name a description for your help function.

```c++
/* ~~~ Definition of the 'with_help' method within the 'option_parser' class ~~~ */
// This is the method 'with_help' that adds a help functionality to your 'option_parser'. It is a configurable help option.
[[maybe_unused]] void with_help(const std::string& help_flag, const std::string& description);
/* ~~~ End definition of the 'with_help' method within the 'option_parser' class */

// This is the method 'with_help' that adds a help functionality to your 'option_parser'. It is a configurable help option.
void option_parser::with_help(const std::string &help_flag, const std::string &description) {
m_help_flag = help_flag; // Assign your configurable help flag to 'm_help_flag'. Used for recognition within this class when parsing the objects.

// Add your option. Convert your 'string' to a C-style character array, used for the method 'add_option'.
m_options_description.add_options()
(help_flag.c_str(), description.c_str());
}
```

#### Adding methods to the option parser

Of course, you want to add options to your option parser, which you can use if you pass arguments to your program. This is of course crucial, otherwise you cannot, for example, indicate that you only want to see the temperature. For example, you can call a certain method on this class, adding an option, with:

```c++
parser.add_flag_option("temperature,t", "prints the temperature level in degrees Celsius"); // Add a 'temperature' flag to the program.
parser.add_string_positional("country_code", "name of the country where you want to display the weather for"); // This is a positional argument for the country code.
parser.add_string_positional("city_name", "name of the city where you want to display the weather for"); // This is a positional argument for the city name.
```

Now that these methods are bound to your class, as a user you can now actually call all your program with:

```shell
$ ./WEATHER_APP --temperature NL, Amsterdam # The usage is in general [FLAGS] <COUNTRY_CODE> <CITY_NAME>.
```

Below are some implementations of options that can be added to your option parser. In this case, this is a `flag` option, along with a `string` option. With this last option you can pass an argument to the flag. In the definition of your code, you first make a complete description of your option, and then add it to your collection of options, `m_options_description`. Note that this code is about the same for an integer option, or a double option. See the [source code](src/option_parser.cpp) for all the methods for adding options.

```c++
/* ~~~ Definition of several methods within the 'option_parser' class ~~~ */
// This method adds a flag option to your 'option_parser'. A flag option does not take an argument.
[[maybe_unused]] void add_flag_option(const std::string& long_flag, const std::string& description);
// This method adds a string option to your 'option_parser'. Your option takes a string argument with it.
[[maybe_unused]] void add_string_option(const std::string& long_flag, const std::string& description);
/* ~~~ End definition of several methods within the 'option_parser' class ~~~ */

// This method adds a flag option to your 'option_parser'. A flag option does not take an argument.
[[maybe_unused]] void option_parser::add_flag_option(const std::string &long_flag, const std::string &description) {
    auto complete_description = description + " [bool]"; // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Add your option. Convert your 'string' to a C-style character array, used for the method 'add_option'.
    m_options_description.add_options()
        (long_flag.c_str(), complete_description.c_str());
}

// This method adds a string option to your 'option_parser'. Your option takes a string argument with it.
[[maybe_unused]] void option_parser::add_string_option(const std::string &long_flag, const std::string &description) {
    auto complete_description = description + " [string]"; // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Add your option. Convert your 'string' to a C-style character array, used for the method 'add_option'.
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<std::string>(), complete_description.c_str());
}
```

A particular option can also contain a default value. As a result, a flag will always be present, even if you don't pass it into your program. Again, this is only given for a `flag` option, and a `string` option. The default value for a string is self-explanatory, it is also just a string. With a `flag` option, this is a boolean, to indicate whether it is present or not. In the program it can be added with `boost::program_options::value<bool>()->default_value(default_value)` for a boolean value. You call a method on a ` ::value`. Of course, you can also add a default value for several types of options. This is pretty much the same as a string option with a default value.

```c++
/* ~~~ Definition of several methods within the 'option_parser' class ~~~ */
// This method adds a flag option to your 'option_parser'. It has a default value.
[[maybe_unused]] void add_flag_option(const std::string& long_flag, const std::string& description, bool default_value);
// This method adds a string option to your 'option_parser'. It has a default value.
[[maybe_unused]] void add_string_option(const std::string& long_flag, const std::string& description, const std::string& default_value);
/* ~~~ End definition of several methods within the 'option_parser' class ~~~ */

// This method adds a flag option to your 'option_parser'. It has a default value.
[[maybe_unused]] void option_parser::add_flag_option(const std::string &long_flag, const std::string &description, bool default_value) {
    auto complete_description = description + " [bool] - DEFAULT: " + ((default_value) ? "true" : "false"); // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Add your option. Convert your 'string' to a C-style character array, used for the method 'add_option'.
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<bool>()->default_value(default_value), complete_description.c_str()); // Here you are using a default value.
}

// This method adds a string option to your 'option_parser'. It has a default value.
[[maybe_unused]] void option_parser::add_string_option(const std::string &long_flag, const std::string &description, const std::string &default_value) {
    auto complete_description = description + " [string] - DEFAULT: " + default_value; // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Add your option. Convert your 'string' to a C-style character array, used for the method 'add_option'.
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<std::string>()->default_value(default_value), complete_description.c_str());  // Here you are using a default value.
}
```

Support for positional arguments is also provided. Positional arguments don't require a specific flag, they just use a fixed place within giving arguments to your program. Know that the user **must** pass this argument to the program.
In the example below, there is only an implementation given for a positional argument that takes a string. It does not contain a default value, which is of course also possible. It's the same as the above explanation in this tutorial, only with the fact that you now have to add it as a positional argument as well. You can also generate positional arguments for an integer, or a double. This is given in the available [source code](src/option_parser.cpp).

 ```c++
/* ~~~ Definition of a method within the 'option_parser' class ~~~ */
// This method adds a string positional argument to your 'option_parser'.
[[maybe_unused]] void add_string_positional(const std::string& long_flag, const std::string& description);
/* ~~~ End definition of a method within the 'option_parser' class ~~~ */

// This method adds a string positional argument to your 'option_parser'.
[[maybe_unused]] void option_parser::add_string_positional(const std::string &long_flag, const std::string &description) {
    auto complete_description = description + " [string]"; // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Your positional arguments is also an option, so add it as an option.
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<std::string>(), complete_description.c_str());

    m_positional_description.add(long_flag.c_str(), 1); // Add your positional argument, with only one value. Convert your 'long_flag' to a C-style character array.
    m_positional_count++; // One positional argument more, so increase it.
}
```

#### Now finally parse all options

After you have added all the necessary options and positional arguments it is time to parse your arguments passed to your program for these options/positional arguments. This is done in the `parse_arguments` method. It takes the variables passed to your program and converts them into parsed options. Positional arguments are also taken into account here. After parsing, it is checked whether you are calling a 'help' functionality, and then returned the use of the options. Finally, you now return a collection of parsed options, which can be used further in the program.

```c++
/* ~~~ Definition of a method within the 'option_parser' class ~~~ */
// This method parses all the given arguments parsed to the program.
[[nodiscard]] const boost::program_options::variables_map& parse_arguments();
/* ~~~ End definition of a method within the 'option_parser' class ~~~ */

// This method parses all the given arguments parsed to the program.
[[maybe_unused]] const boost::program_options::variables_map &option_parser::parse_arguments() {
    // A try/catch block to catch exceptions that can occur.
    try {
        // Parse all the program arguments, take also the positional arguments into account.
        boost::program_options::store(boost::program_options::command_line_parser(m_arguments_count, m_arguments_value)
            .options(m_options_description)
            .positional(m_positional_description)
            .run(), m_options_map);

        boost::program_options::notify(m_options_map); // Used for notifying, you can use the collection of parsed options.
    }
    // Used for catching exceptions, in this case 'program options' exceptions.
    catch (const boost::program_options::error&e) {
        std::cerr << "ERROR MESSAGE - PARSING PROGRAM OPTIONS NOT SUCCEEDED!" << std::endl; // Show a standard error message.
    }

    // Check if you called your 'help' functionality.
    if (m_options_map.count(m_help_flag))
        std::cout << usage_of_options() << std::endl; // Print the usage of the options.

    return m_options_map; // Return the collection of parsed options.
}
```

#### Print help diagnostics

It may seem very strange, you use `Boost` to have access to many extra functions, including these option parser facilities. But unfortunately there is no support for showing full 'help' functionality, let alone for positional arguments. For this reason we have to create a 'help' functionality ourselves, ie a string that is shown in the standard output. We will create a separate method for this called `usage_of_options`. In this method we use a string stream to write a sequence of characters. First we want to show the usage of the program when the 'help' function is called. This will look like `Usage: ./WEATHER_APP [FLAGS] <POSITIONAL ARGUMENTS>`. We use a loop to show all positional arguments, while of course we also have to check whether these arguments are actually present. Finally, of course you want to show all the options, along with all its available descriptions. This also happens in a loop, in which the positional arguments are also shown with its descriptions at the same time. Finally, the 'string stream' is transformed into a string, which is returned by the function. It has been decided not to make this function 'private', so that you can also generate this string from outside.

```c++
/* ~~~ Definition of a method within the 'option_parser' class ~~~ */
// This method generates a 'help' string when your 'help' flag is called.
[[nodiscard]] std::string usage_of_options() const;
/* ~~~ End definition of a method within the 'option_parser' class ~~~ */

// This method generates a 'help' string when your 'help' flag is called.
[[maybe_unused]] std::string option_parser::usage_of_options() const {
    std::stringstream string_stream{}; // Use a 'string stream'.
    string_stream << "Usage: ./" << program_invocation_short_name << " "; // Print the usage.

    // Check if you have flags/options:
    if (!m_options_description.options().empty()) {
        string_stream << "[FLAGS] "; // Show for the usage.

        // Check if you have positional arguments.
        if (m_positional_count) {
            for (int i = 0; i < m_positional_count; i++)
                string_stream << '<' << m_positional_description.name_for_position(i) << "> "; // Print the usage of your positional arguments.
        }

        string_stream << '\n';

        // Assign all the descriptions of your options, respectively the positional arguments.
        for (const auto& single_option : m_options_description.options()) 
            string_stream << std::quoted(single_option->long_name()) << "\t\t" << single_option->description() << std::endl; // Assign it to your 'string stream'.
    }

    return string_stream.str(); // Convert the stream of all the 'help' functionalities into a string.
}
```

#### Creating your own option parser

Now that we have added several methods to our 'option parser' it is now possible to actually construct the complete object. This means that you can create your own parser, with self-defined flags, descriptions and positional arguments. In this case we stick to what is in line with a weather application. For this we first create an instance of the class, which is: `option_parser parser{argc, argv}`. Where `argc` and `argv` are your program arguments (e.g. passed to the main function). Then you can add options that are a string, double, integer or a flag. They can have default values. Positional arguments can also be added, which of course can also have default values with a string, double or integer. Nice is not it! Have you easily made an option parser yourself with `Boost`?

```c++
/* ~~~ Option parser in some function/class/file ~~~ */

option_parser parser{argc, argv}; // Create your own option parser, assign 'argc' and 'argv' to it.

// Add options to the option parser:
parser.with_help("help_desc", "prints help description"); // The configurable 'help' functionality.
parser.add_flag_option("temperature,t", "prints the temperature level in degrees Celsius"); // Option to print the temperature.
/* ~~~ Some more options added to the option parser ~~~ */
parser.add_string_positional("country_code", "name of the country where you want to display the weather for"); // A positional argument for the country. This argument must be present within the program arguments.
parser.add_string_positional("city_name", "name of the city where you want to display the weather for"); // A positional argument for the city name. This argument must be present within the program arguments.

auto parsed_object = parser.parse_arguments(); // Parse the program option, it returns a collection of parsed objects.
```

If you take a look at all the files (code) around the option parser, that is certainly possible! In this project an option parser is created in the [main-function](main.cpp). In addition, the full option parser is created in its associated [header file](inc/option_parser.h) and [source code](src/option_parser.cpp). The code is extensively documented, making it easy to understand.

## Third step: saving all the `weather_client_info`

After all the data has been parsed, we create a wrapper to easily make the next part of the weather application. They provide several getters, but of course also a method within a class that can generate the full HTTPS request, and then contact the server to get it back.

### Create a new class, with fields and a constructor

A new class is created. This class acts as a wrapper around the information generated from all the arguments passed to your program. To ensure that various types can be stored, for example for the temperature, `boost::any` is used. The facilities for this come from `#include <boost/any.hpp>`. Our goal is that it is possible to store various types, coming from your 'option parser'.
Please note that a number of types are assumed in the further program. For example a 'city code' is assumed to be a string, which it is also cast for.
Initially, a constructor is created, to which certain types are passed. Many types are a `std::pair(...)`. The parsed program option is given as the first element of this `pair`. The second element is the abbreviation of this option that is called for when the JSON is parsed when the weather data is retrieved via the internet. After all, the web server returns a request with a JSON object.
Here is the first version of the class given:

```c++
// All the necessary include-files for this class:

#include <boost/any.hpp> // Include the 'Boost' facilities, in this case 'any.hpp'.

#include <sstream> // Include the 'standard' facilities, in this case 'sstream'.

// This is the 'weather_client_info' class, that as a wrapper cares about all parsed options. For example, you can check whether the 'temperature' should be displayed, or the humidity. You can also get the country code and city name.
// 'any' is used to make the code somewhat generic. For example, if you have an integer option as temperature, with an integer argument it can be given here. After all, it is never a problem to work with 'any'.
class weather_client_info {
public:
    // The constructor of the 'weather_client_info' class. It constructs the whole object.
    weather_client_info(std::pair<boost::any, std::string> temperature_exists,
        std::pair<boost::any, std::string> min_temp_exists,
        std::pair<boost::any, std::string> max_temp_exists,
        std::pair<boost::any, std::string> feels_like_exists,
        std::pair<boost::any, std::string> pressure_exists,
        std::pair<boost::any, std::string> humidity_exists,
        const std::string& country_code,
        const std::string& city_name);

    /* ~~~ Here come all the other methods ~~~ */

private:
    std::pair<boost::any, std::string> m_temperature_exists; // A field if your temperature exists (will be written to the standard out after retrieving the data via de webserver).
    std::pair<boost::any, std::string> m_min_temp_exists; // A field if your minimum temperature exists (will be written to the standard out after retrieving the data via de webserver).
    /* ~~~ some more fields ~~~ */
    boost::any m_country_code; // A field for the country code.
    boost::any m_city_name; // A field for the city name.
};

/* ~~~ The constructor: ~~~ */

// The constructor of the 'weather_client_info' class. It constructs the whole object.
weather_client_info::weather_client_info(std::pair<boost::any, std::string> temperature_exists, std::pair<boost::any, std::string> min_temp_exists, std::pair<boost::any, std::string> max_temp_exists, std::pair<boost::any, std::string> feels_like_exists,std::pair<boost::any, std::string> pressure_exists, std::pair<boost::any, std::string> humidity_exists, const std::string &country_code, const std::string &city_name) :
    // Where 'std::move(...)' is used, the ownership is moved.
    m_temperature_exists{std::move(temperature_exists)},
    m_min_temp_exists{std::move(min_temp_exists)},
    /* ~~~ some more fields ~~~ */
    m_country_code{country_code},
    m_city_name{city_name}
{}
```

#### Implementing getter methods

This class contains several getters, which are supported by the weather application. For example a getter, to return the `std::pair(...)` for e.g. temperature, minimum temperature and humidity. In addition, getters are also given for a country's code, along with the name of the city for which it is displayed.

So a `std::pair(...)` contains the parse option, for example a flag option, and as the second element it contains a string which is seen as a recognition within the JSON object that is returned when the web server is contacted . This is used while parsing this JSON object. For example, the 'temperature' flag here has the abbreviation 'temp'.

The getters are easy to implement, you create a method that returns only a particular field of your class. It is important that this is a constant method. Thus, the data of the object that is returned cannot be modified. For example, the signature of this function could be: `const std::pair<boost::any, std::string>& get_exists_temperature() const`. A constant reference is also returned, so that the data cannot be changed at all!

```c++
/* ~~~ Definition of several methods within the 'weather_client_info' class ~~~ */
// This method returns a constant reference to your pair of your option, along with the recognition in the JSON object, e.g. 'temp'.
[[nodiscard]] const std::pair<boost::any, std::string>& get_exists_temperature() const;
// This method returns a constant reference to your pair of your option, along with the recognition in the JSON object, e.g. 'temp_min'.
[[nodiscard]] const std::pair<boost::any, std::string>& get_exists_min_temperature() const;
/* ~~~ End definition of several methods within the 'weather_client_info' class ~~~ */

// This class returns a constant reference to your pair of your option, along with the recognition in the JSON object, e.g. 'temp'.
const std::pair<boost::any, std::string> &weather_client_info::get_exists_temperature() const {
    return m_temperature_exists;
}

// This class returns a constant reference to your pair of your option, along with the recognition in the JSON object, e.g. 'temp_min'.
const std::pair<boost::any, std::string> &weather_client_info::get_exists_min_temperature() const {
    return m_min_temp_exists;
}
```

#### Create an HTTPS request

We want to contact a web server that returns a response containing the body of a JSON object. This JSON object will contain all the necessary information for which it can be displayed again.
But to be able to contact the server we have to use an HTTP request. In this request will be given the URL of the server containing the country code and the name of the city (for which the weather is shown of course). In addition, it also has an API key, and other information. The request sent to the server looks like this:

```http request
GET /data/2.5/weather?q=NL,Amsterdam&appid={API_KEY} HTTP/1.1
Host: api.openweathermap.org
Connection: close
```

To make it easy, we have created a method that generates this request. You do have to provide the relevant hostname of the server, the URL (which must contain the code of the country and name of the city) and the API key. Ultimately, this entire request will be returned on this basis. This method looks like this:To make it easy, we have created a method that generates this request. You do have to provide the relevant hostname of the server, the URL (which must contain the code of the country and name of the city) and the API key. Ultimately, this entire request will be returned on this basis. This method looks like this:

```c++
/* ~~~ Definition of a method within the 'weather_client_info' class ~~~ */
// This method generates an HTTPS request for which it must be shown again.
[[nodiscard]] std::string generate_http_weather_request(const std::string& host_name, const std::string& url_path, const std::string& api_key) const;
/* ~~~ End definition of a method within the 'weather_client_info' class ~~~ */

// This method generates an HTTPS request for which it must be shown again.
std::string weather_client_info::generate_http_weather_request(const std::string &host_name, const std::string &url_path, const std::string &api_key) const {
    std::stringstream string_stream{}; // Use a 'string stream'.

    // Generate the HTTPS request. Here, we apply a cast for the 'any' type. In our application, we assume that a city name is always a string, with so your country code.
    string_stream << "GET " << url_path << boost::any_cast<std::string>(m_city_name) << "," << boost::any_cast<std::string>(m_country_code) << "&appid=" << api_key << " HTTP/1.1\n";
    string_stream << "Host: " << host_name << '\n';
    string_stream << "Connection: close\n\n";

    return string_stream.str(); // Convert the stream of all the HTTPS request into a string.
}
```

#### Creating an instance of this class

Creating an instance of the class is very simple. However, you should note that in this case we make a Boolean comparison for each argument that is passed because the constructor is called. So you see that for all options we only check whether they are present or not. So it is a Boolean value. We only give a string for the country code and city name. We also check whether you have actually passed this data to the program as arguments. If not, an empty string is used. A call we use within our weather application looks like this:

```c++
/* ~~~ Creating an instance in some function/class/file ~~~ */

weather_client_info data{
    {parsed_object.count("temperature") != 0, "temp"},
    {parsed_object.count("min_temperature") != 0, "temp_min"},
    {parsed_object.count("max_temperature") != 0, "temp_max"},
    {parsed_object.count("feels_like") != 0, "feels_like"},
    {parsed_object.count("pressure") != 0, "pressure"},
    {parsed_object.count("humidity") != 0, "humidity"},
    parsed_object.count("country_code") ? parsed_object["country_code"].as<std::string>() : "",
    parsed_object.count("city_name") ? parsed_object["city_name"].as<std::string>() : ""
};
```

## Fourth step: retrieving the weather data in `weather_json_info`

Now comes the heart of the application: retrieving the weather data from the web server (in our case openweathermap). This is done via an HTTPS request. `Boost` offers some great facilities for this which are offered in `#include <boost/asio.hpp>` and `#include <boost/asio/ssl.hpp>`. Whereby a secure HTTPS connection can be easily made with the web server. Finally, the response of this request is also parsed with `#include <boost/beast.hpp>`, to get only the body with the weather data encoded in JSON.

### Create a new class, with fields and a constructor

The class 'weather_data_json' gets in its constructor the data of a client, given in the type `weather_client_info`. In addition, the hostname of the server is given, the URL and of course the API key. In our application we contact the service of 'openweathermap'. Your class will initially look like this:

```c++
// All the necessary include-files for this class:

#include <boost/asio.hpp> // Include the 'Boost' facilities, in this case 'asio.hpp'.
#include <boost/asio/ssl.hpp> // Include the 'Boost' facilities, in this case 'asio - ssl.hpp'.
#include <boost/beast.hpp> // Include the 'Boost' facilities, in this case 'beast'.

#include <iostream> // Include the 'standard' facilities, in this case 'iostream'.

#include "weather_client_info.h" // Include the 'weather_json_parser' facilities.

// This is the 'weather_data_json' class. This class is given this name because it really only serves the purpose of returning a JSON message from the web server that supplies it.
// It contacts the server by performing a handshake, and then actually gets the data in the form of a JSON format.
class weather_data_json {
public:
    // The constructor of the 'weather_data_json' class. It constructs the whole object.
    weather_data_json(weather_client_info client_info, std::string host_name, std::string host_url, std::string api_key);

    /* ~~~ Here come all the other methods ~~~ */
    
private:
    weather_client_info m_client_data; // This field contains the data of your client.

    std::string m_host_name_weather_app; // This field represents the hostname of the weather app. In this case 'openweathermap'.
    std::string m_host_url; // This field contains the URL.
    std::string m_api_key_weather_app; // This field contains the API key.
};

/* ~~~ The constructor: ~~~ */

// The constructor of the 'weather_data_json' class. It constructs the whole object.
weather_data_json::weather_data_json(weather_client_info client_info, std::string host_name, std::string host_url, std::string api_key) :
    // Where 'std::move(...)' is used, the ownership is moved.
    m_client_data{std::move(client_info)},
    m_host_name_weather_app{std::move(host_name)},
    m_host_url{std::move(host_url)},
    m_api_key_weather_app{std::move(api_key)}
{}
```

#### Returning the JSON data

Now we come to the real muscles of `Boost`! Let's start networking in C++! The standard facilities of C++ provide [none](https://quuxplusone.github.io/blog/2019/10/09/why-no-networking/) for this. First, the example below is slightly shortened, for the full code, see the [source code](src/weather_data_json.cpp).

We first want to obtain the IP address of the web server. Based on this, a secure connection can be created in order to send the data over it. This is done with the following: `auto endpoint_of_server = resolver_ip_address.resolve(m_host_name_weather_app, std::to_string(PORT_VALUE_HTTPS))`. The variable `endpoint_of_server` here contains an object containing the actual IP address of the server.
After this, the actual connection to the server is established. A handshake takes place to verify that the security considerations match.
Now the actual request is sent, followed by a response.
You only need the body of this HTTP response, in which the weather data is given in JSON format. This is parsed with a special parser, from which you only request the body of this request: `response_parser.release().body()`.

```c++
/* ~~~ Definition of a method within the 'weather_data_json' class ~~~ */
// This method is the heart of the application. It contacts the webserver, that returns the JSON object with weather data. It also parses the HTTP request from the webserver.
[[nodiscard]] std::string retrieve_weather_json() const;
/* ~~~ End definition of a method within the 'weather_data_json' class ~~~ */

// This method is the heart of the application. It contacts the webserver, that returns the JSON object with weather data. It also parses the HTTP request from the webserver.
std::string weather_data_json::retrieve_weather_json() const {
    std::string response_message{}; // A string where the response message will be stored.

    // A try/catch block to catch exceptions that can occur.
    try {
        boost::asio::io_context io_context_data; // The context data for the I/O.
        boost::asio::ssl::context ssl_context_data(boost::asio::ssl::context::tls); // The context data used for SSL. Its type is TLS (Transport Layer Security).
        boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_application(io_context_data, ssl_context_data); // Create a socket, whereby the underlying layer TCP is. This internet protocol ensures that all sent packets arrive at the server. It is a connection oriented socket.

        /* ~~~ Some more code here... Please take a look at this method within 'weather_data_json.cpp'. ~~~ */
        
        // Try to parse the whole HTTPS message from the server, because you only want the body of this message:
        boost::beast::http::parser<false, boost::beast::http::string_body> response_parser;
        response_parser.eager(true); // Used for directly getting the body of the HTTPS request.
        response_parser.put(boost::asio::buffer(response.data()), error_code); // Here, you are parsing the HTTPS request.

        response_message = response_parser.release().body(); // Retrieve the body from the parser.
    }
    // Used for catching exceptions, in this case all exceptions that can occur.
    catch (const std::exception&) {
        std::cerr << "ERROR MESSAGE - CREATING A CONNECTION WITH THE INTERNET SERVICE NOT SUCCEEDED!" << std::endl; // Show a standard error message.
    }

    return response_message; // Return the body of the response, this is encoded in JSON format. Empty string if retrieving the weather data failed.
}
```

Finally! We now have some weather data! But unfortunately we're not there yet... The weather data is given in JSON, which needs to be parsed. This is done in the next and last section of this tutorial.

## Final step: parsing the JSON object in `weather_json_parser`

We are now going to create a JSON parser, to show all the requested information to the user. We create a class, containing a method that parses the obtained body of the web server, to show, for example, only the temperature and air pressure. All information is written to the standard out.

### Create a new class, with fields and a constructor

The last part of our weather application: parsing the JSON object that contains all the weather data. We will also create a class for this, called `weather_json_parser`. This class has as field the data of the client, `weather_client_info`. Note that this class also contains information from the client, in the form of the arguments passed to the program. This way you know whether you should show the temperature with the minimum temperature, other combinations are also possible. This depends on the arguments passed to the program.
To parse the JSON, the following include is used: `#include <boost/property_tree/json_parser.hpp>`. You can see that the `json_parser` underwater uses a `property_tree`.
Based on this you can very easily get objects from the JSON object with weather data.
The class will initially look like this:

```c++
// All the necessary include-files for this class:

#include <boost/program_options.hpp> // Include the 'Boost' facilities, in this case 'program_options.hpp'.
#include <boost/property_tree/json_parser.hpp> // Include the 'Boost' facilities, in this case 'property_tree - json_parser.hpp'.
#include <boost/any.hpp> // Include the 'Boost' facilities, in this case 'any.hpp'.

#include <sstream> // Include the 'standard' facilities, in this case 'sstream'.
#include <iostream> // Include the 'standard' facilities, in this case 'iostream'.

#include "weather_client_info.h" // Include the 'weather_client_info' facilities.

#define TEMP_DEGREES_DECR (273) // Definition of the decrease to go from degrees Kelvin to degrees Celsius.

// This is the 'weather_json_parser' class. It gets a string (which is given in JSON format). It is then decoded using 'Boost', to which the requested information is shown in the standard out.
// The information is displayed by means of the options parsed with the 'option parser'. For example, if you passed '--temperature' the temperature will be shown, after it has of course been parsed with a JSON parser.
class weather_json_parser {
public:
    // The constructor of the 'weather_json_parser' class. It constructs the whole object.
    explicit weather_json_parser(weather_client_info client_info);

    /* ~~~ Here come all the other methods ~~~ */
    
private:
    weather_client_info m_client_data; // This field contains the data of your client.
};

/* ~~~ The constructor: ~~~ */

// The constructor of the 'weather_json_parser' class. It constructs the whole object.
weather_json_parser::weather_json_parser(weather_client_info client_info) :
    // Where 'std::move(...)' is used, the ownership is moved.
    m_client_data{std::move(client_info)}
{}
```

#### Let's print the data

Everything is starting to fall into place, and the last step remains for us to show the requested data to the user. This is done in the `print_required_json` method. You pass your JSON object with weather data. Then you create a 'string stream', to which you pass this given string. This will be used by `Boost` JSON parser.
To parse the data you must first create a data structure called a `boost::property_tree::ptree`. You can now provide your 'string stream', along with this data structure, for which your JSON will be parsed. This is done with: `boost::property_tree::read_json(...)`.
Now you can look up elements in the data structure, which contains the JSON objects that have been parsed. This is done for example for the temperature with: `prop_tree.get<double>("main.temp")`. Make sure that your `main.temp` here matches the fields in the original JSON format passed to this method.

For example, to see if you have passed a `--temperature` flag to the program, an if statement is checked. You do this by looking in the data of `m_client_data`, and the first element of this `std::pair` which is returned. If it is present, and the evaluation in this if statement is true, the information will be displayed.

An earlier code snippet in this tutorial explained that we use boolean values to indicate whether a flag is present or not. This is done for example with `parsed_object.count("temperature") != 0`. Because this returns a boolean value, it also tries to cast to a boolean, in order to print the data.

You also want to convert degrees Kelvin to degrees Celsius before it is written to the standard out, if you are dealing with temperature.

```c++
/* ~~~ Definition of a method within the 'weather_json_parser' class ~~~ */
// This method converts the JSON format, and displays this information in the standard output. What is displayed is indicated by means of arguments that can be passed to the program.
void print_required_json(const std::string& json_message) const;
/* ~~~ End definition of a method within the 'weather_json_parser' class ~~~ */

// This method converts the JSON format, and displays this information in the standard output. What is displayed is indicated by means of arguments that can be passed to the program.
void weather_json_parser::print_required_json(const std::string &json_message) const {
    // A try/catch block to catch exceptions that can occur.
    try {
        std::stringstream string_stream{json_message}; // This 'string stream' will be used by the JSON parser.

        boost::property_tree::ptree prop_tree{}; // This data structure is used by the JSON parser, it is called a 'property_tree'.
        boost::property_tree::read_json(string_stream, prop_tree); // Read the 'string stream', and parse it to JSON (individual objects within this specific JSON format).

        auto country_code = boost::any_cast<std::string>(m_client_data.get_country_code()); // Retrieve the country code.
        auto city_name = boost::any_cast<std::string>(m_client_data.get_city_name()); // Retrieve the city name.

        // Show where the weather is displayed for:
        std::cout << "WEATHER FOR: "
            << (!country_code.empty() ? country_code : "NO COUNTRY CODE PROVIDED") // Check if the country code is not an empty string. If it is an empty string, no country code was provided within the arguments passed to your program.
            << ", "
            << (!city_name.empty() ? city_name : "NO CITY NAME PROVIDED") // Check if the city name is not an empty string. If it is an empty string, no city name was provided within the arguments passed to your program.
            << std::endl;

        // Check if the temperature flag passed to the program. If so, print the temperature.
        if (boost::any_cast<bool>(m_client_data.get_exists_temperature().first))
            std::cout << "TEMPERATURE: " << (prop_tree.get<double>("main." + m_client_data.get_exists_temperature().second) - TEMP_DEGREES_DECR) << " °C" << std::endl;

        // Check if the minimum temperature flag passed to the program. If so, print the minimum temperature.
        if (boost::any_cast<bool>(m_client_data.get_exists_min_temperature().first))
            std::cout << "MINIMUM TEMPERATURE: " << (prop_tree.get<double>("main." + m_client_data.get_exists_min_temperature().second) - TEMP_DEGREES_DECR) << " °C" << std::endl;

        /* ~~~ Some more checks are here, please check the 'weather_json_parser.cpp' file for all the checks for printing objects. ~~~ */
        
        // Check if the humidity flag passed to the program. If so, print the humidity.
        if (boost::any_cast<bool>(m_client_data.get_exists_humidity().first))
            std::cout << "HUMIDITY: " << prop_tree.get<double>("main." + m_client_data.get_exists_humidity().second) << "%" << std::endl;
    }
    // Used for catching exceptions, in this case all exceptions that can occur.
    catch (const std::exception&) {
        std::cerr << "ERROR MESSAGE - PARSING TO SPECIFIC OBJECTS NOT SUCCEEDED!" << std::endl; // Show a standard error message.
    }
}
```

## Congratulations 🎉!

Congratulations! We did it! We have generated a weather application! Time to test it now, but of course you must have a valid API key. You can get one for free from [OpenWeatherMap](https://openweathermap.org/api). If you are still unsure about the code you have just written? Feel free to check all include files and source files again. These are also equipped with extensive commentary. And, do you already know how warm it is in your hometown?

## What we have learned

We have created an advanced application, using an advanced topic, `Boost`. Looking back at this tutorial, we used the following parts of `Boost`:
* boost - program options, in combination with boost - any.
* boost - asio, in combination with: boost - asio/ssl
* boost - property tree/json_parser, in combination with boost - any.
* boost - beast

To also evaluate your general C++ knowledge, the objects used in this program are also named at a 'higher' level:
* Parsing arguments passed to the main function. Next, we learned how to take action on arguments parsed by a parser.
* We learned how to contact a web server in C++. Normally these functionalities are not provided in the `std` namespace.
* We learned something from data networks, namely how to make an HTTP/HTTPS request at a low level. For example, getting an IP address from a server, opening a socket with TCP connection. After doing 'handshakes' you eventually get the actual data.
* You learned how to parse an HTTP request to get the body of this message.
* We know how to work with JSON, and how to parse it. You also now know how to get elements from the data structure, called a `property_tree`. Your request must match exactly what is written in JSON.
* Not exactly a C++ skill, but very important to be able to compile your C++ program properly: you now know how extensive all warnings and extra functionalities can be added in your `CMakeLists.txt`. You probably won't forget how to find packages either.

## What the writers learned

While generating the code, along with this tutorial, the authors also gained a lot of experience. There was experience with networking within C#, but within C++, in combination this is definitely taken to another level. In C# you can contact this web server from 'OpenWeatherMap', and parse the information in three lines in total. This looks like this:

```cs
using var client = new HttpClient // New 'HttpClient'.
var streamTask = client.GetStreamAsync($"https://api.openweathermap.org/data/2.5/weather?q={_data.City}&appid={API_KEY}"); 
var weatherData = await JsonSerializer.DeserializeAsync<WeatherData>(await streamTask);
```

Unfortunately this doesn't work in C++... The web server of 'OpenWeatherMap' has to be contacted in a low level way, just to get a message at all. Your HTTP request has not even been parsed yet, or processed within JSON.

The study on `Boost` has given us an advanced overview of what secret functions C++ can offer when you use `Boost`.

Although `Boost` is a very difficult topic, with little documentation we hope that we have excited the reader with this tutorial to get started with C++, in combination with CMake, if not with `Boost`. It offers many beautiful functionalities for which you can create a simple yet impressive application.