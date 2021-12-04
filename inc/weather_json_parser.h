#ifndef WEATHER_APP_WEATHER_JSON_PARSER_H
#define WEATHER_APP_WEATHER_JSON_PARSER_H

#include <boost/program_options.hpp> // Include the 'Boost' facilities, in this case 'program_options.hpp'.
#include <boost/property_tree/json_parser.hpp> // Include the 'Boost' facilities, in this case 'property_tree - json_parser.hpp'.
#include <boost/any.hpp> // Include the 'Boost' facilities, in this case 'any.hpp'.

#include <sstream> // Include the 'standard' facilities, in this case 'sstream'.
#include <iostream> // Include the 'standard' facilities, in this case 'iostream'.

#include "weather_client_info.h" // Include the 'weather_client_info' facilities.

#define TEMP_DEGREES_DECR (273) // Definition of the decrease to go from degrees Kelvin to degrees Celsius.

/// This is the 'weather_json_parser' class. It gets a string (which is given in JSON format). It is then decoded using 'Boost', to which the requested information is shown in the standard out.
/// The information is displayed by means of the options parsed with the 'option parser'. For example, if you passed '--temperature' the temperature will be shown, after it has of course been parsed with a JSON parser.
class weather_json_parser {
public:
    /// The constructor of the 'weather_json_parser' class. It constructs the whole object.
    /// \param client_info The object that represents the info of your client. It also contains the flags/options parsed by the option parser.
    explicit weather_json_parser(weather_client_info client_info);

    /// This method converts the JSON format, and displays this information in the standard output. What is displayed is indicated by means of arguments that can be passed to the program.
    /// \param json_message The JSON object that contains all the weather information (obtained from the 'openweathermap' web server).
    void print_required_json(const std::string& json_message) const;

private:
    weather_client_info m_client_data; // This field contains the data of your client.
};

#endif