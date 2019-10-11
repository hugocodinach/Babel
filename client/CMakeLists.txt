project(Babel)
cmake_minimum_required(VERSION 2.8.12)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

SET(INCLUDE_DIRECTORY "./include")
SET(INCLUDE_DIRECTORY_PORTAUDIO "./include/Client/PortAudio")
SET(INCLUDE_DIRECTORY_OPUS "./include/Client/Opus")
SET(INCLUDE_DIRECTORY_BABEL "./include/Client/Babel")
SET(INCLUDE_DIRECTORY_QT "./include/Client/Qt")
SET(CMAKE_AUTOMOC ON)

include_directories(${INCLUDE_DIRECTORY})
include_directories(${INCLUDE_DIRECTORY_PORTAUDIO})
include_directories(${INCLUDE_DIRECTORY_OPUS})
include_directories(${INCLUDE_DIRECTORY_BABEL})
include_directories(${INCLUDE_DIRECTORY_QT})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)

include_directories(${CMAKE_INCLUDE_PATH})
add_executable(babel_client 
        ./main.cpp
        ./myudp.cpp
        ./myudp.hpp
        ./NetworkClient.cpp
        ./NetworkClient.hpp
        #src/Client/main.cpp
        #src/Client/PortAudio/PortAudio.cpp
        #src/Client/PortAudio/Stream.cpp
        #src/Client/PortAudio/StreamParam.cpp
        #src/Client/Opus/Opus.cpp
        #src/Client/Opus/Encoder.cpp
        #src/Client/Opus/Decoder.cpp
        #src/Client/Babel/Babel.cpp
        #src/Client/Qt/QtBabel.cpp
        )
target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Widgets Qt5::Network boost_system boost_thread boost_timer pthread boost_iostreams)
