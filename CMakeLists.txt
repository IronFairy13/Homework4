cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(homework_2 VERSION ${PROJECT_VERSION})

option(WITH_GTEST "Whether to build GTest test" ON)

configure_file(version.h.in version.h)

add_executable(ip_filter main.cpp)
add_library(homework_2 lib.cpp ipv4.cpp)

set_target_properties(ip_filter homework_2 PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(homework_2
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(ip_filter PRIVATE
    homework_2
)

if(WITH_GTEST)
    find_package(GTest REQUIRED)
    add_executable(test_ip test_ip.cpp  ipv4.cpp)

    set_target_properties(test_ip PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
    )

    target_link_libraries(test_ip
        GTest::gtest
        GTest::gtest_main
        homework_2
    )
endif()

if (MSVC)
    target_compile_options(ip_filter PRIVATE
        /W4
    )
    target_compile_options(homework_2 PRIVATE
        /W4
    )
    if(WITH_GTEST)
        target_compile_options(test_ip PRIVATE
            /W4
        )
    endif()
else ()
    target_compile_options(ip_filter PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(homework_2 PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    if(WITH_GTEST)
        target_compile_options(test_ip PRIVATE
            -Wall -Wextra -pedantic -Werror
        )
    endif()
endif()

install(TARGETS ip_filter RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT savchenko.mn.dev@gmail.com)
include(CPack)

if(WITH_GTEST)
    enable_testing()
    add_test(NAME test_ip COMMAND test_ip)
endif()
