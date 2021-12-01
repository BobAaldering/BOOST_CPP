#ifndef HTTP_TOOL_WEATHER_DATA_JSON_H
#define HTTP_TOOL_WEATHER_DATA_JSON_H

#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>
#include <boost/beast.hpp>

#include <iostream>

#include "weather_client_info.h"

#define PORT_VALUE_HTTPS (443)

class weather_data_json {
public:
    explicit weather_data_json(weather_client_info client_info, std::string host_name, std::string host_url, std::string api_key);

    [[nodiscard]] std::string retrieve_weather_json() const;

private:
    weather_client_info m_client_data;

    std::string m_host_name_weather_app;
    std::string m_host_url;
    std::string m_api_key_weather_app;
};

#endif