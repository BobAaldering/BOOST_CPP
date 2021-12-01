#ifndef HTTP_TOOL_WEATHER_CLIENT_INFO_H
#define HTTP_TOOL_WEATHER_CLIENT_INFO_H

#include <sstream>
#include <boost/any.hpp>

class weather_client_info {
public:
    weather_client_info(boost::any temperature_exists, boost::any pressure_exists, boost::any humidity_exists, boost::any country_code, boost::any city_name);

    [[nodiscard]] const boost::any& get_exists_temperature() const;
    [[nodiscard]] const boost::any& get_exists_pressure() const;
    [[nodiscard]] const boost::any& get_exists_humidity() const;

    [[nodiscard]] const boost::any& get_country_code() const;
    [[nodiscard]] const boost::any& get_city_name() const;

    [[nodiscard]] std::string generate_http_weather_request(const std::string& host_name, const std::string& url_path, const std::string& api_key) const;
private:
    boost::any m_temperature_exists;
    boost::any m_pressure_exists;
    boost::any m_humidity_exists;

    boost::any m_country_code;
    boost::any m_city_name;
};

#endif