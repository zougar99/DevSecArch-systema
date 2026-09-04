cmake_minimum_required(VERSION 3.20)
project(ForxoOS-Desktop VERSION 2.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS
    Core
    Gui
    Widgets
    Network
    Sql
    Svg
    Xml
    Charts
    Concurrent
)

set(SOURCES
    src/main.cpp
    src/mainwindow.cpp
    src/dashboard.cpp
    src/filemanager.cpp
    src/texteditor.cpp
    src/securitytools.cpp
    src/terminal.cpp
    src/settings.cpp
    src/about.cpp
    src/forxostore.cpp
    src/iosstatusbar.cpp
    src/iosdock.cpp
    src/ioshome.cpp
    src/ioscontrolcenter.cpp
    src/ioslockscreen.cpp
    src/iossettings.cpp
    src/iosshell.cpp
)

set(HEADERS
    src/mainwindow.h
    src/dashboard.h
    src/filemanager.h
    src/texteditor.h
    src/securitytools.h
    src/terminal.h
    src/settings.h
    src/about.h
    src/forxostore.h
    src/iosstatusbar.h
    src/iosdock.h
    src/ioshome.h
    src/ioscontrolcenter.h
    src/ioslockscreen.h
    src/iossettings.h
    src/iosshell.h
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Network
    Qt6::Sql
    Qt6::Svg
    Qt6::Xml
    Qt6::Charts
    Qt6::Concurrent
)

target_include_directories(${PROJECT_NAME} PRIVATE src)

install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
