find_package(GTest QUIET)

if(NOT GTest_FOUND)
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.15.2.tar.gz
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)
set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
endif()

include(GoogleTest)

add_executable(ml_tests
vec2_test.cpp)

target_link_libraries(ml_tests PRIVATE ml::ml GTest::gtest_main)
gtest_discover_tests(ml_tests)