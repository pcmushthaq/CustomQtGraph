cmake_minimum_required(VERSION 3.16)

project(GraphLibraryTest VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_QML_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR})

find_package(Qt6 6.5 COMPONENTS Quick ShaderTools REQUIRED)

qt_add_library(GraphLibraryTest STATIC)
qt_add_qml_module(GraphLibraryTest
    URI GraphLibraryTest
    VERSION 1.0
    QML_FILES QCustomGraphControls.qml
    SOURCES qcustomgraph.cpp qcustomgraph.h
    SOURCES linenode.h linenode.cpp
)

qt6_add_shaders(GraphLibraryTest "GraphLibraryShaders"
    PREFIX
        "/"
    GLSL "310 es,430"
    FILES
        "shaders/line.frag"
        "shaders/line.vert"
)

set_target_properties(GraphLibraryTest PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(GraphLibraryTest
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(GraphLibraryTest
    PRIVATE Qt6::Quick)

target_include_directories(GraphLibraryTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Example Project
qt_add_executable(ExampleProject example/example.cpp)
qt_add_qml_module(ExampleProject
    URI ExampleProjectApp
    VERSION 1.0
    QML_FILES example/example.qml
)
target_link_libraries(ExampleProject PRIVATE Qt6::Quick GraphLibraryTestplugin)
target_compile_definitions(ExampleProject PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
