#ifndef CONFIG_HELPER_HPP
#define CONFIG_HELPER_HPP

//Parsing Config file
const auto tbl = toml::parse_file("/home/kunal/email-tui/include/config.toml");  //add path to config file, also configure the config file accordingly.
std::optional<std::string> urlStringimap = tbl["urlimap"].value<std::string>();
std::optional<std::string> urlStringsmtp = tbl["urlsmtp"].value<std::string>();
std::optional<std::string> username = tbl["user"].value<std::string>();
std::optional<std::string> password = tbl["passwd"].value<std::string>();
std::optional<std::string> name = tbl["name"].value<std::string>();


#endif