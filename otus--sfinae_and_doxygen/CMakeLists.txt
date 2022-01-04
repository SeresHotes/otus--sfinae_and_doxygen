cmake_minimum_required (VERSION 3.12)

project(print_ip)

add_executable (print_ip "main.cpp"  "ip_gen.h")
add_executable (target_test "test.cpp")
 
set_property(TARGET print_ip PROPERTY CXX_STANDARD 17)
set_property(TARGET target_test PROPERTY CXX_STANDARD 17)


if (MSVC)
    target_compile_options(print_ip PRIVATE
        /W4 
    )
    target_compile_options(target_test PRIVATE
        /W4 
    )
else ()
    target_compile_options(print_ip PRIVATE
        -Wall -Wextra -pedantic -Werror -pedantic-errors -Wextra-semi
    )
    target_compile_options(target_test PRIVATE
        -Wall -Wextra -pedantic -Werror -pedantic-errors -Wextra-semi
    ) 
endif()




find_package(GTest REQUIRED)
target_link_libraries(target_test PRIVATE GTest::gtest GTest::gtest_main)
 
enable_testing()
add_test(test_ip_print target_test)

################################################################
#### Packaging #################################################
################################################################

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT example@example.com)

include(CPack)
