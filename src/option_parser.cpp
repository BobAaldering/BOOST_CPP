#include "option_parser.h"

// The constructor of your class. It takes the number of arguments passed to the program, with its values.
option_parser::option_parser(int arguments_count, char* arguments_value[]) :
    // Where '{}' is used after a field, that is a default initialization.
    m_options_description{},
    m_positional_description{},
    m_options_map{},
    m_positional_count{},
    m_help_flag{},
    m_arguments_value{arguments_value}, // Initialize this field with the values of the arguments passed to the program.
    m_arguments_count{arguments_count} // Initialize this field with the number of arguments passed to the program.
{}

// This is the method 'with_help' that adds a help functionality to your 'option_parser'. It is a configurable help option.
void option_parser::with_help(const std::string &help_flag, const std::string &description) {
    m_help_flag = help_flag; // Assign your configurable help flag to 'm_help_flag'. Used for recognition within this class when parsing the objects.

    // Add your option. Convert your 'string' to a C-style character array, used for the method 'add_option'.
    m_options_description.add_options()
        (help_flag.c_str(), description.c_str());
}

// This method adds a flag option to your 'option_parser'. A flag option does not take an argument.
[[maybe_unused]] void option_parser::add_flag_option(const std::string &long_flag, const std::string &description) {
    auto complete_description = description + " [bool]"; // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Add your option. Convert your 'string' to a C-style character array, used for the method 'add_option'.
    m_options_description.add_options()
        (long_flag.c_str(), complete_description.c_str());
}

// This method adds a string option to your 'option_parser'. Your option takes a string argument with it.
[[maybe_unused]] void option_parser::add_string_option(const std::string &long_flag, const std::string &description) {
    auto complete_description = description + " [string]"; // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Add your option. Convert your 'string' to a C-style character array, used for the method 'add_option'.
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<std::string>(), complete_description.c_str());
}

// This method adds an integer option to your 'option_parser'. Your option takes an integer argument with it.
[[maybe_unused]] void option_parser::add_int_option(const std::string &long_flag, const std::string &description) {
    auto complete_description = description + " [int]"; // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Add your option. Convert your 'string' to a C-style character array, used for the method 'add_option'.
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<int>(), complete_description.c_str());
}

// This method adds a double option to your 'option_parser'. Your option takes a double argument with it.
[[maybe_unused]] void option_parser::add_dbl_option(const std::string &long_flag, const std::string &description) {
    auto complete_description = description + " [double]"; // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Add your option. Convert your 'string' to a C-style character array, used for the method 'add_option'.
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<double>(), complete_description.c_str());
}

// This method adds a flag option to your 'option_parser'. It has a default value.
[[maybe_unused]] void option_parser::add_flag_option(const std::string &long_flag, const std::string &description, bool default_value) {
    auto complete_description = description + " [bool] - DEFAULT: " + ((default_value) ? "true" : "false"); // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Add your option. Convert your 'string' to a C-style character array, used for the method 'add_option'.
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<bool>()->default_value(default_value), complete_description.c_str()); // Here you are using a default value.
}

// This method adds a string option to your 'option_parser'. It has a default value.
[[maybe_unused]] void option_parser::add_string_option(const std::string &long_flag, const std::string &description, const std::string &default_value) {
    auto complete_description = description + " [string] - DEFAULT: " + default_value; // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Add your option. Convert your 'string' to a C-style character array, used for the method 'add_option'.
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<std::string>()->default_value(default_value), complete_description.c_str());  // Here you are using a default value.
}

// This method adds an integer option to your 'option_parser'. It has a default value.
[[maybe_unused]] void option_parser::add_int_option(const std::string &long_flag, const std::string &description, int default_value) {
    auto complete_description = description + " [int] - DEFAULT: " + std::to_string(default_value); // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Add your option. Convert your 'string' to a C-style character array, used for the method 'add_option'.
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<int>()->default_value(default_value), complete_description.c_str());  // Here you are using a default value.
}

// This method adds a double option to your 'option_parser'. It has a default value.
[[maybe_unused]] void option_parser::add_dbl_option(const std::string &long_flag, const std::string &description, double default_value) {
    auto complete_description = description + " [double] - DEFAULT: " + std::to_string(default_value); // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Add your option. Convert your 'string' to a C-style character array, used for the method 'add_option'.
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<double>()->default_value(default_value), complete_description.c_str());  // Here you are using a default value.
}

// This method adds a string positional argument to your 'option_parser'.
[[maybe_unused]] void option_parser::add_string_positional(const std::string &long_flag, const std::string &description) {
    auto complete_description = description + " [string]"; // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Your positional arguments is also an option, so add it as an option.
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<std::string>(), complete_description.c_str());

    m_positional_description.add(long_flag.c_str(), 1); // Add your positional argument, with only one value. Convert your 'long_flag' to a C-style character array.
    m_positional_count++; // One positional argument more, so increase it.
}

