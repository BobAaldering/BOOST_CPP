#include <iostream>

#include "option_parser.h"
#include "weather_client_info.h"
#include "weather_data_json.h"
#include "weather_json_parser.h"

int main(int argc, char* argv[]) {
    option_parser parser{argc, argv};

    parser.with_help("help_desc,d", "prints help description");
    parser.add_flag_option("temperature,t", "prints the temperature level in degrees Celsius");
    parser.add_flag_option("min_temperature,l", "prints the minimum temperature");
    parser.add_flag_option("max_temperature,h", "prints the maximum temperature");
    parser.add_flag_option("feels_like,f", "prints shows the temperature as it feels to humans");
    parser.add_flag_option("pressure,p", "prints the barometric pressure level");
    parser.add_flag_option("humidity,v", "prints the humidity level");
    parser.add_string_positional("country_code", "name of the country where you want to display the weather for");
    parser.add_string_positional("city_name", "name of the city where you want to display the weather for");

    auto parsed_object = parser.parse_arguments();

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

    weather_data_json json_object{data, "api.openweathermap.org", "/data/2.5/weather?q=", "19733fe7cf4a691b3fba8b1a8cffb44b"};

    weather_json_parser json_parser{data};

    json_parser.print_required_json(json_object.retrieve_weather_json());

    return 0;
}