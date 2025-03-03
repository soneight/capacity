cmake_minimum_required(VERSION 3.14...3.28)
project(capacity VERSION 0.0.0 LANGUAGES CXX)

set(SON8PROJ son8__${PROJECT_NAME})

add_subdirectory(source)
add_library(son8::${PROJECT_NAME} ALIAS ${SON8PROJ})
target_include_directories(${SON8PROJ} INTERFACE include)
target_compile_features(${SON8PROJ} INTERFACE cxx_std_17)

if (EXISTS "${CMAKE_SOURCE_DIR}/temp/CMakeLists.txt")
    add_subdirectory(temp)
endif()
