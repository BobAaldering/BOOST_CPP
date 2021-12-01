#include "weather_json_parser.h"

weather_json_parser::weather_json_parser(weather_client_info client_info) :
    m_client_data{std::move(client_info)}
{}

void weather_json_parser::print_required_json(const std::string &json_message) const {
    try {
        std::stringstream string_stream{json_message};

        boost::property_tree::ptree prop_tree{};
        boost::property_tree::read_json(string_stream, prop_tree);

        std::cout << "WEATHER FOR: "
            << boost::any_cast<std::string>(m_client_data.get_country_code())
            << ", "
            << boost::any_cast<std::string>(m_client_data.get_city_name()) << std::endl;

        if (boost::any_cast<bool>(m_client_data.get_exists_temperature().first))
            std::cout << "TEMPERATURE: " << (prop_tree.get<double>("main." + m_client_data.get_exists_temperature().second) - TEMP_DEGREES_DECR) << " °C" << std::endl;

        if (boost::any_cast<bool>(m_client_data.get_exists_min_temperature().first))
            std::cout << "MINIMUM TEMPERATURE: " << (prop_tree.get<double>("main." + m_client_data.get_exists_min_temperature().second) - TEMP_DEGREES_DECR) << " °C" << std::endl;

        if (boost::any_cast<bool>(m_client_data.get_exists_max_temperature().first))
            std::cout << "MAXIMUM TEMPERATURE: " << (prop_tree.get<double>("main." + m_client_data.get_exists_max_temperature().second) - TEMP_DEGREES_DECR) << " °C" << std::endl;

        if (boost::any_cast<bool>(m_client_data.get_exists_feels_like().first))
            std::cout << "FEELS LIKE: " << (prop_tree.get<double>("main." + m_client_data.get_exists_feels_like().second) - TEMP_DEGREES_DECR) << " °C" << std::endl;

        if (boost::any_cast<bool>(m_client_data.get_exists_pressure().first))
            std::cout << "PRESSURE: " << prop_tree.get<double>("main." + m_client_data.get_exists_pressure().second) << " hPa" << std::endl;

        if (boost::any_cast<bool>(m_client_data.get_exists_humidity().first))
            std::cout << "HUMIDITY: " << prop_tree.get<double>("main." + m_client_data.get_exists_humidity().second) << "%" << std::endl;
    }
    catch (const std::exception&) {
        std::cerr << "ERROR MESSAGE - PARSING TO SPECIFIC OBJECTS NOT SUCCEEDED!" << std::endl;
    }
}
