#include <array>       // for array
#include <chrono>      // for operator""s, chrono_literals
#include <cmath>       // for sin
#include <functional>  // for ref, reference_wrapper, function
#include <memory>      // for allocator, shared_ptr, __shared_ptr_access
#include <string>  // for string, basic_string, operator+, char_traits, to_string
#include <thread>   // for sleep_for, thread
#include <utility>  // for move
#include <vector>   // for vector
#include<iostream>
#include <filesystem>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/stat.h>
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"  // for Checkbox, Renderer, Horizontal, Vertical, Menu, Radiobox, Tab, Toggle
#include "ftxui/component/component_base.hpp"     // for ComponentBase
#include "ftxui/component/component_options.hpp"  // for InputOption
#include "ftxui/component/event.hpp"              // for Event, Event::Custom
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for operator|, color, bgcolor, filler, Element, size, vbox, flex, hbox, graph, separator, EQUAL, WIDTH, hcenter, bold, border, window, HEIGHT, Elements, hflow, flex_grow, frame, gauge, LESS_THAN, spinner, dim, GREATER_THAN
#include "ftxui/screen/color.hpp"  // for Color, Color::BlueLight, Color::RedLight, Color::Black, Color::Blue, Color::Cyan, Color::CyanLight, Color::GrayDark, Color::GrayLight, Color::Green, Color::GreenLight, Color::Magenta, Color::MagentaLight, Color::Red, Color::White, Color::Yellow, Color::YellowLight, Color::Default

using namespace ftxui;
using namespace std;
namespace fs = std::filesystem;

int main(int argc, const char* argv[]) {

  auto screen = ScreenInteractive::Fullscreen();
  int shift = 0;
  
// *********************GRAPH****************************
// *********************GRAPH****************************
  auto my_graph = [&shift](int width, int height) {
    std::vector<int> output(width);
    float v = 0.5;
    for (int i = 0; i < width; ++i) {
      output[i]=(height/2)+sin(v+(shift*0.01))*height*0.5;
      v+=0.01;
      if(output[i]<0){output[i]=output[i]*(-1);}
    }
    return output;
  };
  auto htop = Renderer([&] {
    auto wave = vbox({
        text("Sine Wave ") | hcenter,
        hbox({
            vbox({
                text("+1 "),filler(),text("0 "),filler(),text("-1 "),}),
                graph(std::ref(my_graph)) | color(Color::BlueLight) | flex | border,
        }) | flex,   
    });
    return wave;
  });

// *********************dir****************************
// *********************dir****************************

  std::string input_add_content;
  std::vector<std::string> entries;
  Component input_add = Input(&input_add_content, "input files", InputOption());
  Elements line;  
  auto render_command = [&] {
        line.clear();
        entries.clear();
        if(fs::exists(input_add_content)&&fs::is_directory(input_add_content))
        {
          line.push_back(text("List of Files & Folders:- ") | color(Color::Cyan));
          for (const auto & entry : fs::directory_iterator(input_add_content))
            {           
              entries.push_back(entry.path());
            }
            for (auto k = entries.begin(); k != entries.end(); ++k)
              {line.push_back(text(*k));}
        }
        else
          line.push_back(text("No such directory"));
  };
  int selected=0;
  auto radiobox=Menu(&entries,&selected);
  auto filemenu = Renderer(radiobox, [&] {
    return radiobox->Render() | frame | size(HEIGHT, LESS_THAN, 50) ;
  });
  Component button=Button("Press Enter",render_command);
  
  
  auto renderer = Renderer(Container::Horizontal({input_add,button,filemenu}),[&]{
    return vbox({
      hbox({input_add->Render(),button->Render()}),filemenu->Render()|frame|border,
    });
  });


//*******************HERE IT ALL COMES TOGETHER***********************
//*******************HERE IT ALL COMES TOGETHER***********************
  int tab_index = 0;
  std::vector<std::string> tab_entries = {"SINE", "INPUT"};

  auto tab_selection = Toggle(&tab_entries, &tab_index);
  auto tab_content = Container::Tab({htop,renderer},&tab_index);

  auto main_container = Container::Vertical({
      tab_selection,
      tab_content,
  });

  auto main_renderer = Renderer(main_container, [&] {
    return vbox({
        text("FTXUI Demo") | bold | hcenter,
        tab_selection->Render() | hcenter,
        tab_content->Render() | flex ,
    });
  });

  bool refresh_ui_continue = true;
  std::thread refresh_ui([&] {
    while (refresh_ui_continue) {
      using namespace std::chrono_literals;
      std::this_thread::sleep_for(0.001s);
      shift++;
      screen.PostEvent(Event::Custom);
    }
  });

  screen.Loop(main_renderer);
  refresh_ui_continue = false;
  refresh_ui.join();
  return 0;
}

// Copyright 2020 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license that can be found in
// the LICENSE file.