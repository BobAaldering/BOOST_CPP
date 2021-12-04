#include <iostream> // Include the 'standard' facilities, in this case 'iostream'.

#include "option_parser.h" // Include the 'option_parser' facilities.
#include "weather_client_info.h" // Include the 'weather_client_info' facilities.
#include "weather_data_json.h" // Include the 'weather_data_json' facilities.
#include "weather_json_parser.h" // Include the 'weather_json_parser' facilities.

// The main-function, here 'argc' and 'argv' are used for the program arguments passed to the program.
int main(int argc, char* argv[]) {
    option_parser parser{argc, argv}; // Create your own option parser, assign 'argc' and 'argv' to it.

    // Add options to the option parser:
    parser.with_help("help_desc", "prints help description"); // The configurable 'help' functionality.
    parser.add_flag_option("temperature,t", "prints the temperature level in degrees Celsius"); // Option to print the temperature.
    parser.add_flag_option("min_temperature,l", "prints the minimum temperature"); // Option to print the minimum temperature.
    parser.add_flag_option("max_temperature,h", "prints the maximum temperature"); // Option to print the maximum temperature.
    parser.add_flag_option("feels_like,f", "prints shows the temperature as it feels to humans"); // Option to print the 'feels like' temperature.
    parser.add_flag_option("pressure,p", "prints the barometric pressure level"); // Option to print the pressure in 'hPa'.
    parser.add_flag_option("humidity,v", "prints the humidity level"); // Option to print the percentage of the humidity.
    parser.add_string_positional("country_code", "name of the country where you want to display the weather for"); // A positional argument for the country. This argument must be present within the program arguments.
    parser.add_string_positional("city_name", "name of the city where you want to display the weather for"); // A positional argument for the city name. This argument must be present within the program arguments.

    auto parsed_object = parser.parse_arguments(); // Parse the program option, it returns a collection of parsed objects.

    // Pay attention! We use a boolean value to identify whether a particular option is present. This for this '... != 0'. Use a string for the country code and city name. This can be an empty string, if these arguments are not passed to the program.
    weather_client_info data{
        {parsed_object.count("temperature") != 0, "temp"}, // Find the temperature in the collection of parsed options. Also define the string that will be searched for in the JSON object that the web server returns after requesting the weather.
        {parsed_object.count("min_temperature") != 0, "temp_min"}, // Find the minimum temperature in the collection of parsed options. Also define the string that will be searched for in the JSON object that the web server returns after requesting the weather.
        {parsed_object.count("max_temperature") != 0, "temp_max"}, // Find the maximum temperature in the collection of parsed options. Also define the string that will be searched for in the JSON object that the web server returns after requesting the weather.
        {parsed_object.count("feels_like") != 0, "feels_like"}, // Find the 'feels like' temperature in the collection of parsed options. Also define the string that will be searched for in the JSON object that the web server returns after requesting the weather.
        {parsed_object.count("pressure") != 0, "pressure"}, // Find the pressure in the collection of parsed options. Also define the string that will be searched for in the JSON object that the web server returns after requesting the weather.
        {parsed_object.count("humidity") != 0, "humidity"}, // Find the humidity in the collection of parsed options. Also define the string that will be searched for in the JSON object that the web server returns after requesting the weather.
        parsed_object.count("country_code") ? parsed_object["country_code"].as<std::string>() : "", // Your country code, as you see, we are using a simple string for representing the country code.
        parsed_object.count("city_name") ? parsed_object["city_name"].as<std::string>() : "" // Your city name, as you see, we are using a simple string for representing the city name.
    };

    weather_data_json json_object{data, "api.openweathermap.org", "/data/2.5/weather?q=", "19733fe7cf4a691b3fba8b1a8cffb44b"}; // Create an instance for retrieving th JSON data.

    weather_json_parser json_parser{data}; // Parse the given data.

    json_parser.print_required_json(json_object.retrieve_weather_json()); // Print the requested data by calling this method on 'json_parser'.

    return 0;
}