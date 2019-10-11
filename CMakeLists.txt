project(Babel)
cmake_minimum_required(VERSION 2.8.12)

SET(GCC_COVERAGE_COMPILE_FLAGS "-std=c++11")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})
#add_definitions(-DQT_NO_VERSION_TAGGING)

SET(INCLUDE_DIRECTORY "./include")
SET(INCLUDE_DIRECTORY_UDP "./client")
SET(INCLUDE_DIRECTORY_AUDIO "./include/Client/Audio")
SET(INCLUDE_DIRECTORY_COMPRESSOR "./include/Client/Compressor")
SET(INCLUDE_DIRECTORY_BABEL "./include/Client/Babel")
SET(INCLUDE_DIRECTORY_QT "./include/Client/Qt")
SET(CMAKE_AUTOMOC ON)

include_directories(${INCLUDE_DIRECTORY})
include_directories(${INCLUDE_DIRECTORY_UDP})
include_directories(${INCLUDE_DIRECTORY_AUDIO})
include_directories(${INCLUDE_DIRECTORY_COMPRESSOR})
include_directories(${INCLUDE_DIRECTORY_BABEL})
include_directories(${INCLUDE_DIRECTORY_QT})

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
find_package(Qt5Widgets CONFIG REQUIRED)
find_package(Qt5Network CONFIG REQUIRED)
find_package(Qt5Multimedia CONFIG REQUIRED)
find_package(Qt5Core REQUIRED)

include_directories(${CMAKE_INCLUDE_PATH})
add_executable(babel_client
        client/myudp.cpp
        client/NetworkClient.cpp
        src/Client/main.cpp
        src/Client/Audio/Audio.cpp
        src/Client/Audio/Stream.cpp
        src/Client/Audio/StreamParam.cpp
        src/Client/Compressor/Compressor.cpp
        src/Client/Compressor/Encoder.cpp
        src/Client/Compressor/Decoder.cpp
        src/Client/Babel/Babel.cpp
        src/Client/Babel/WindowConnection.cpp
        src/Client/Babel/WindowDaugio.cpp
        src/Client/Babel/WindowProgram.cpp
        src/Client/Babel/CallButton.cpp
        src/Client/Qt/QtBabel.cpp
        src/Client/Qt/AbstractWindow.cpp
        src/Client/Qt/TextField.cpp

        client/myudp.hpp
        client/NetworkClient.hpp
        include/Client/Babel/WindowConnection.hpp
        include/Client/Babel/WindowDaugio.hpp
        include/Client/Babel/CallButton.hpp
        include/Client/Qt/TextField.hpp
        )
target_link_libraries(babel_client ${CONAN_LIBS} Qt5::Widgets Qt5::Network Qt5::Core Qt5::Multimedia boost_system boost_thread boost_timer pthread boost_iostreams)
