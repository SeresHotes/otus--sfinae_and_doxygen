cmake_minimum_required (VERSION 3.12)

project(print_ip)

add_executable (otus--sfinae_and_doxygen "main.cpp"  "ip_gen.cpp"  "ip_gen.h")
add_executable (target_test "test.cpp")
 
set_property(TARGET otus--sfinae_and_doxygen PROPERTY CXX_STANDARD 17)
set_property(TARGET target_test PROPERTY CXX_STANDARD 17)

find_package(GTest CONFIG REQUIRED)
target_link_libraries(target_test PRIVATE GTest::gtest GTest::gtest_main)

enable_testing()
add_test(test_ip_print target_test)