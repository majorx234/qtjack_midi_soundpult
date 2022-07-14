cmake_minimum_required(VERSION 2.6)
PROJECT(qtjack_midi_soundpult)

set(CMAKE_AUTOMOC ON)
find_package(Qt4 COMPONENTS QTCORE QTGUI PHONON)
find_package(yaml-cpp)
INCLUDE(${QT_USE_FILE})

QT4_WRAP_UI(UISrcs src/mainwindow.ui)
QT4_WRAP_CPP(MOCSrcs include/mainwindow.h)
QT4_WRAP_CPP(MOCSrcs include/instruments_list.h)
QT4_WRAP_CPP(MOCSrcs include/soundpult_widget.h)
QT4_WRAP_CPP(MOCSrcs include/sound_dispatcher.h)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)
 
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})
 
set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)

include_directories("${PROJECT_INCLUDE_DIR}")
include_directories("${PROJECT_SOURCE_DIR}")
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include ${CMAKE_CURRENT_BINARY_DIR})
include_directories(${YAML_CPP_INCLUDE_DIR})
 
ADD_EXECUTABLE(qt_midi_soundpult
  ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/mainwindow.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/soundpult_widget.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/instruments_list.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/sound_dispatcher.cpp
  ${MOCSrcs}
  ${UISrcs})

TARGET_LINK_LIBRARIES(qt_midi_soundpult ${QT_QTMAIN_LIBRARY} ${QT_LIBRARIES} ${YAML_CPP_LIBRARIES})
