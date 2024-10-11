# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/home/msquare01/fuzz/my_fuzz/cmake-build-debug/_deps/re2-src")
  file(MAKE_DIRECTORY "/home/msquare01/fuzz/my_fuzz/cmake-build-debug/_deps/re2-src")
endif()
file(MAKE_DIRECTORY
  "/home/msquare01/fuzz/my_fuzz/cmake-build-debug/_deps/re2-build"
  "/home/msquare01/fuzz/my_fuzz/cmake-build-debug/_deps/re2-subbuild/re2-populate-prefix"
  "/home/msquare01/fuzz/my_fuzz/cmake-build-debug/_deps/re2-subbuild/re2-populate-prefix/tmp"
  "/home/msquare01/fuzz/my_fuzz/cmake-build-debug/_deps/re2-subbuild/re2-populate-prefix/src/re2-populate-stamp"
  "/home/msquare01/fuzz/my_fuzz/cmake-build-debug/_deps/re2-subbuild/re2-populate-prefix/src"
  "/home/msquare01/fuzz/my_fuzz/cmake-build-debug/_deps/re2-subbuild/re2-populate-prefix/src/re2-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/home/msquare01/fuzz/my_fuzz/cmake-build-debug/_deps/re2-subbuild/re2-populate-prefix/src/re2-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/home/msquare01/fuzz/my_fuzz/cmake-build-debug/_deps/re2-subbuild/re2-populate-prefix/src/re2-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
