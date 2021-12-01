# Boost your C++!

Sometimes the `std` facilities are not sufficient in your C++ program. You want to have access to certain functions that are not available at all in the `std` namespace. However, these are often available in one of the many `Boost` libraries! So don't hesitate, and go through the tutorial that shows you how to install these libraries, and then actually write a program with various `Boost` facilities.

## Tutorial

To give an introduction to the `Boost` libraries, a [tutorial](TUTORIAL.md) has been generated for this. This tutorial first shows you how to install all libraries via your command line. After that, an explanation will be given on how to set up your `CMakeLists.txt`.
An explanation is also given how `Boost` actually works. Finally, working pieces of code are also given, in which various facilities of this library are implemented.

## Additional information

This repository has been developed for a specific subject for [Saxion University of Applied Sciences](https://www.saxion.edu), department [Applied Computer Science](https://www.saxion.edu/programmes/bachelor/applied-computer-science). This course is 'Advanced Programming Concepts', which required further investigation of a particular topic. Obviously, this topic is `Boost`.
This course requires a short presentation covering the main topics of this subject. In addition, a [tutorial](TUTORIAL.md) had to be generated as well. This file is written in this way, just like you learn a new programming language, for example. In addition, a number of experiences/learning processes will also be given. This has obviously taken place while generating all the necessary information to learn more about the advanced concept called `Boost`.

## How the program works

For this assignment it was decided to deliver a fully working application, making use of various `Boost` facilities. The application retrieves it again. A number of arguments must be given to the program, together with the code of the country concerned and the place. The correct information is then shown to the program on the basis of the flags provided.

An example of how the program in question works:
```shell
$ Usage: ./WEATHER_APP [FLAGS] <country_code> <city_name>
"help_desc"             prints help description
"temperature"           prints the temperature level in degrees Celsius [bool]
"min_temperature"       prints the minimum temperature [bool]
"max_temperature"       prints the maximum temperature [bool]
"feels_like"            prints shows the temperature as it feels to humans [bool]
"pressure"              prints the barometric pressure level [bool]
"humidity"              prints the humidity level [bool]
"country_code"          name of the country where you want to display the weather for [string]
"city_name"             name of the city where you want to display the weather for [string]

$ ./WEAHTER_APP -t -l -h --humidity NL Enschede
WEATHER FOR: NL, Enschede
TEMPERATURE: 5.43 °C
MINIMUM TEMPERATURE: 4.31 °C
MAXIMUM TEMPERATURE: 6.16 °C
HUMIDITY: 76%

$ ./WEAHTER_APP -t NL AMSTERDAM
WEATHER FOR: NL, Amsterdam
TEMPERATURE: 6.28 °C
```

You can see within this repository that various `Boost` facilities are being used, by delivering an actual working application that displays the weather. For example, use is made of 'networking' within C++, which is normally not possible at all! Handy, though, an extra extension of libraries, instead of the often simple `std` facilities.