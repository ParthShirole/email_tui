cmake_minimum_required (VERSION 3.11)

# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG 4d50dadb4167f356583cc2bb7b4257b340ba6275
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()


# ------------------------------------------------------------------------------

project(email-tui
  LANGUAGES CXX
  VERSION 1.0.0
)

add_executable(email-tui src/main.cpp )
# Enter the path of following
# 1. Directory in which you have cloned FTXUI	2. VMime 3. Toml++ 
target_include_directories(email-tui PRIVATE src /usr/include/vmime/ /usr/include/p11-kit-1 include/ /home/kunal/tomlplusplus/include)

target_link_libraries(email-tui
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component # Not needed for this example.
  PRIVATE vmime
)

install(TARGETS email-tui RUNTIME DESTINATION "bin")
