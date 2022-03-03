cmake_minimum_required(VERSION 3.10)

project(TextEditor VERSION 0.0.4)
# version 0.0.4 - теперь уже имеется то, что нужно был сделать к уроку 8

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

find_package(Qt6 COMPONENTS Widgets Core Gui PrintSupport) 
find_package(Qt5 COMPONENTS Widgets Core Gui PrintSupport) 

target_include_directories(${TARGET_APP} PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
target_include_directories(${TARGET_APP} PUBLIC ${HEADER_DIR})

if(Qt6_FOUND)
	message("Found Qt6 libraries")
	message("Qt_LIBRARIES = " ${Qt6Widgets_LIBRARIES})
	target_link_libraries(${TARGET_APP} Qt6::Widgets Qt6::Core Qt6::Gui Qt6::PrintSupport)
else()
	if(Qt5_FOUND)
		message("Found Qt5 libraries")
		message("Qt_LIBRARIES = " ${Qt5Widgets_LIBRARIES})
		#	qt5_add_resources(SOURCES ${RESOURCES})
		target_link_libraries(${TARGET_APP} Qt5::Widgets Qt5::Core Qt5::Gui Qt5::PrintSupport)
	else()
		message("Не получится собрать приложение\n, не найден Qt")
		exit()
	endif()
endif()

set_target_properties(
	${TARGET_APP} PROPERTIES
	CXX_STANDARD 17	#Собирать в соответствии со стандартом c17
	)
