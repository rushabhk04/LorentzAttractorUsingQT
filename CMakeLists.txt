cmake_minimum_required(VERSION 3.5)

project(LorentzAttractor VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find required Qt packages
find_package(Qt6 COMPONENTS Widgets Charts DataVisualization REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
)

if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    qt_add_executable(LorentzAttractor
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
else()
    if(ANDROID)
        add_library(LorentzAttractor SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(LorentzAttractor
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Link against Qt libraries
target_link_libraries(LorentzAttractor PRIVATE
    Qt6::Widgets
    Qt6::Charts
    Qt6::DataVisualization
)

# Set target properties as needed
if(QT_VERSION_MAJOR GREATER_EQUAL 6)
    qt_finalize_executable(LorentzAttractor)
endif()

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(QT_VERSION LESS_EQUAL 6)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.LorentzAttractor)
endif()
set_target_properties(LorentzAttractor PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS LorentzAttractor
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
