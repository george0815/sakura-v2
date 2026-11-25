cmake_minimum_required (VERSION 3.22)
enable_testing()


project (sakura-v2 
  LANGUAGES CXX
  VERSION 1.0
)


# Common dependencies
add_library(common_deps INTERFACE)
target_link_libraries(common_deps INTERFACE  
  ftxui::screen
  ftxui::dom
  ftxui::component
  SDL3::SDL3
  i18ncpp
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Get FTXUI

include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
set(FETCHCONTENT_QUIET OFF)

# Get FTXUI

FetchContent_Declare(ftxui
  GIT_REPOSITORY  https://github.com/arthursonzogni/ftxui.git
  GIT_TAG         v5.0.0
  GIT_PROGRESS    TRUE
  GIT_SHALLOW     TRUE
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(ftxui)


# Get i18ncpp

FetchContent_Declare(i18ncpp
  GIT_REPOSITORY  https://github.com/GeTechG/i18ncpp
  GIT_PROGRESS    TRUE
  GIT_SHALLOW     TRUE
  EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(i18ncpp)

# Get SDL3

FetchContent_Declare(SDL3
  GIT_REPOSITORY  https://github.com/libsdl-org/SDL.git
  GIT_TAG    main
  GIT_SHALLOW     TRUE
  EXCLUDE_FROM_ALL
)
FetchContent_MakeAvailable(SDL3)



file(GLOB_RECURSE SRC CONFIGURE_DEPENDS

  "core/*.cpp"
  "ui/*.cpp"

)


file(GLOB_RECURSE TEST_SRC CONFIGURE_DEPENDS
  "core/*.cpp"
  "ui/views/*.cpp"
  "ui/settings/*.cpp"
  "ui/state.h"
  "ui/resources/*"
  "tests/*.cpp"
)


add_executable(sakura-v2 ${SRC})

add_executable(cpu_tests ${TEST_SRC}) # CPU tests



target_include_directories(sakura-v2 PRIVATE ui PRIVATE core)
target_include_directories(cpu_tests PRIVATE core)
add_test(NAME CPUTests COMMAND cpu_tests)


target_link_libraries(cpu_tests PRIVATE common_deps)
target_link_libraries(sakura-v2 PRIVATE common_deps)
