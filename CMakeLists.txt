cmake_minimum_required(VERSION 3.20)
project(Pong)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} raylib)
install(TARGETS ${PROJECT_NAME})

if (WIN32)
    target_include_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_PATH}/include)
    target_link_directories(${PROJECT_NAME} PRIVATE ${RAYLIB_PATH}/lib)
    target_link_libraries(${PROJECT_NAME} gdi32 msvcrt winmm)
    set(COMPILE_FLAGS "/NODEFAULTLIB:libcmt")
endif ()
