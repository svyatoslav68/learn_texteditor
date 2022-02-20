cmake_minimum_required(VERSION 3.10)

project(TextEditor VERSION 0.0.3)
# version 0.0.3 - уже почти все работает

configure_file(
	${CMAKE_HOME_DIRECTORY}/version.hpp.in
	${CMAKE_CURRENT_BINARY_DIR}/version.hpp
)

set(SOURCE_DIR ${CMAKE_HOME_DIRECTORY}/sources)
set(HEADER_DIR ${CMAKE_HOME_DIRECTORY}/headers)
set(RESOURCES_DIR ${CMAKE_HOME_DIRECTORY}/resources)

message("CMAKE_HOME_DIRECTORY = ${CMAKE_HOME_DIRECTORY}")
message("CMAKE_CURRENT_BINARY_DIR = ${CMAKE_CURRENT_BINARY_DIR}")
message("SOURCE_DIR = ${SOURCE_DIR}")
message("HEADER_DIR = ${HEADER_DIR}")

set(TARGET_APP texteditor)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

file(GLOB SOURCES ${SOURCE_DIR}/*.cpp)
file(GLOB HEADERS ${HEADER_DIR}/*.hpp)
file(GLOB RESOURCES ${RESOURCES_DIR}/*.qrc)

list(APPEND CMAKE_MODULE_PATH $ENV{HOME}/cmake_modules)

add_executable(${TARGET_APP} ${SOURCES} ${HEADERS} ${RESOURCES})

find_package(Qt5 REQUIRED COMPONENTS Widgets Core Gui) 

target_include_directories(${TARGET_APP} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${TARGET_APP} PUBLIC ${HEADER_DIR})

if(Qt5_FOUND)
	message("Qt_LIBRARIES = " ${Qt5_LIBRARIES})
	target_link_libraries(${TARGET_APP} Qt5::Widgets Qt5::Core Qt5::Gui)
else()
	message("Не получится собрать приложение\n, не найден Qt5")
	exit()
endif()

set_target_properties(
	${TARGET_APP} PROPERTIES
	CXX_STANDARD 17	#Собирать в соответствии со стандартом c17
	)
