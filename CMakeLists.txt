cmake_minimum_required(VERSION 3.8)
project(callstackpp LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(WERROR "Add -Werror flag to build (turns warnings into errors)" ON)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

if(CONAN_EXPORTED) # in conan local cache
  include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
  conan_basic_setup()
else() # in user space
  include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/conan.cmake)
  conan_cmake_run(CONANFILE conanfile.py
                  BASIC_SETUP
				  CMAKE_TARGETS
				  BUILD missing)
endif()

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(OPTIMIZATION_FLAGS "-DDEBUG")
  if(NOT MSVC)
    set(OPTIMIZATION_FLAGS "${OPTIMIZATION_FLAGS} -O0")
  endif()
  message("-- Configuring debug build")
else()
  if(MSVC)
    set(OPTIMIZATION_FLAGS "-DNDEBUG -O2 -Zi")
  else()
    set(OPTIMIZATION_FLAGS "-DNDEBUG -g")
  endif()
  message("-- Configuring release build")
endif()

if(MSVC)
  set(DESIRED_WARNINGS "-WX")
else()
  set(DESIRED_WARNINGS "-Wall -Wextra -Wconversion -Wunreachable-code -Wuninitialized -pedantic-errors -Wold-style-cast -Wno-error=unused-variable -Wshadow -Wfloat-equal")
  if(CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(DESIRED_WARNINGS "${DESIRED_WARNINGS} -Wmost")
  endif()
  if (WERROR)
    set(DESIRED_WARNINGS "${DESIRED_WARNINGS} -Werror")
  endif()
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OPTIMIZATION_FLAGS} ${DESIRED_WARNINGS}")

include_directories("${PROJECT_SOURCE_DIR}/include")

add_library(callstackpp STATIC src/callstackpp.cpp)
target_compile_definitions(callstackpp PUBLIC BACKWARD_HAS_LIBUNWIND=1 BACKWARD_HAS_DWARF=1)
target_link_libraries(callstackpp PUBLIC dl CONAN_PKG::libdwarf CONAN_PKG::libunwind)

file(GLOB TEST_SOURCES test/*.cpp)
add_executable(unit-tests ${TEST_SOURCES})
target_link_libraries(unit-tests callstackpp CONAN_PKG::catch2)
