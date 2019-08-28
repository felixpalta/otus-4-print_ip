cmake_minimum_required(VERSION 3.2)


if(DEFINED ENV{TRAVIS_BUILD_NUMBER})
    set(TRAVIS_BUILD_CMAKE_VAR $ENV{TRAVIS_BUILD_NUMBER})
else()
    set(TRAVIS_BUILD_CMAKE_VAR 999)
endif()

project(print_ip VERSION 0.0.${TRAVIS_BUILD_CMAKE_VAR})

message("Version ${PROJECT_VERSION_MAJOR} ${PROJECT_VERSION_MINOR} ${PROJECT_VERSION_PATCH}")

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
add_subdirectory(./googletest)

add_executable(print_ip "main.cpp")
add_library(print_ip_lib "lib.cpp")
add_executable(tests_default tests_default.cpp)

set_target_properties(print_ip print_ip_lib tests_default PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
)

target_link_libraries(print_ip PRIVATE
    print_ip_lib
)
target_link_libraries(tests_default PRIVATE
    gtest_main
    print_ip_lib
)

if (MSVC)
    target_compile_options(print_ip PRIVATE
        /W4
    )
    target_compile_options(print_ip_lib PRIVATE
        /W4
    )
else ()
    target_compile_options(print_ip PRIVATE
        -Wall -Wextra -pedantic
    )
    target_compile_options(print_ip_lib PRIVATE
        -Wall -Wextra -pedantic
    )
endif()

enable_testing()

add_test(tests_default tests_default)

install(TARGETS print_ip RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT "Felix Palta <my@email.com>")

include(CPack)
