#include "weather_client_info.h"

// The constructor of the 'weather_client_info' class. It constructs the whole object.
weather_client_info::weather_client_info(std::pair<boost::any, std::string> temperature_exists, std::pair<boost::any, std::string> min_temp_exists, std::pair<boost::any, std::string> max_temp_exists, std::pair<boost::any, std::string> feels_like_exists,std::pair<boost::any, std::string> pressure_exists, std::pair<boost::any, std::string> humidity_exists, const std::string &country_code, const std::string &city_name) :
    // Where 'std::move(...)' is used, the ownership is moved.
    m_temperature_exists{std::move(temperature_exists)},
    m_min_temp_exists{std::move(min_temp_exists)},
    m_max_temp_exists{std::move(max_temp_exists)},
    m_feels_like_exists{std::move(feels_like_exists)},
    m_pressure_exists{std::move(pressure_exists)},
    m_humidity_exists{std::move(humidity_exists)},
    m_country_code{country_code},
    m_city_name{city_name}
{}

// This method returns a constant reference to your pair of your option, along with the recognition in the JSON object, e.g. 'temp'.
const std::pair<boost::any, std::string> &weather_client_info::get_exists_temperature() const {
    return m_temperature_exists;
}

// This method returns a constant reference to your pair of your option, along with the recognition in the JSON object, e.g. 'temp_min'.
const std::pair<boost::any, std::string> &weather_client_info::get_exists_min_temperature() const {
    return m_min_temp_exists;
}

// This method returns a constant reference to your pair of your option, along with the recognition in the JSON object, e.g. 'temp_max'.
const std::pair<boost::any, std::string> &weather_client_info::get_exists_max_temperature() const {
    return m_max_temp_exists;
}

// This method returns a constant reference to your pair of your option, along with the recognition in the JSON object, e.g. 'feels_like'.
const std::pair<boost::any, std::string> &weather_client_info::get_exists_feels_like() const {
    return m_feels_like_exists;
}

// This method returns a constant reference to your pair of your option, along with the recognition in the JSON object, e.g. 'pressure'.
const std::pair<boost::any, std::string> &weather_client_info::get_exists_pressure() const {
    return m_pressure_exists;
}

// This method returns a constant reference to your pair of your option, along with the recognition in the JSON object, e.g. 'humidity'.
const std::pair<boost::any, std::string> &weather_client_info::get_exists_humidity() const {
    return m_humidity_exists;
}

// This method returns the country code of the country for which the weather should be displayed. It returns 'any', so your country code can be either a string or an integer.
const boost::any &weather_client_info::get_country_code() const {
    return m_country_code;
}

// This method returns the city name for which the weather should be displayed. It returns 'any', so your country code can be either a string or an integer.
const boost::any &weather_client_info::get_city_name() const {
    return m_city_name;
}

// This method generates an HTTPS request for which it must be shown again.
std::string weather_client_info::generate_http_weather_request(const std::string &host_name, const std::string &url_path, const std::string &api_key) const {
    std::stringstream string_stream{}; // Use a 'string stream'.

    // Generate the HTTPS request. Here, we apply a cast for the 'any' type. In our application, we assume that a city name is always a string, with so your country code.
    string_stream << "GET " << url_path << boost::any_cast<std::string>(m_city_name) << "," << boost::any_cast<std::string>(m_country_code) << "&appid=" << api_key << " HTTP/1.1\n";
    string_stream << "Host: " << host_name << '\n';
    string_stream << "Connection: close\n\n";

    return string_stream.str(); // Convert the stream of all the HTTPS request into a string.
}