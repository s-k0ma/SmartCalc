cmake_minimum_required(VERSION 3.22)
project(helloQt)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Check the system type and update the prefix path accordingly
if(UNIX)
    # This is Linux
    set(CMAKE_PREFIX_PATH "/opt/qt/6.6.0/gcc_64/lib/cmake")
elseif(APPLE)
    # This is macOS
    set(CMAKE_PREFIX_PATH "/usr/local/Cellar/qt/6.2.3/bin/")
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets PrintSupport)
qt6_add_resources(QT_RESOURCES qrc/qrc.qrc)

set(PROJECT_SOURCES
        main.cc
        Calculator.cc
        Calculator.h
        Graph.cc
        Graph.h
        MainWindow.cc
        MainWindow.h
        qcustomplot.cpp
        qcustomplot.h
        Deposit.cc
        Deposit.h
        Credit.cc
        Credit.h
        DifferCredit.cc
        DifferCredit.h
        DepositReport.cc
        DepositReport.h
        #backend
        "../backend/types.h"
        "../backend/types.c"
        "../backend/calc.h"
        "../backend/calc.c"
        "../backend/parser.h"
        "../backend/parser.c"
        "../backend/bank.c"
        "../backend/bank.h"
        )

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(helloQt
            MANUAL_FINALIZATION
            ${PROJECT_SOURCES}
            ${QT_RESOURCES}
            )
    # Define target properties for Android with Qt 6 as:
    #    set_property(TARGET helloQt APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
    #                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
    # For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(helloQt SHARED
                ${PROJECT_SOURCES}
                ${QT_RESOURCES}
                )
        # Define properties for Android with Qt 5 after find_package() calls as:
        #    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(helloQt
                ${PROJECT_SOURCES}
                ${QT_RESOURCES}
                )
    endif()
endif()
target_link_libraries(helloQt PRIVATE Qt${QT_VERSION_MAJOR}::PrintSupport)

target_link_libraries(helloQt PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(helloQt)
endif()