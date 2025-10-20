cmake_minimum_required(VERSION 3.24)

project(magazine_clippings)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable(Catch2)

add_executable(factorial_test tests/factorial_test.cpp src/factorial.cpp)
add_executable(magazine_clippings_test tests/magazine_clippings_test.cpp src/magazine_clippings.cpp)
add_executable(main main.cpp src/magazine_clippings.cpp)

target_link_libraries(factorial_test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(magazine_clippings_test PRIVATE Catch2::Catch2WithMain)
