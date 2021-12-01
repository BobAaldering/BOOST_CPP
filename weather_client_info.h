#ifndef HTTP_TOOL_WEATHER_CLIENT_INFO_H
#define HTTP_TOOL_WEATHER_CLIENT_INFO_H

#include <boost/any.hpp>

#include <sstream>

class weather_client_info {
public:
    weather_client_info(std::pair<boost::any, std::string> temperature_exists,
        std::pair<boost::any, std::string> min_temp_exists,
        std::pair<boost::any, std::string> max_temp_exists,
        std::pair<boost::any, std::string> feels_like_exists,
        std::pair<boost::any, std::string> pressure_exists,
        std::pair<boost::any, std::string> humidity_exists,
        const std::string& country_code,
        const std::string& city_name);

    [[nodiscard]] const std::pair<boost::any, std::string>& get_exists_temperature() const;
    [[nodiscard]] const std::pair<boost::any, std::string>& get_exists_min_temperature() const;
    [[nodiscard]] const std::pair<boost::any, std::string>& get_exists_max_temperature() const;
    [[nodiscard]] const std::pair<boost::any, std::string>& get_exists_feels_like() const;
    [[nodiscard]] const std::pair<boost::any, std::string>& get_exists_pressure() const;
    [[nodiscard]] const std::pair<boost::any, std::string>& get_exists_humidity() const;

    [[nodiscard]] const boost::any& get_country_code() const;
    [[nodiscard]] const boost::any& get_city_name() const;

    [[nodiscard]] std::string generate_http_weather_request(const std::string& host_name, const std::string& url_path, const std::string& api_key) const;
private:
    std::pair<boost::any, std::string> m_temperature_exists;
    std::pair<boost::any, std::string> m_min_temp_exists;
    std::pair<boost::any, std::string> m_max_temp_exists;
    std::pair<boost::any, std::string> m_feels_like_exists;
    std::pair<boost::any, std::string> m_pressure_exists;
    std::pair<boost::any, std::string> m_humidity_exists;

    boost::any m_country_code;
    boost::any m_city_name;
};

#endif