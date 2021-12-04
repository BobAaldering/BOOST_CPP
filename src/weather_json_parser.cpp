#include "weather_json_parser.h"

// The constructor of the 'weather_json_parser' class. It constructs the whole object.
weather_json_parser::weather_json_parser(weather_client_info client_info) :
    // Where 'std::move(...)' is used, the ownership is moved.
    m_client_data{std::move(client_info)}
{}

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

        // Check if the maximum temperature flag passed to the program. If so, print the maximum temperature.
        if (boost::any_cast<bool>(m_client_data.get_exists_max_temperature().first))
            std::cout << "MAXIMUM TEMPERATURE: " << (prop_tree.get<double>("main." + m_client_data.get_exists_max_temperature().second) - TEMP_DEGREES_DECR) << " °C" << std::endl;

        // Check if the 'feels like' temperature flag passed to the program. If so, print the 'feels like' temperature.
        if (boost::any_cast<bool>(m_client_data.get_exists_feels_like().first))
            std::cout << "FEELS LIKE: " << (prop_tree.get<double>("main." + m_client_data.get_exists_feels_like().second) - TEMP_DEGREES_DECR) << " °C" << std::endl;

        // Check if the pressure flag passed to the program. If so, print the pressure.
        if (boost::any_cast<bool>(m_client_data.get_exists_pressure().first))
            std::cout << "PRESSURE: " << prop_tree.get<double>("main." + m_client_data.get_exists_pressure().second) << " hPa" << std::endl;

        // Check if the humidity flag passed to the program. If so, print the humidity.
        if (boost::any_cast<bool>(m_client_data.get_exists_humidity().first))
            std::cout << "HUMIDITY: " << prop_tree.get<double>("main." + m_client_data.get_exists_humidity().second) << "%" << std::endl;
    }
    // Used for catching exceptions, in this case all exceptions that can occur.
    catch (const std::exception&) {
        std::cerr << "ERROR MESSAGE - PARSING TO SPECIFIC OBJECTS NOT SUCCEEDED!" << std::endl; // Show a standard error message.
    }
}
