#include <iostream>
#include <boost/program_options.hpp>

int main(int argc, char* argv[]) {
    boost::program_options::options_description description("Allowed options");
    description.add_options()
            ("help", "produce help message")
            ("city", boost::program_options::value<std::string>(), "city whose weather is to be displayed.")
            ("country", "country whose weather to be displayed");

    boost::program_options::variables_map map;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, description), map);
    boost::program_options::notify(map);

    if (map.count("help"))
        std::cout << description << std::endl;

    return 0;
}