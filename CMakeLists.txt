cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(JLMG CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(SOURCES src/main.cpp include/Database.hpp src/Database.cpp)

add_executable(JLMG ${SOURCES})

target_compile_options(JLMG PRIVATE
        -Wall -Werror -Wextra -pedantic-errors -Wcast-align -Wcast-qual
        -Wdisabled-optimization -Wformat=2 -Wlogical-op
        -Wmissing-declarations -Wmissing-include-dirs -Wredundant-decls
        -Wshadow -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused
        -Wpadded -Wno-error=padded)

#if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR  CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
target_compile_options(JLMG PRIVATE
        -Wall -Werror -Wextra -pedantic-errors -Wcast-align -Wcast-qual
        -Wdisabled-optimization -Wformat=2 -Wlogical-op
        -Wmissing-declarations -Wmissing-include-dirs -Wredundant-decls
        -Wshadow -Wstrict-overflow=5 -Wswitch-default -Wundef -Wno-unused
        -Wpadded -Wno-error=padded)
#elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Intel")
#elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
#endif()

find_package(SDL2 REQUIRED)
find_package(SQLite3 REQUIRED)

target_include_directories(JLMG PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(JLMG PRIVATE ${SQLite3_INCLUDE_DIRS})
target_include_directories(JLMG PRIVATE ${SDL2_INCLUDE_DIR})

target_link_libraries(JLMG PRIVATE stdc++)
target_link_libraries(JLMG PRIVATE ${SQLite3_LIBRARIES})
target_link_libraries(JLMG PRIVATE ${SDL2_LIBRARY})

# We need to copy the default word database to the executable directory after building
add_custom_command(TARGET JLMG POST_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy
                   "${PROJECT_SOURCE_DIR}/resources/wordbank.db"
                   $<TARGET_FILE_DIR:JLMG>)
