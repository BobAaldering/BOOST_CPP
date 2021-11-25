#include <iostream>

#include "option_parser.h"

int main(int argc, char* argv[]) {
    option_parser parser{argc, argv};

    parser.with_help("help_desc", "prints help diagnostics");
    parser.add_string_positional("host_name", "host name for the server to get the HTTP response from");
    parser.add_int_positional("port_number", "port number for the server to get the HTTP response from", 80);
    parser.add_string_positional("target", "target character for the server to get the HTTP response from", "/");
    parser.add_dbl_positional("http_version", "the HTTP version that is used for the HTTP request", 1.1);

    auto parsed_object = parser.parse_arguments();

    if (!parsed_object.empty()) {
        std::cout << "host name: " << parsed_object["host_name"].as<std::string>() << std::endl;
        std::cout << "port number: " << parsed_object["port_number"].as<int>() << std::endl;
        std::cout << "target: " << parsed_object["target"].as<std::string>() << std::endl;
        std::cout << "HTTP version: " << parsed_object["http_version"].as<double>() << std::endl;
    }

    return 0;
}