# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/Hunter/Documents/Github/sakura-v2/_deps/i18ncpp-src")
  file(MAKE_DIRECTORY "/home/Hunter/Documents/Github/sakura-v2/_deps/i18ncpp-src")
endif()
file(MAKE_DIRECTORY
  "/home/Hunter/Documents/Github/sakura-v2/_deps/i18ncpp-build"
  "/home/Hunter/Documents/Github/sakura-v2/_deps/i18ncpp-subbuild/i18ncpp-populate-prefix"
  "/home/Hunter/Documents/Github/sakura-v2/_deps/i18ncpp-subbuild/i18ncpp-populate-prefix/tmp"
  "/home/Hunter/Documents/Github/sakura-v2/_deps/i18ncpp-subbuild/i18ncpp-populate-prefix/src/i18ncpp-populate-stamp"
  "/home/Hunter/Documents/Github/sakura-v2/_deps/i18ncpp-subbuild/i18ncpp-populate-prefix/src"
  "/home/Hunter/Documents/Github/sakura-v2/_deps/i18ncpp-subbuild/i18ncpp-populate-prefix/src/i18ncpp-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/Hunter/Documents/Github/sakura-v2/_deps/i18ncpp-subbuild/i18ncpp-populate-prefix/src/i18ncpp-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/Hunter/Documents/Github/sakura-v2/_deps/i18ncpp-subbuild/i18ncpp-populate-prefix/src/i18ncpp-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
