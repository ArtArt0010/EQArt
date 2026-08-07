cmake_minimum_required(VERSION 3.16)

project(EQ_Art VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)
find_package(Qt6 REQUIRED COMPONENTS Multimedia)

qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(appEQ_Art
    main.cpp
)

qt_add_qml_module(appEQ_Art
    URI EQ_Art
    QML_FILES
        Main.qml
        SOURCES audioinput.h audioinput.cpp
        SOURCES audioprocessor.h audioprocessor.cpp
        SOURCES ringbuffer.h ringbuffer.cpp
        SOURCES waveformview.h waveformview.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appEQ_Art PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appEQ_Art
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appEQ_Art
    PRIVATE
        Qt6::Quick
        Qt6::Multimedia
)

include(GNUInstallDirs)
install(TARGETS appEQ_Art
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
