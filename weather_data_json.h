#ifndef HTTP_TOOL_WEATHER_DATA_JSON_H
#define HTTP_TOOL_WEATHER_DATA_JSON_H

#include <iostream>
#include <boost/asio.hpp>
#include <boost/asio/ssl.hpp>

#include "weather_client_info.h"

namespace io = boost::asio;
namespace ip = io::ip;
using tcp = ip::tcp;
using error_code = boost::system::error_code;

// Here we go
namespace ssl = io::ssl;
using ssl_socket = ssl::stream<tcp::socket>;

class weather_data_json {
public:
    explicit weather_data_json(weather_client_info client_info);

    std::string retrieve_weather_json() const;

    void run();

private:
    weather_client_info m_client_data;
};

#endif