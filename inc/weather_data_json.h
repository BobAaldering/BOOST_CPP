#ifndef WEATHER_APP_WEATHER_DATA_JSON_H
#define WEATHER_APP_WEATHER_DATA_JSON_H

#include <boost/asio.hpp> // Include the 'Boost' facilities, in this case 'asio.hpp'.
#include <boost/asio/ssl.hpp> // Include the 'Boost' facilities, in this case 'asio - ssl.hpp'.
#include <boost/beast.hpp> // Include the 'Boost' facilities, in this case 'beast'.

#include <iostream> // Include the 'standard' facilities, in this case 'iostream'.

#include "weather_client_info.h" // Include the 'weather_json_parser' facilities.

#define PORT_VALUE_HTTPS (443) // Define of the port used for HTTPS.

/// This is the 'weather_data_json' class. This class is given this name because it really only serves the purpose of returning a JSON message from the web server that supplies it.
/// It contacts the server by performing a handshake, and then actually gets the data in the form of a JSON format.
class weather_data_json {
public:
    /// The constructor of the 'weather_data_json' class. It constructs the whole object.
    /// \param client_info The object that represents the info of your client. This also generates the HTTP request.
    /// \param host_name The hostname of the server.
    /// \param host_url The URL of the server, for retrieving the right information.
    /// \param api_key The API key. When you do not deliver an API key, the server will not give any information.
    weather_data_json(weather_client_info client_info, std::string host_name, std::string host_url, std::string api_key);

    /// This method is the heart of the application. It contacts the webserver, that returns the JSON object with weather data. It also parses the HTTP request from the webserver.
    /// \return A string with the whole JSON object with weather data.
    [[nodiscard]] std::string retrieve_weather_json() const;

private:
    weather_client_info m_client_data; // This field contains the data of your client.

    std::string m_host_name_weather_app; // This field represents the hostname of the weather app. In this case 'openweathermap'.
    std::string m_host_url; // This field contains the URL.
    std::string m_api_key_weather_app; // This field contains the API key.
};

#endif