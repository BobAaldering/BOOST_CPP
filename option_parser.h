#ifndef HTTP_TOOL_OPTION_PARSER_H
#define HTTP_TOOL_OPTION_PARSER_H

#include <boost/program_options.hpp>

#include <iomanip>
#include <iostream>


class option_parser {
public:
    option_parser(int arguments_count, char* arguments_value[]);

    [[maybe_unused]] void with_help(const std::string& help_flag, const std::string& description);

    [[maybe_unused]] void add_flag_option(const std::string& long_flag, const std::string& description);
    [[maybe_unused]] void add_string_option(const std::string& long_flag, const std::string& description);
    [[maybe_unused]] void add_int_option(const std::string& long_flag, const std::string& description);
    [[maybe_unused]] void add_dbl_option(const std::string& long_flag, const std::string& description);

    [[maybe_unused]] void add_flag_option(const std::string& long_flag, const std::string& description, bool default_value);
    [[maybe_unused]] void add_string_option(const std::string& long_flag, const std::string& description, const std::string& default_value);
    [[maybe_unused]] void add_int_option(const std::string& long_flag, const std::string& description, int default_value);
    [[maybe_unused]] void add_dbl_option(const std::string& long_flag, const std::string& description, double default_value);

    [[maybe_unused]] void add_string_positional(const std::string& long_flag, const std::string& description);
    [[maybe_unused]] void add_int_positional(const std::string& long_flag, const std::string& description);
    [[maybe_unused]] void add_dbl_positional(const std::string& long_flag, const std::string& description);

    [[maybe_unused]] void add_string_positional(const std::string& long_flag, const std::string& description, const std::string& default_value);
    [[maybe_unused]] void add_int_positional(const std::string& long_flag, const std::string& description, int default_value);
    [[maybe_unused]] void add_dbl_positional(const std::string& long_flag, const std::string& description, double default_value);

    [[nodiscard]] const boost::program_options::variables_map& parse_arguments();

    [[nodiscard]] std::string usage_of_options() const;

private:
    boost::program_options::options_description m_options_description;
    boost::program_options::positional_options_description m_positional_description;
    boost::program_options::variables_map m_options_map;

    int m_positional_count;

    std::string m_help_flag;

    char** m_arguments_value;
    int m_arguments_count;
};

#endif