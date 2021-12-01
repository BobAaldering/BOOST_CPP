#include "weather_data_json.h"

weather_data_json::weather_data_json(weather_client_info client_info, std::string host_name, std::string host_url, std::string api_key) :
    m_client_data{std::move(client_info)},
    m_host_name_weather_app{std::move(host_name)},
    m_host_url{std::move(host_url)},
    m_api_key_weather_app{std::move(api_key)}
{}

std::string weather_data_json::retrieve_weather_json() const {
    std::string response_message{};

    try {
        boost::asio::io_context io_context_data;
        boost::asio::ssl::context ssl_context_data(boost::asio::ssl::context::tls);
        boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_application(io_context_data, ssl_context_data);

        boost::asio::ip::tcp::resolver resolver_ip_address(io_context_data);
        auto endpoint_of_server = resolver_ip_address.resolve(m_host_name_weather_app, std::to_string(PORT_VALUE_HTTPS));

        boost::asio::connect(socket_application.next_layer(), endpoint_of_server);

        socket_application.handshake(boost::asio::ssl::stream_base::client);

        boost::asio::write(socket_application, boost::asio::buffer(m_client_data.generate_http_weather_request(m_host_name_weather_app, m_host_url, m_api_key_weather_app)));

        boost::asio::streambuf response;
        boost::system::error_code error_code;
        boost::asio::read(socket_application, response, error_code);

        boost::beast::http::parser<false, boost::beast::http::string_body> response_parser;
        response_parser.eager(true);
        response_parser.put(boost::asio::buffer(response.data()), error_code);

        response_message = response_parser.release().body();
    }
    catch (const std::exception&) {
        std::cerr << "ERROR MESSAGE - CREATING A CONNECTION WITH THE INTERNET SERVICE NOT SUCCEEDED!" << std::endl;
    }

    return response_message;
}