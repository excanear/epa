cmake_minimum_required(VERSION 3.13)
project(epa C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)

add_compile_options(-Wall -Wextra)

add_executable(epa-init
    core/src/init.c
    core/src/log.c
    cli/src/shell.c
)

target_include_directories(epa-init PRIVATE
    core/include
    cli/include
)

install(TARGETS epa-init RUNTIME DESTINATION bin)

if(EPA_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests/unit)
endif()
