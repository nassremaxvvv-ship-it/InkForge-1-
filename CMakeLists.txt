cmake_minimum_required(VERSION 3.16)
project(InkForgeEngine VERSION 0.1.0 LANGUAGES CXX)

option(INKFORGE_BUILD_TESTS "Build engine tests" ON)

add_library(inkforge_engine
    src/document.cpp
    src/brush.cpp
)
target_include_directories(inkforge_engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_features(inkforge_engine PUBLIC cxx_std_17)

if(INKFORGE_BUILD_TESTS)
    enable_testing()
    add_executable(inkforge_engine_smoke tests/smoke.cpp)
    target_link_libraries(inkforge_engine_smoke PRIVATE inkforge_engine)
    add_test(NAME inkforge_engine_smoke COMMAND inkforge_engine_smoke)
endif()
