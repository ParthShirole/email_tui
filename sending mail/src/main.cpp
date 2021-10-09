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
#include "example6_authenticator.hpp"
#include "example6_certificateVerifier.hpp"
#include <toml++/toml.h>

using namespace ftxui;
Elements line;

int main(int argc, const char* argv[]) 
{

//std::string urlString;
//std::string username;
//std::string password;
std::string sender;
std::string receiver;
std::ostringstream data;
std::string lines;
InputOption password_option;
password_option.password = true;

//Component input_url=Input(&urlString,"URL(eg. smtp://smtp.gmail.com)");
//Component input_user=Input(&username,"");
//Component input_pass=Input(&password,"",password_option);
Component input_sender=Input(&sender,"");
Component input_receiver=Input(&receiver,"");
Component input_data=Input(&lines,"");

const auto tbl = toml::parse_file("config.toml");
std::optional<std::string> urlString = tbl["url"].value<std::string>();
std::optional<std::string> username = tbl["user"].value<std::string>();
std::optional<std::string> password = tbl["passwd"].value<std::string>();
std::optional<std::string> name = tbl["name"].value<std::string>();

static::vmime::shared_ptr <vmime::net::session> g_session=vmime::net::session::create();

auto trans=[&]{
	vmime::utility::url url(*urlString);
	vmime::shared_ptr<vmime::net::transport> tr;
	tr=g_session->getTransport(url);
	
	tr->setProperty("connection.tls",true);
	tr->setProperty("auth.username", *username);
	tr->setProperty("auth.password", *password);
	tr->setProperty("options.need-authentication", "true");
	
	tr->setCertificateVerifier
			(vmime::make_shared <interactiveCertificateVerifier>());

	tr->connect();
	
	data<<lines;
	vmime::string msgData = data.str();
	vmime::mailbox from(sender);
	vmime::mailboxList to;
	to.appendMailbox(vmime::make_shared <vmime::mailbox>(receiver));
	vmime::utility::inputStreamStringAdapter vis(msgData);
	if(sender==""||receiver==""||msgData=="")
	{
		line.clear();
		line.push_back(text("One/more field missing")|color(Color::Red)|blink);
	}
	else
	{
		tr->send(from,to,vis,msgData.length());
		line.clear();
		line.push_back(text("Mail Sent :)")|color(Color::Green));
		tr->disconnect();
		data.clear();
		lines="";sender="";receiver="";
	}
	return line;
};

auto button=Button("Send",trans);

auto component=Container::Vertical({
	/*input_url,input_user,input_pass,*/
	input_sender,input_receiver,input_data,button,
});
std::string wel="Welcome to "+*name+"'s SMTP Client!";
auto renderer=Renderer(component,[&]{
	return window(text(wel)|hcenter,
		vbox({
		//hbox(text("Srvr URL: "),input_url->Render(),filler()),
		//hbox(text("Username: "),input_user->Render(),filler()),
		//hbox(text("Password: "),input_pass->Render(),filler()),
		hbox(text("Sender: "),input_sender->Render(),filler()),
		hbox(text("Receiver: "),input_receiver->Render(),filler()),
		hbox(text("Message: "),input_data->Render(),filler()),
		button->Render()|size(WIDTH,LESS_THAN,7)|hcenter,
		separator(),
		vbox(line),
	}));
});

  auto screen = ScreenInteractive::Fullscreen();
  screen.Loop(renderer);
  return EXIT_SUCCESS;
}
