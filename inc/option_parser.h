#ifndef WEATHER_APP_OPTION_PARSER_H
#define WEATHER_APP_OPTION_PARSER_H

#include <boost/program_options.hpp> // Include the 'Boost' facilities, in this case 'program_option.hpp'.

#include <iomanip> // Include the 'standard' facilities, in this case 'iomanip'.
#include <iostream> // Include the 'standard' facilities, in this case 'iostream'.

/// This is the 'option_parser' class, which provides several methods for adding options including flags, and positional arguments.
/// It also supports a configurable 'help' option.
class option_parser {
public:
    /// The constructor of the 'option_parser' class. It construct the whole object.
    /// \param arguments_count The number of arguments passed to your program.
    /// \param arguments_value The values of all the arguments passed to your program.
    option_parser(int arguments_count, char* arguments_value[]);

    /// This is the method 'with_help' that adds a help functionality to your 'option_parser'. It is a configurable help option.
    /// \param help_flag The flag that will activate the given help functionality for all the options configured in some source file.
    /// \param description The description of your help functionality.
    [[maybe_unused]] void with_help(const std::string& help_flag, const std::string& description);

    /// This method adds a flag option to your 'option_parser'. A flag option does not take an argument.
    /// \param long_flag The long flag of your flag. Might be something like "temperature,t", for providing a short flag.
    /// \param description The description of your option.
    [[maybe_unused]] void add_flag_option(const std::string& long_flag, const std::string& description);

    /// This method adds a string option to your 'option_parser'. Your option takes a string argument with it.
    /// \param long_flag The long flag of your string option. Might be something like "temperature,t", for providing a short flag.
    /// \param description The description of your option.
    [[maybe_unused]] void add_string_option(const std::string& long_flag, const std::string& description);

    /// This method adds an integer option to your 'option_parser'. Your option takes an integer argument with it.
    /// \param long_flag The long flag of integer option. Might be something like "temperature,t", for providing a short flag.
    /// \param description The description of your option.
    [[maybe_unused]] void add_int_option(const std::string& long_flag, const std::string& description);

    /// This method adds a double option to your 'option_parser'. Your option takes an double argument with it.
    /// \param long_flag The long flag of your double option. Might be something like "temperature,t", for providing a short flag.
    /// \param description The description of your option.
    [[maybe_unused]] void add_dbl_option(const std::string& long_flag, const std::string& description);

    /// This method adds a flag option to your 'option_parser'. It has a default value.
    /// \param long_flag The long flag of your flag option. Might be something like "temperature,t", for providing a short flag.
    /// \param description The description of your option.
    /// \param default_value This is the default value of the option, in this case a boolean.
    [[maybe_unused]] void add_flag_option(const std::string& long_flag, const std::string& description, bool default_value);

    /// This method adds a string option to your 'option_parser'. It has a default value.
    /// \param long_flag The long flag of your string option. Might be something like "temperature,t", for providing a short flag.
    /// \param description The description of your option.
    /// \param default_value This is the default value of the option, in this case a string.
    [[maybe_unused]] void add_string_option(const std::string& long_flag, const std::string& description, const std::string& default_value);

    /// This method adds an integer option to your 'option_parser'. It has a default value.
    /// \param long_flag The long flag of your integer option. Might be something like "temperature,t", for providing a short flag.
    /// \param description The description of your option.
    /// \param default_value This is the default value of the option, in this case an integer.
    [[maybe_unused]] void add_int_option(const std::string& long_flag, const std::string& description, int default_value);

    /// This method adds a double option to your 'option_parser'. It has a default value.
    /// \param long_flag The long flag of your double option. Might be something like "temperature,t", for providing a short flag.
    /// \param description The description of your option.
    /// \param default_value This is the default value of the option, in this case a double.
    [[maybe_unused]] void add_dbl_option(const std::string& long_flag, const std::string& description, double default_value);

    /// This method adds a string positional argument to your 'option_parser'.
    /// \param long_flag The long flag of your string positional argument. It only needs a long flag, for recognition within the help functionality.
    /// \param description The description of your positional option.
    [[maybe_unused]] void add_string_positional(const std::string& long_flag, const std::string& description);

    /// This method adds an integer positional argument to your 'option_parser'.
    /// \param long_flag The long flag of your string positional argument. It only needs a long flag, for recognition within the help functionality.
    /// \param description The description of your positional option.
    [[maybe_unused]] void add_int_positional(const std::string& long_flag, const std::string& description);

    /// This method adds a double positional argument to your 'option_parser'.
    /// \param long_flag The long flag of your string positional argument. It only needs a long flag, for recognition within the help functionality.
    /// \param description The description of your positional option.
    [[maybe_unused]] void add_dbl_positional(const std::string& long_flag, const std::string& description);

    /// This method adds a string positional argument to your 'option_parser'. It also has a default value.
    /// \param long_flag The long flag of your string positional argument. It only needs a long flag, for recognition within the help functionality.
    /// \param description The description of your positional option.
    /// \param default_value This is the default value of the positional option, in this case a string.
    [[maybe_unused]] void add_string_positional(const std::string& long_flag, const std::string& description, const std::string& default_value);

    /// This method adds an integer positional argument to your 'option_parser'. It also has a default value.
    /// \param long_flag The long flag of your integer positional argument. It only needs a long flag, for recognition within the help functionality.
    /// \param description The description of your positional option.
    /// \param default_value This is the default value of the positional option, in this case an integer.
    [[maybe_unused]] void add_int_positional(const std::string& long_flag, const std::string& description, int default_value);

    /// This method adds a double positional argument to your 'option_parser'. It also has a default value.
    /// \param long_flag The long flag of your double positional argument. It only needs a long flag, for recognition within the help functionality.
    /// \param description The description of your positional option.
    /// \param default_value This is the default value of the positional option, in this case a double.
    [[maybe_unused]] void add_dbl_positional(const std::string& long_flag, const std::string& description, double default_value);

    /// This method parses all the given arguments parsed to the program.
    /// \return A map with all the parsed options.
    [[nodiscard]] const boost::program_options::variables_map& parse_arguments();

    /// This method generates a 'help' string when your 'help' flag is called.
    /// \return A string with all the descriptions of your 'help' functionality.
    [[nodiscard]] std::string usage_of_options() const;

private:
    boost::program_options::options_description m_options_description; // A field for all de descriptions of the options. It uses a special collection under the hood for storing all the given options.
    boost::program_options::positional_options_description m_positional_description; // A field for all de descriptions of the positional arguments. It uses a special collection under the hood for storing all the given positional arguments.
    boost::program_options::variables_map m_options_map; // A field for a map that is used for storing parsed program arguments.

    int m_positional_count; // Counter for keeping track of the positional arguments.

    std::string m_help_flag; // The configurable 'help' flag for the option parser.

    char** m_arguments_value; // Pointer to character arrays to program arguments. Yes, maybe strange, but this is the only way of writing it.
    int m_arguments_count; // The number of arguments parsed to the program.
};

#endif