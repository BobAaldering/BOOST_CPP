#include <iostream>

#include "option_parser.h"
#include "weather_client_info.h"
#include "weather_data_json.h"

int main(int argc, char* argv[]) {
    option_parser parser{argc, argv};

    parser.with_help("help_desc", "prints help description");
    parser.add_flag_option("temperature", "prints the temperature level in degrees Celsius", true);
    parser.add_flag_option("pressure", "prints the barometric pressure level");
    parser.add_flag_option("humidity", "prints the humidity level");
    parser.add_string_positional("country_code", "name of the country where you want to display the weather for");
    parser.add_string_positional("city_name", "name of the city where you want to display the weather for");

    auto parsed_object = parser.parse_arguments();

    weather_client_info data{
        parsed_object["temperature"].as<bool>(),
        parsed_object["pressure"].as<bool>(),
        parsed_object["humidity"].as<bool>(),
        parsed_object["country_code"].as<std::string>(),
        parsed_object["city_name"].as<std::string>()
    };

    weather_data_json json_object{};

    json_object.run();

    return 0;
}