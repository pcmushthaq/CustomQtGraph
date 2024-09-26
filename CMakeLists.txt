cmake_minimum_required(VERSION 3.16)

project(QCustomGraph VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(QT_QML_OUTPUT_DIRECTORY  ${CMAKE_BINARY_DIR})

find_package(Qt6 6.2 COMPONENTS Quick ShaderTools REQUIRED)

qt_add_library(QCustomGraph STATIC)
qt_add_qml_module(QCustomGraph
    URI QCustomGraph
    VERSION 1.0
    QML_FILES QCustomGraphControls.qml
    SOURCES src/qcustomgraph.cpp src/qcustomgraph.h
    SOURCES src/nodes/linenode.h src/nodes/linenode.cpp
    SOURCES src/series/basegraphseries.h src/series/basegraphseries.cpp
    SOURCES src/series/linegraphseries.h src/series/linegraphseries.cpp
    SOURCES src/series/xypoint.h src/series/xypoint.cpp
    SOURCES src/series/areagraphseries.h src/series/areagraphseries.cpp
    SOURCES src/nodes/areanode.h src/nodes/areanode.cpp
    SOURCES src/axes/baseaxis.h src/axes/baseaxis.cpp
    SOURCES src/axes/valueaxis.h src/axes/valueaxis.cpp
)

qt6_add_shaders(QCustomGraph "GraphLibraryShaders"
    PREFIX
        "/"
    GLSL "310 es,430"
    FILES
        "shaders/line.frag"
        "shaders/line.vert"
)

set_target_properties(QCustomGraph PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_compile_definitions(QCustomGraph
    PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
target_link_libraries(QCustomGraph
    PRIVATE Qt6::Quick)

target_include_directories(QCustomGraph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(QCustomGraph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src)
target_include_directories(QCustomGraph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/series)
target_include_directories(QCustomGraph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/nodes)
target_include_directories(QCustomGraph PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src/axes)

# Example Project
qt_add_executable(ExampleProject example/example.cpp)
qt_add_qml_module(ExampleProject
    URI ExampleProjectApp
    VERSION 1.0
    QML_FILES example/example.qml
)
target_link_libraries(ExampleProject PRIVATE Qt6::Quick QCustomGraphplugin)
target_compile_definitions(ExampleProject PRIVATE $<$<OR:$<CONFIG:Debug>,$<CONFIG:RelWithDebInfo>>:QT_QML_DEBUG>)
