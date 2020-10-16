cmake_minimum_required(VERSION 3.1.0)

set(PROJECT lab_04)

project(${PROJECT})

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    "gui"
)

set(HEADERS
    include/mainwindow.h
    include/GraphicsBuilder.h
    include/Mathematics.h
)

set(SOURCES
    source/main.cc
    source/mainwindow.cc
    source/GraphicsBuilder.cc
    source/Mathematics.cc
)

set(GUI
    gui/mainwindow.ui
)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5Charts)

add_executable(${PROJECT}
    ${HEADERS}
    ${SOURCES}
    ${FORMS}
)

target_include_directories(${PROJECT}
    PUBLIC
        "include"
)

target_link_libraries(${PROJECT}
    Qt5::Widgets
    Qt5::Charts
)
