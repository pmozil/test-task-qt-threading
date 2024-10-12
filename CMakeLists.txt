cmake_minimum_required(VERSION 3.16)

project(threads-demo-petro-mozil VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets)

set(PROJECT_SOURCES
    ${CMAKE_SOURCE_DIR}/src/main.cpp
    ${CMAKE_SOURCE_DIR}/src/numberproducer.cpp
    ${CMAKE_SOURCE_DIR}/src/numberqueue.cpp
    ${CMAKE_SOURCE_DIR}/src/numberconsumer.cpp
    ${CMAKE_SOURCE_DIR}/src/threadsdemowindow.ui
    ${CMAKE_SOURCE_DIR}/src/threadsdemowindow.cpp
    ${CMAKE_SOURCE_DIR}/include/threadsdemowindow.h
    ${CMAKE_SOURCE_DIR}/include/numberproducer.h
    ${CMAKE_SOURCE_DIR}/include/numberqueue.h
    ${CMAKE_SOURCE_DIR}/include/numberconsumer.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(threads-demo-petro-mozil
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET threads-demo-petro-mozil APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
        add_executable(threads-demo-petro-mozil
            ${PROJECT_SOURCES}
        )
endif()

target_link_libraries(threads-demo-petro-mozil PRIVATE Qt${QT_VERSION_MAJOR}::Core
                                                       Qt${QT_VERSION_MAJOR}::Gui
                                                       Qt${QT_VERSION_MAJOR}::Widgets
)

target_include_directories(threads-demo-petro-mozil PRIVATE ${CMAKE_SOURCE_DIR}/include)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.threads-demo-petro-mozil)
endif()
set_target_properties(threads-demo-petro-mozil PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS threads-demo-petro-mozil
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(threads-demo-petro-mozil)
endif()

# set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=thread")
