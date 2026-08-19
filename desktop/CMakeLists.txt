cmake_minimum_required(VERSION 3.20)
project(DevSecArch-Desktop VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# Find Qt packages
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

# Source files
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
)

# Header files
set(HEADERS
    src/mainwindow.h
    src/dashboard.h
    src/filemanager.h
    src/texteditor.h
    src/securitytools.h
    src/terminal.h
    src/settings.h
    src/about.h
)

# Resource files
set(RESOURCES
    resources/resources.qrc
)

# Create executable
add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${RESOURCES}
)

# Link Qt libraries
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

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE src)

# Install rules
install(TARGETS ${PROJECT_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
