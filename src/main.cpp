#include "/home/kunal/email-tui/include/main-helper.hpp"

int main(int argc, const char* argv[]) 
{

auto screen = ScreenInteractive::Fullscreen();
password_option.password = true;

Component input_sender	  =	Input(&sender,"");
Component input_receiver  =	Input(&receiver,"");
Component input_data	  =	Input(&lines,"");
Component input_msgnumber =	Input(&num,"");

auto button1 	  = Button("Send",trans);
auto button2      = Button("Show",store);
auto button_quit1 = Button("Quit", screen.ExitLoopClosure());
auto button_quit2 = Button("Quit", screen.ExitLoopClosure());

auto component1=Container::Vertical({
	input_sender,
	input_receiver,
	input_data,
	Container::Horizontal({button1,button_quit1}),
});
auto renderer1=Renderer(component1,[&]{
	return window(text("Compose a message")|hcenter,
	vbox({
		hbox(text("Sender: "), input_sender->Render(), filler() ),
		hbox(text("Receiver: "), input_receiver->Render(), filler()),
		hbox(text("Message: "), input_data->Render(), filler()),
		hbox({
			  button1->Render() | size(WIDTH,LESS_THAN,7),
			  button_quit1->Render() | size(WIDTH,LESS_THAN,7)}) | hcenter,
		separator(),
		vbox(line),
	}));
});


auto component2=Container::Vertical({
	input_msgnumber,
	Container::Horizontal({button2,button_quit2}),
});
auto renderer2=Renderer(component2,[&]{
	return window(text("Welcome to your Inbox") | hcenter,
	vbox({
		hbox(text("Message Number: "),input_msgnumber->Render(),filler()),
		hbox({
			button2->Render() | size(WIDTH,LESS_THAN,7),
			button_quit2->Render() | size(WIDTH,LESS_THAN,7)}) | hcenter,
		separator(),
		vbox(line),
		//hflow(paragraph(bodyStr))|border,       comment out, to print body of the message
	}));
});


int tab_index = 0;
std::vector<std::string> tab_entries = {"SMTP", "IMAP",};
auto tab_selection  = Toggle(&tab_entries, &tab_index);
auto tab_content    = Container::Tab({renderer1,renderer2,},&tab_index);
auto main_container = Container::Vertical({tab_selection,tab_content,});


auto main_renderer = Renderer(main_container,[&]{
    return vbox({
        text("```````Email Tui```````") | bold | hcenter | color(Color::Green),
        tab_selection->Render() | hcenter,
        tab_content->Render() | flex,
    });
  });

  screen.Loop(main_renderer);
  return EXIT_SUCCESS;
}