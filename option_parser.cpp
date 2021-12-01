#include "option_parser.h"

option_parser::option_parser(int arguments_count, char* arguments_value[]) :
    m_options_description{},
    m_positional_description{},
    m_options_map{},
    m_positional_count{},
    m_help_flag{},
    m_arguments_value{arguments_value},
    m_arguments_count{arguments_count}
{}

void option_parser::with_help(const std::string &help_flag, const std::string &description) {
    m_help_flag = help_flag;

    m_options_description.add_options()
        (help_flag.c_str(), description.c_str());
}

[[maybe_unused]] void option_parser::add_flag_option(const std::string &long_flag, const std::string &description) {
    auto complete_description = description + " [bool]";
    m_options_description.add_options()
        (long_flag.c_str(), complete_description.c_str());
}

[[maybe_unused]] void option_parser::add_string_option(const std::string &long_flag, const std::string &description) {
    auto complete_description = description + " [string]";
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<std::string>(), complete_description.c_str());
}

[[maybe_unused]] void option_parser::add_int_option(const std::string &long_flag, const std::string &description) {
    auto complete_description = description + " [int]";
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<int>(), complete_description.c_str());
}

[[maybe_unused]] void option_parser::add_dbl_option(const std::string &long_flag, const std::string &description) {
    auto complete_description = description + " [double]";
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<double>(), complete_description.c_str());
}

[[maybe_unused]] void option_parser::add_flag_option(const std::string &long_flag, const std::string &description, bool default_value) {
    auto complete_description = description + " [bool] - DEFAULT: " + ((default_value) ? "true" : "false");
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<bool>()->default_value(default_value), complete_description.c_str());
}

[[maybe_unused]] void option_parser::add_string_option(const std::string &long_flag, const std::string &description, const std::string &default_value) {
    auto complete_description = description + " [string] - DEFAULT: " + default_value;
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<std::string>()->default_value(default_value), complete_description.c_str());
}

[[maybe_unused]] void option_parser::add_int_option(const std::string &long_flag, const std::string &description, int default_value) {
    auto complete_description = description + " [int] - DEFAULT: " + std::to_string(default_value);
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<int>()->default_value(default_value), complete_description.c_str());
}

[[maybe_unused]] void option_parser::add_dbl_option(const std::string &long_flag, const std::string &description, double default_value) {
    auto complete_description = description + " [double] - DEFAULT: " + std::to_string(default_value);
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<double>()->default_value(default_value), complete_description.c_str());
}

[[maybe_unused]] void option_parser::add_string_positional(const std::string &long_flag, const std::string &description) {
    auto complete_description = description + " [string]";
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<std::string>(), complete_description.c_str());

    m_positional_description.add(long_flag.c_str(), 1);
    m_positional_count++;
}

[[maybe_unused]] void option_parser::add_int_positional(const std::string &long_flag, const std::string &description) {
    auto complete_description = description + " [int]";
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<int>(), complete_description.c_str());

    m_positional_description.add(long_flag.c_str(), 1);
    m_positional_count++;
}

[[maybe_unused]] void option_parser::add_dbl_positional(const std::string &long_flag, const std::string &description) {
    auto complete_description = description + " [double]";
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<double>(), complete_description.c_str());

    m_positional_description.add(long_flag.c_str(), 1);
    m_positional_count++;
}

void option_parser::add_string_positional(const std::string &long_flag, const std::string &description, const std::string &default_value) {
    auto complete_description = description + " [string] - DEFAULT: " + default_value;
    m_options_description.add_options()
            (long_flag.c_str(), boost::program_options::value<std::string>()->default_value(default_value), complete_description.c_str());

    m_positional_description.add(long_flag.c_str(), 1);
    m_positional_count++;
}

void option_parser::add_int_positional(const std::string &long_flag, const std::string &description, int default_value) {
    auto complete_description = description + " [int] - DEFAULT: " + std::to_string(default_value);
    m_options_description.add_options()
            (long_flag.c_str(), boost::program_options::value<int>()->default_value(default_value), complete_description.c_str());

    m_positional_description.add(long_flag.c_str(), 1);
    m_positional_count++;
}

void option_parser::add_dbl_positional(const std::string &long_flag, const std::string &description, double default_value) {
    auto complete_description = description + " [double] - DEFAULT: " + std::to_string(default_value);
    m_options_description.add_options()
            (long_flag.c_str(), boost::program_options::value<double>()->default_value(default_value), complete_description.c_str());

    m_positional_description.add(long_flag.c_str(), 1);
    m_positional_count++;
}

[[maybe_unused]] const boost::program_options::variables_map &option_parser::parse_arguments() {
    try {
        boost::program_options::store(boost::program_options::command_line_parser(m_arguments_count, m_arguments_value)
            .options(m_options_description)
            .positional(m_positional_description)
            .run(), m_options_map);

        boost::program_options::notify(m_options_map);
    }
    catch (const boost::program_options::error&e) {
        std::cerr << "ERROR MESSAGE - PARSING PROGRAM OPTIONS NOT SUCCEEDED!" << std::endl;
    }

    if (m_options_map.count(m_help_flag))
        std::cout << usage_of_options() << std::endl;

    return m_options_map;
}

[[maybe_unused]] std::string option_parser::usage_of_options() const {
    std::stringstream string_stream{};
    string_stream << "Usage: ./" << program_invocation_short_name << " ";

    if (!m_options_description.options().empty()) {
        string_stream << "[FLAGS] ";

        if (m_positional_count) {
            for (int i = 0; i < m_positional_count; i++)
                string_stream << '<' << m_positional_description.name_for_position(i) << "> ";
        }

        string_stream << '\n';

        for (const auto& single_option : m_options_description.options()) {
            string_stream << std::quoted(single_option->long_name()) << "\t\t" << single_option->description() << std::endl;
        }
    }

    return string_stream.str();
}