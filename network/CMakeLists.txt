cmake_minimum_required(VERSION 3.11)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11 -g3")

SET(INCLUDE_DIRECTORY "./include")
SET(INCLUDE_DIRECTORY_UI "./include/UI")
SET(INCLUDE_DIRECTORY_UI_OBJ "./include/UI/Obj")
SET(INCLUDE_DIRECTORY_UI_SCENE "./include/UI/Scene")

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
include_directories(${INCLUDE_DIRECTORY})

add_executable(
		server

		src/server.cpp
		src/clientS.cpp
		src/room.cpp
		src/word_array.cpp

)

target_link_libraries(server boost_system boost_thread boost_timer pthread)