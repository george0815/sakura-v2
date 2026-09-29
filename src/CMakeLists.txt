cmake_minimum_required (VERSION 3.22)


project (sakura-v2 
  LANGUAGES CXX
  VERSION 1.0
)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Get FTXUI

include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(FETCHCONTENT_QUIET OFF)


FetchContent_Declare(ftxui
  GIT_REPOSITORY  https://github.com/arthursonzogni/ftxui.git
  GIT_TAG         v5.0.0
  GIT_PROGRESS    TRUE
  GIT_SHALLOW     TRUE
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(ftxui)


# Get FTXUI

FetchContent_Declare(i18ncpp
  GIT_REPOSITORY  https://github.com/GeTechG/i18ncpp
  GIT_PROGRESS    TRUE
  GIT_SHALLOW     TRUE
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(i18ncpp)

add_executable(sakura-v2 ui/main.cpp)
target_include_directories(sakura-v2 PRIVATE ui PRIVATE core)

target_link_libraries(sakura-v2
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
  PRIVATE i18ncpp
)



