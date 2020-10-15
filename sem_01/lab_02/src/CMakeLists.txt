cmake_minimum_required(VERSION 3.1.0)

project(lab_02)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    "gui"
)

set(HEADERS
    include/mainwindow.h
    include/Mathematics.h
    include/GraphicsBuilder.h
    include/Interpolation.h
)

set(SOURCES
    source/main.cc
    source/mainwindow.cc
    source/Mathematics.cc
    source/GraphicsBuilder.cc
    source/Interpolation.cc
)

set(GUI
    gui/mainwindow.ui
)

find_package(Qt5 COMPONENTS Widgets REQIURED)
find_package(Qt5Charts)

add_executable(lab_02
    ${HEADERS}
    ${SOURCES}
    ${FORMS}
)

target_include_directories(lab_02
    PUBLIC
        "include"
)

target_link_libraries(lab_02
    Qt5::Widgets
    Qt5::Charts
)
