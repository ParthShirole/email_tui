#ifndef MAIN_HELPER_HPP
#define MAIN_HELPER_HPP

#include <sstream>
#include <map>
#include <locale>
#include <clocale>
#include "vmime/vmime.hpp"
#include "vmime/platforms/posix/posixHandler.hpp"
#include <array>       
#include <chrono>      
#include <cmath>   
#include <functional>  
#include <memory>      
#include <string>      
#include <thread>      
#include <utility>     
#include <vector>      
#include <iostream>
#include <filesystem>
#include <fstream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include "ftxui/component/captured_mouse.hpp"      
#include "ftxui/component/component.hpp"           
#include "ftxui/component/component_base.hpp"      
#include "ftxui/component/component_options.hpp"   
#include "ftxui/component/event.hpp"               
#include "ftxui/component/screen_interactive.hpp"  
#include "ftxui/dom/elements.hpp"                  
#include "ftxui/screen/color.hpp"                  
#include "authenticator.hpp"
#include "certificateVerifier.hpp"
#include <toml++/toml.h>
#include "/home/kunal/email-tui/include/configHelper.hpp"


using namespace ftxui;
Elements line;

std::string sender;
std::string receiver;
std::ostringstream data;
std::string lines;
std::string num;
vmime::string bodyStr;
InputOption password_option;

//Creating Net Service session
static::vmime::shared_ptr <vmime::net::session> g_session=vmime::net::session::create();

#include "/home/kunal/email-tui/include/transportHelper.hpp"
#include "/home/kunal/email-tui/include/storeHelper.hpp"


#endif
