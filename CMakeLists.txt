cmake_minimum_required(VERSION 3.25)
project(manimlite VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)  # for clangd / clang-tidy

option(ML_ENABLE_SANITIZERS "Build with ASan + UBSan" ON)
option(ML_BUILD_TESTS "Build unit tests" ON)

# Header-only core library. Later weeks add real .cpp files here.
add_library(ml INTERFACE)
add_library(ml::ml ALIAS ml)
target_include_directories(ml INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)
target_compile_features(ml INTERFACE cxx_std_20)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  target_compile_options(ml INTERFACE -Wall -Wextra -Wpedantic -Wshadow -Wconversion)
endif()

if(ML_ENABLE_SANITIZERS AND CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
  add_compile_options(-fsanitize=address,undefined -fno-omit-frame-pointer)
  add_link_options(-fsanitize=address,undefined)
endif()

if(ML_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()
