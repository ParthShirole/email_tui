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
auto screen = ScreenInteractive::Fullscreen();

int main(int argc, const char* argv[]) 
{
std::string sender;
std::string receiver;
std::ostringstream data;
std::string lines;
std::string num;
vmime::string bodyStr;
InputOption password_option;
password_option.password = true;

Component input_sender=Input(&sender,"");
Component input_receiver=Input(&receiver,"");
Component input_data=Input(&lines,"");
Component input_msgnumber=Input(&num,"");

//Parsing Config file
const auto tbl = toml::parse_file("/home/user/email_tui/src/config.toml");  //add path to config file, also configure the config file accordingly.
std::optional<std::string> urlStringimap = tbl["urlimap"].value<std::string>();
std::optional<std::string> urlStringsmtp = tbl["urlsmtp"].value<std::string>();
std::optional<std::string> username = tbl["user"].value<std::string>();
std::optional<std::string> password = tbl["passwd"].value<std::string>();
std::optional<std::string> name = tbl["name"].value<std::string>();

//Creating Net Service session
static::vmime::shared_ptr <vmime::net::session> g_session=vmime::net::session::create();


//Transport service(sending mail)
auto trans=[&]{
	vmime::utility::url url(*urlStringsmtp);
	vmime::shared_ptr<vmime::net::transport> tr;
	tr=g_session->getTransport(url);
	tr->setProperty("connection.tls",true);
	tr->setProperty("auth.username", *username);
	tr->setProperty("auth.password", *password);
	tr->setProperty("options.need-authentication", "true");
	tr->setCertificateVerifier(vmime::make_shared <interactiveCertificateVerifier>());
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

auto store=[&]{
	vmime::utility::url url(*urlStringimap);
	vmime::shared_ptr<vmime::net::store> st;
	st=g_session->getStore(url);
	
	st->setProperty("connection.tls",true);
	st->setProperty("auth.username", *username);
	st->setProperty("auth.password", *password);
	st->setProperty("options.need-authentication", "true");
	st->setCertificateVerifier(vmime::make_shared <interactiveCertificateVerifier>());
	st->connect();

	vmime::shared_ptr <vmime::net::connectionInfos> ci = st->getConnectionInfos();
	auto a=ci->getHost();
	auto b=ci->getPort();
	
	line.clear();	//delete this, if want to see multiple messages on same screen
	line.push_back(text("Inbox Status: ")|color(Color::Blue));
	line.push_back(text("Connected to   URL: "+a+"    PORT: "+std::to_string(b))|color(Color::Green));

	vmime::shared_ptr <vmime::net::folder> f = st->getDefaultFolder();
	f->open(vmime::net::folder::MODE_READ_WRITE);
	vmime::size_t count = f->getMessageCount();
	line.push_back(text(std::to_string(count)+" message(s) in your inbox"));
	
	typedef std::map <vmime::size_t, vmime::shared_ptr <vmime::net::message> > MessageList;
	MessageList msgList;
	vmime::shared_ptr <vmime::net::message> msg;
	msg = f->getMessage(std::stoi(num));
	msgList.insert(MessageList::value_type(std::stoi(num), msg));

	vmime::net::fetchAttributes attr(vmime::net::fetchAttributes::ENVELOPE);
	f->fetchMessage(msg, attr);
	auto outputDate=msg->getHeader()->Date()->generate();
	auto outputSubject=msg->getHeader()->Subject()->generate();
	auto outputFrom=msg->getHeader()->From()->generate();
	auto outputTo=msg->getHeader()->To()->generate();
	auto outputSender=msg->getHeader()->Sender()->generate();

	vmime::net::fetchAttributes attr1(vmime::net::fetchAttributes::STRUCTURE);
	f->fetchMessage(msg, attr1);
	
	vmime::utility::outputStreamStringAdapter outStr(bodyStr);
	msg->extractPart(msg->getStructure()->getPartAt(0),outStr);

	line.push_back(text(" "));
	line.push_back(text("Message "+num+":"));
	line.push_back(text(outputDate)|flex);
	line.push_back(text(outputSubject)|flex);
	line.push_back(text(outputFrom)|flex);
	line.push_back(text(outputTo)|flex);
	line.push_back(text(outputSender)|flex);
	//line.push_back(text(bodyStr));        comment out, to print body of the message

	st->disconnect();
	return line;
};

auto button1=Button("Send",trans);
auto button2=Button("Show",store);
auto button_quit1 = Button("Quit", screen.ExitLoopClosure());
auto button_quit2 = Button("Quit", screen.ExitLoopClosure());

auto component1=Container::Vertical({
	input_sender,input_receiver,input_data,Container::Horizontal({button1,button_quit1}),
});
auto renderer1=Renderer(component1,[&]{
	return window(text("Compose a message")|hcenter,
	vbox({
		hbox(text("Sender: "),input_sender->Render(),filler()),
		hbox(text("Receiver: "),input_receiver->Render(),filler()),
		hbox(text("Message: "),input_data->Render(),filler()),
		hbox({button1->Render()|size(WIDTH,LESS_THAN,7),button_quit1->Render()|size(WIDTH,LESS_THAN,7)})|hcenter,
		separator(),
		vbox(line),
	}));
});
auto component2=Container::Vertical({
	input_msgnumber,Container::Horizontal({button2,button_quit2}),
});
auto renderer2=Renderer(component2,[&]{
	return window(text("Welcome to your Inbox")|hcenter,
	vbox({
		hbox(text("Message Number: "),input_msgnumber->Render(),filler()),
		hbox({button2->Render()|size(WIDTH,LESS_THAN,7),button_quit2->Render()|size(WIDTH,LESS_THAN,7)})|hcenter,
		separator(),
		vbox(line),
		//hflow(paragraph(bodyStr))|border,       comment out, to print body of the message
	}));
});


int tab_index = 0;
  std::vector<std::string> tab_entries = {
      "SMTP", "IMAP",
  };
  auto tab_selection = Toggle(&tab_entries, &tab_index);
  auto tab_content = Container::Tab({
      renderer1,
      renderer2,
    },&tab_index);
 
  auto main_container = Container::Vertical({
      tab_selection,
      tab_content,
  });
 
  auto main_renderer = Renderer(main_container, [&] {
    return vbox({
        text("```````Email Tui```````") | bold | hcenter|color(Color::Green),
        tab_selection->Render() | hcenter,
        tab_content->Render() | flex,
    });
  });

  screen.Loop(main_renderer);
  return EXIT_SUCCESS;
}