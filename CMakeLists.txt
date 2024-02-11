cmake_minimum_required(VERSION 3.16)
project(Vimrc-Helper LANGUAGES CXX)

include(qt.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR}
    COMPONENTS
        Core
        Gui
        Widgets
)
qt_standard_project_setup()

set(PROJECT_SOURCES
    main.cpp
    Mainwindow.ui
    Mainwindow.h
    Mainwindow.cpp
    vimrc_helper.qrc
)

qt_add_executable(Vimrc-Helper ${PROJECT_SOURCES})

set_target_properties(Vimrc-Helper
    PROPERTIES
        WIN32_EXECUTABLE TRUE
)

target_link_libraries(Vimrc-Helper
    PUBLIC
        Qt::Core
        Qt::Gui
        Qt::Widgets
)
