cmake_minimum_required(VERSION 3.20)
project(ArchInstall-GUI VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)

set(SOURCES
    src/main.cpp
    src/installer.cpp
    src/welcome.cpp
    src/language.cpp
    src/keyboard.cpp
    src/partition.cpp
    src/userinfo.cpp
    src/desktop.cpp
    src/summary.cpp
    src/installing.cpp
    src/complete.cpp
)

set(HEADERS
    src/installer.h
    src/welcome.h
    src/language.h
    src/keyboard.h
    src/partition.h
    src/userinfo.h
    src/desktop.h
    src/summary.h
    src/installing.h
    src/complete.h
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
)

target_include_directories(${PROJECT_NAME} PRIVATE src)
