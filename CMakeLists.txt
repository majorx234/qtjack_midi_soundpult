cmake_minimum_required(VERSION 3.16)
PROJECT(qtjack_midi_soundpult)

set(CMAKE_AUTOMOC ON)
find_package(Qt5 COMPONENTS Core Widgets Gui REQUIRED)
find_package(Phonon4Qt5 REQUIRED)
find_package(yaml-cpp)

QT5_WRAP_UI(UISrcs
  ${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.ui)
QT5_WRAP_CPP(MOCSrcs
  ${CMAKE_CURRENT_SOURCE_DIR}/include/mainwindow.h)
QT5_WRAP_CPP(MOCSrcs
  ${CMAKE_CURRENT_SOURCE_DIR}/include/instruments_list.h)
QT5_WRAP_CPP(MOCSrcs
  ${CMAKE_CURRENT_SOURCE_DIR}/include/soundpult_widget.h)
QT5_WRAP_CPP(MOCSrcs
  ${CMAKE_CURRENT_SOURCE_DIR}/include/sound_dispatcher.h)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

#include_directories("${PROJECT_INCLUDE_DIR}")
#include_directories("${PROJECT_SOURCE_DIR}")
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR})

add_executable(qt_midi_soundpult)
target_sources(qt_midi_soundpult
 PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/soundpult_widget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/instruments_list.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/sound_dispatcher.cpp
  ${MOCSrcs}
  ${UISrcs})
target_include_directories(qt_midi_soundpult
 PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/include
  ${CMAKE_CURRENT_BINARY_DIR}
 PRIVATE
  ${YAML_CPP_INCLUDE_DIR}
)
target_link_libraries(qt_midi_soundpult
  PRIVATE
  Qt5::Core
  Qt5::Widgets
  ${PHONON_LIBRARY}
  ${YAML_CPP_LIBRARIES}
)
