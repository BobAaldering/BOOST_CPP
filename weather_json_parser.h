#ifndef HTTP_TOOL_WEATHER_JSON_PARSER_H
#define HTTP_TOOL_WEATHER_JSON_PARSER_H

#include <boost/program_options.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/any.hpp>

#include <sstream>
#include <iostream>

#include "weather_client_info.h"

#define TEMP_DEGREES_DECR (273)

class weather_json_parser {
public:
    explicit weather_json_parser(weather_client_info client_info);

    void print_required_json(const std::string& json_message) const;

private:
    weather_client_info m_client_data;
};

#endif