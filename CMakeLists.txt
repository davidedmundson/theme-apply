project(plasma-desktop)
set(PROJECT_VERSION "5.1.90")
set(PROJECT_VERSION_MAJOR 5)

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)
set(QT_MIN_VERSION "5.3.0")

find_package(ECM 1.0.0 REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${ECM_MODULE_PATH} ${ECM_KDE_MODULE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include(ECMInstallIcons)
include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings)
include(FeatureSummary)

find_package(Qt5 ${QT_MIN_VERSION} CONFIG REQUIRED COMPONENTS
    Core
    Gui
    DBus
)

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS
    WindowSystem
)

add_definitions(-Wall -std=c++11 )


set(pager_SRCS
        main.cpp
        abstracttask.cpp
        wmthemetask.cpp
        wallpapertask.cpp)

add_executable(theme-apply ${pager_SRCS})

target_compile_definitions(theme-apply PRIVATE -DQT_NO_KEYWORDS)

target_link_libraries(theme-apply
                      Qt5::Core
                      Qt5::Gui
                      KF5::WindowSystem)