// This method adds an integer positional argument to your 'option_parser'.
[[maybe_unused]] void option_parser::add_int_positional(const std::string &long_flag, const std::string &description) {
    auto complete_description = description + " [int]"; // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Your positional arguments is also an option, so add it as an option.
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<int>(), complete_description.c_str());

    m_positional_description.add(long_flag.c_str(), 1); // Add your positional argument, with only one value. Convert your 'long_flag' to a C-style character array.
    m_positional_count++; // One positional argument more, so increase it.
}

// This method adds a double positional argument to your 'option_parser'.
[[maybe_unused]] void option_parser::add_dbl_positional(const std::string &long_flag, const std::string &description) {
    auto complete_description = description + " [double]"; // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Your positional arguments is also an option, so add it as an option.
    m_options_description.add_options()
        (long_flag.c_str(), boost::program_options::value<double>(), complete_description.c_str());

    m_positional_description.add(long_flag.c_str(), 1); // Add your positional argument, with only one value. Convert your 'long_flag' to a C-style character array.
    m_positional_count++; // One positional argument more, so increase it.
}

// This method adds a string positional argument to your 'option_parser'. It also has a default value.
[[maybe_unused]] void option_parser::add_string_positional(const std::string &long_flag, const std::string &description, const std::string &default_value) {
    auto complete_description = description + " [string] - DEFAULT: " + default_value; // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Your positional arguments is also an option, so add it as an option.
    m_options_description.add_options()
            (long_flag.c_str(), boost::program_options::value<std::string>()->default_value(default_value), complete_description.c_str()); // Here you are using a default value.

    m_positional_description.add(long_flag.c_str(), 1); // Add your positional argument, with only one value. Convert your 'long_flag' to a C-style character array.
    m_positional_count++; // One positional argument more, so increase it.
}

// This method adds an integer positional argument to your 'option_parser'. It also has a default value.
[[maybe_unused]] void option_parser::add_int_positional(const std::string &long_flag, const std::string &description, int default_value) {
    auto complete_description = description + " [int] - DEFAULT: " + std::to_string(default_value); // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Your positional arguments is also an option, so add it as an option.
    m_options_description.add_options()
            (long_flag.c_str(), boost::program_options::value<int>()->default_value(default_value), complete_description.c_str()); // Here you are using a default value.

    m_positional_description.add(long_flag.c_str(), 1); // Add your positional argument, with only one value. Convert your 'long_flag' to a C-style character array.
    m_positional_count++; // One positional argument more, so increase it.
}

// This method adds a double positional argument to your 'option_parser'. It also has a default value.
[[maybe_unused]] void option_parser::add_dbl_positional(const std::string &long_flag, const std::string &description, double default_value) {
    auto complete_description = description + " [double] - DEFAULT: " + std::to_string(default_value); // The complete description to show when the 'help' functionality is called within the arguments passed to the program.

    // Your positional arguments is also an option, so add it as an option.
    m_options_description.add_options()
            (long_flag.c_str(), boost::program_options::value<double>()->default_value(default_value), complete_description.c_str()); // Here you are using a default value.

    m_positional_description.add(long_flag.c_str(), 1); // Add your positional argument, with only one value. Convert your 'long_flag' to a C-style character array.
    m_positional_count++; // One positional argument more, so increase it.
}

// This method parses all the given arguments parsed to the program.
[[maybe_unused]] const boost::program_options::variables_map &option_parser::parse_arguments() {
    // A try/catch block to catch exceptions that can occur.
    try {
        // Parse all the program arguments, take also the positional arguments into account.
        boost::program_options::store(boost::program_options::command_line_parser(m_arguments_count, m_arguments_value)
            .options(m_options_description)
            .positional(m_positional_description)
            .run(), m_options_map);

        boost::program_options::notify(m_options_map); // Used for notifying, you can use the collection of parsed options.
    }
    // Used for catching exceptions, in this case 'program options' exceptions.
    catch (const boost::program_options::error&e) {
        std::cerr << "ERROR MESSAGE - PARSING PROGRAM OPTIONS NOT SUCCEEDED!" << std::endl; // Show a standard error message.
    }

    // Check if you called your 'help' functionality.
    if (m_options_map.count(m_help_flag))
        std::cout << usage_of_options() << std::endl; // Print the usage of the options.

    return m_options_map; // Return the collection of parsed options.
}

// This method generates a 'help' string when your 'help' flag is called.
[[maybe_unused]] std::string option_parser::usage_of_options() const {
    std::stringstream string_stream{}; // Use a 'string stream'.
    string_stream << "Usage: ./" << program_invocation_short_name << " "; // Print the usage.

    // Check if you have flags/options:
    if (!m_options_description.options().empty()) {
        string_stream << "[FLAGS] "; // Show for the usage.

        // Check if you have positional arguments.
        if (m_positional_count) {
            for (int i = 0; i < m_positional_count; i++)
                string_stream << '<' << m_positional_description.name_for_position(i) << "> "; // Print the usage of your positional arguments.
        }

        string_stream << '\n';

        // Assign all the descriptions of your options, respectively the positional arguments.
        for (const auto& single_option : m_options_description.options())
            string_stream << std::quoted(single_option->long_name()) << "\t\t" << single_option->description() << std::endl; // Assign it to your 'string stream'.
    }

    return string_stream.str(); // Convert the stream of all the 'help' functionalities into a string.
}