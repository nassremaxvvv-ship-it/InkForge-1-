
cmake_minimum_required(VERSION 3.21)

project(InkForge
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
)

qt_add_executable(InkForge
    src/main.cpp
    src/ui/inkforgewindow.h
    src/ui/inkforgewindow.cpp
    src/ui/canvaswidget.h
    src/ui/canvaswidget.cpp
)

target_include_directories(InkForge PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(InkForge PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)
