cmake_minimum_required(VERSION 3.20)
project(Pong)

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 17)

find_package(raylib REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} raylib)

if (EMSCRIPTEN)
    set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX .html)
    target_link_options(${PROJECT_NAME}
                        PRIVATE
                        -sALLOW_MEMORY_GROWTH=1
                        -sUSE_GLFW=3
                        -sEXPORTED_RUNTIME_METHODS=[requestFullscreen]
    )
endif ()

if (WIN32)
    target_link_libraries(${PROJECT_NAME} gdi32 winmm)
    set(COMPILE_FLAGS "/NODEFAULTLIB:libcmt")
endif ()

install(TARGETS ${PROJECT_NAME})
