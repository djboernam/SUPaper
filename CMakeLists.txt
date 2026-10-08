cmake_minimum_required(VERSION 3.20)

project(SUPaper VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
qt_standard_project_setup()

add_executable(SUPaper
    src/app/main.cpp
    src/app/App.cpp
    src/app/App.h

    src/core/Document.cpp
    src/core/Document.h
    src/core/DocumentEngine.cpp
    src/core/DocumentEngine.h
    src/core/GeometryLayer.cpp
    src/core/GeometryLayer.h
    src/core/Layer.cpp
    src/core/Layer.h
    src/core/Project.cpp
    src/core/Project.h
    src/core/Sheet.cpp
    src/core/Sheet.h
    src/core/Viewport.cpp
    src/core/Viewport.h
    src/core/ViewportSystem.cpp
    src/core/ViewportSystem.h

    src/ui/MainWindow.cpp
    src/ui/MainWindow.h

    src/ruby/ExtensionManifest.cpp
    src/ruby/ExtensionManifest.h
    src/ruby/RubyExtensionAPI.cpp
    src/ruby/RubyExtensionAPI.h
    src/ruby/RubyRuntime.cpp
    src/ruby/RubyRuntime.h

    src/rendering/PdfExporter.cpp
    src/rendering/PdfExporter.h
)

target_include_directories(SUPaper PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

target_link_libraries(SUPaper PRIVATE Qt6::Core Qt6::Gui Qt6::Widgets)

set_target_properties(SUPaper PROPERTIES
    WIN32_EXECUTABLE ON
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

install(TARGETS SUPaper RUNTIME DESTINATION bin)

include(InstallRequiredSystemLibraries)

set(CPACK_PACKAGE_NAME "SUPaper")
set(CPACK_PACKAGE_VENDOR "djboernam")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "SketchUp documentation and layout application")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_GENERATOR "ZIP")
include(CPack)
