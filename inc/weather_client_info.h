#ifndef WEATHER_APP_WEATHER_CLIENT_INFO_H
#define WEATHER_APP_WEATHER_CLIENT_INFO_H

#include <boost/any.hpp> // Include the 'Boost' facilities, in this case 'any.hpp'.

#include <sstream> // Include the 'standard' facilities, in this case 'sstream'.

/// This is the 'weather_client_info' class, that as a wrapper cares about all parsed options. For example, you can check whether the 'temperature' should be displayed, or the humidity. You can also get the country code and city name..
/// 'any' is used to make the code somewhat generic. For example, if you have an integer option as temperature, with an integer argument it can be given here. After all, it is never a problem to work with 'any'.
class weather_client_info {
public:
    /// The constructor of the 'weather_client_info' class. It constructs the whole object.
    /// \param temperature_exists A pair if the temperature exists within your whole program (passed to you program as argument).
    /// \param min_temp_exists A pair if the minimum temperature exists within your whole program (passed to you program as argument).
    /// \param max_temp_exists A pair if the maximum temperature exists within your whole program (passed to you program as argument).
    /// \param feels_like_exists A pair if the 'feels like' temperature exists within your whole program (passed to you program as argument).
    /// \param pressure_exists A pair if the pressure exists within your whole program (passed to you program as argument).
    /// \param humidity_exists A pair if the humidity exists within your whole program (passed to you program as argument).
    /// \param country_code A string if the temperature exists within your whole program (passed to you program as argument).
    /// \param city_name A string if the city name exists within your whole program (passed to you program as argument).
    weather_client_info(std::pair<boost::any, std::string> temperature_exists,
        std::pair<boost::any, std::string> min_temp_exists,
        std::pair<boost::any, std::string> max_temp_exists,
        std::pair<boost::any, std::string> feels_like_exists,
        std::pair<boost::any, std::string> pressure_exists,
        std::pair<boost::any, std::string> humidity_exists,
        const std::string& country_code,
        const std::string& city_name);

    /// This method returns a constant reference to your pair of your option, along with the recognition in the JSON object, e.g. 'temp'.
    /// \return A pair of your parse option, and a identifier for the JSON object.
    [[nodiscard]] const std::pair<boost::any, std::string>& get_exists_temperature() const;

    /// This method returns a constant reference to your pair of your option, along with the recognition in the JSON object, e.g. 'temp_min'.
    /// \return A pair of your parse option, and a identifier for the JSON object.
    [[nodiscard]] const std::pair<boost::any, std::string>& get_exists_min_temperature() const;

    /// This method returns a constant reference to your pair of your option, along with the recognition in the JSON object, e.g. 'temp_max'.
    /// \return A pair of your parse option, and a identifier for the JSON object.
    [[nodiscard]] const std::pair<boost::any, std::string>& get_exists_max_temperature() const;

    /// This method returns a constant reference to your pair of your option, along with the recognition in the JSON object, e.g. 'feels_like'.
    /// \return A pair of your parse option, and a identifier for the JSON object.
    [[nodiscard]] const std::pair<boost::any, std::string>& get_exists_feels_like() const;

    /// This method returns a constant reference to your pair of your option, along with the recognition in the JSON object, e.g. 'pressure'.
    /// \return A pair of your parse option, and a identifier for the JSON object.
    [[nodiscard]] const std::pair<boost::any, std::string>& get_exists_pressure() const;

    /// This method returns a constant reference to your pair of your option, along with the recognition in the JSON object, e.g. 'humidity'.
    /// \return A pair of your parse option, and a identifier for the JSON object.
    [[nodiscard]] const std::pair<boost::any, std::string>& get_exists_humidity() const;

    /// This method returns the country code of the country for which the weather should be displayed. It returns 'any', so your country code can be either a string or an integer.
    /// \return The country code, it can optionally be a string or an integer. Hence the use of 'any'. Note that you have to take into account casting to a certain type.
    [[nodiscard]] const boost::any& get_country_code() const;

    /// This method returns the city name for which the weather should be displayed. It returns 'any', so your country code can be either a string or an integer.
    /// \return The city name, it can optionally be a string or an integer. Hence the use of 'any'. Note that you have to take into account casting to a certain type.
    [[nodiscard]] const boost::any& get_city_name() const;

    /// This method generates an HTTPS request for which it must be shown again.
    /// \param host_name The name of the server's host. This could be 'api.openweathermap.org'.
    /// \param url_path The specific URL, for which the server should be consulted.
    /// \param api_key The server requires an API key. It can be given here.
    /// \return A string which in this case is your HTTPS request.
    [[nodiscard]] std::string generate_http_weather_request(const std::string& host_name, const std::string& url_path, const std::string& api_key) const;
private:
    std::pair<boost::any, std::string> m_temperature_exists; // A field if your temperature exists (will be written to the standard out after retrieving the data via de webserver).
    std::pair<boost::any, std::string> m_min_temp_exists; // A field if your minimum temperature exists (will be written to the standard out after retrieving the data via de webserver).
    std::pair<boost::any, std::string> m_max_temp_exists; // A field if your maximum temperature exists (will be written to the standard out after retrieving the data via de webserver).
    std::pair<boost::any, std::string> m_feels_like_exists; // A field if your 'feels like' temperature exists (will be written to the standard out after retrieving the data via de webserver).
    std::pair<boost::any, std::string> m_pressure_exists; // A field if your pressure exists (will be written to the standard out after retrieving the data via de webserver).
    std::pair<boost::any, std::string> m_humidity_exists; // A field if your humidity exists (will be written to the standard out after retrieving the data via de webserver).

    boost::any m_country_code; // A field for the country code.
    boost::any m_city_name; // A field for the city name.
};

#endif