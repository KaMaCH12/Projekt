cmake_minimum_required(VERSION 2.8)

project(SpaceCommander)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

include_directories(${SFML_INCLUDE_DIR}
	include)

file(GLOB SOURCES "src/*.c")

add_executable(${PROJECT_NAME} ${SOURCES})

target_compile_features(${PROJECT_NAME} PUBLIC c_std_11)

find_package(SFML 2 REQUIRED graphics window audio system)

target_link_libraries(SpaceCommander
	${SFML_LIBRARIES}
	${SFML_DEPENDENCIES})
