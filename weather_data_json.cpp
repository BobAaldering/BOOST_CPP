#include "weather_data_json.h"

weather_data_json::weather_data_json(weather_client_info client_info) :
    m_client_data{std::move(client_info)}
{}

void weather_data_json::run() {
    boost::asio::io_context io_context;
    boost::asio::ssl::context ssl_context(boost::asio::ssl::context::tls);
    ssl_socket socket(io_context, ssl_context);

    boost::asio::ip::tcp::resolver resolver(io_context);
    auto endpoints = resolver.resolve("api.openweathermap.org", "443");

    // We use next_layer member function to get wrapped TCP socket reference
    boost::asio::connect(socket.next_layer(), endpoints);

    socket.handshake(boost::asio::ssl::stream_base::client);

    char request[] =
            "GET /data/2.5/weather?q=Netherlands&appid=19733fe7cf4a691b3fba8b1a8cffb44b HTTP/1.1\n"
            "Host: api.openweathermap.org\n"
            "Connection: close\n\n";

    io::write(socket, io::buffer(request));

    io::streambuf response;
    error_code ec;
    io::read(socket, response, ec);
    std::cout << std::istream(&response).rdbuf() << "\n";
}

std::string weather_data_json::retrieve_weather_json() const {
    boost::asio::io_context io_context_data{};
    boost::asio::ssl::context ssl_context_data{boost::asio::ssl::context::tls};
    ssl::stream<tcp::socket> socket_application{io_context_data, ssl_context_data};

    boost::asio::ip::tcp::resolver resolver_ip_address(io_context_data);

    auto endpoint_of_server = resolver_ip_address.resolve("api.openweathermap.org", "443");

    boost::asio::connect(socket_application.next_layer(), endpoint_of_server);

    return std::string();
}
