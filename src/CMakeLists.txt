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


set(CMAKE_CXX_STANDARD 23) # C++ 23
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


# Set up FetchContent, FetchContent populates content at config time 
# FetchContent_Delcare sets up the options that are used to populate the 
#content, such as the repo link and version. 
# FetchContent_MakeAvailable "ensures that each of the named dependencies 
#are made available to the time it returns."
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


# Recursivly search through directory, generate a list of matching 
# files, then store that list in variable "SRC"

file(GLOB_RECURSE SRC CONFIGURE_DEPENDS

  "core/*.cpp"
  "ui/*.cpp"

)

# Same as above but for TEST_SRC
file(GLOB_RECURSE TEST_SRC CONFIGURE_DEPENDS
  "core/*.cpp"
  "ui/views/*.cpp"
  "ui/settings/*.cpp"
  "ui/state.h"
  "ui/resources/*"
  "tests/*.cpp"
)



# Creates a build target for an executable binary from source file(s)
add_executable(sakura-v2 ${SRC})
add_executable(sakura-v2-tests ${TEST_SRC}) # CPU tests


# Tells the compile where to find header files
target_include_directories(sakura-v2 PRIVATE ui PRIVATE core)
target_include_directories(sakura-v2-tests PRIVATE core)

# Tells the linker which compiled libs to link
target_link_libraries(sakura-v2-tests PRIVATE common_deps)
target_link_libraries(sakura-v2 PRIVATE common_deps)

add_test(NAME sakura-v2-tests COMMAND sakura-v2-tests) # add build target as a test
