#include "weather_data_json.h"

// The constructor of the 'weather_data_json' class. It constructs the whole object.
weather_data_json::weather_data_json(weather_client_info client_info, std::string host_name, std::string host_url, std::string api_key) :
    // Where 'std::move(...)' is used, the ownership is moved.
    m_client_data{std::move(client_info)},
    m_host_name_weather_app{std::move(host_name)},
    m_host_url{std::move(host_url)},
    m_api_key_weather_app{std::move(api_key)}
{}

// This method is the heart of the application. It contacts the webserver, that returns the JSON object with weather data. It also parses the HTTP request from the webserver.
std::string weather_data_json::retrieve_weather_json() const {
    std::string response_message{}; // A string where the response message will be stored.

    // A try/catch block to catch exceptions that can occur.
    try {
        boost::asio::io_context io_context_data; // The context data for the I/O.
        boost::asio::ssl::context ssl_context_data(boost::asio::ssl::context::tls); // The context data used for SSL. Its type is TLS (Transport Layer Security).
        boost::asio::ssl::stream<boost::asio::ip::tcp::socket> socket_application(io_context_data, ssl_context_data); // Create a socket, whereby the underlying layer TCP is. This internet protocol ensures that all sent packets arrive at the server. It is a connection oriented socket.

        boost::asio::ip::tcp::resolver resolver_ip_address(io_context_data); // Variable to find the IP address of your host.
        auto endpoint_of_server = resolver_ip_address.resolve(m_host_name_weather_app, std::to_string(PORT_VALUE_HTTPS)); // Try to find the IP-address. Use port '433', used for HTTPS request. Defined by RFC.

        boost::asio::connect(socket_application.next_layer(), endpoint_of_server); // Connect with the server.

        socket_application.handshake(boost::asio::ssl::stream_base::client); // Apply a handshake.

        boost::asio::write(socket_application, boost::asio::buffer(m_client_data.generate_http_weather_request(m_host_name_weather_app, m_host_url, m_api_key_weather_app))); // Send your whole request to the server.

        boost::asio::streambuf response; // Stream buffer for the response.
        boost::system::error_code error_code; // Variable for the 'error code'.
        boost::asio::read(socket_application, response, error_code); // Read the whole buffer (data retrieved from the webserver).

        // Try to parse the whole HTTPS message from the server, because you only want the body of this message:
        boost::beast::http::parser<false, boost::beast::http::string_body> response_parser;
        response_parser.eager(true); // Used for directly getting the body of the HTTPS request.
        response_parser.put(boost::asio::buffer(response.data()), error_code); // Here, you are parsing the HTTPS request.

        response_message = response_parser.release().body(); // Retrieve the body from the parser.
    }
    // Used for catching exceptions, in this case all exceptions that can occur.
    catch (const std::exception&) {
        std::cerr << "ERROR MESSAGE - CREATING A CONNECTION WITH THE INTERNET SERVICE NOT SUCCEEDED!" << std::endl; // Show a standard error message.
    }

    return response_message; // Return the body of the response, this is encoded in JSON format. Empty string if retrieving the weather data failed.
}