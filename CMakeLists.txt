cmake_minimum_required( VERSION 3.1 )

project( OPENGL_TEST )

find_package( OpenGL REQUIRED )
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories( ${OPENGL_INCLUDE_DIRS} )

set( GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only" )
set( GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only" )
set( GLAD_GL "" )
set (IMGUI "" )

add_subdirectory( glfw )

option( GLFW-CMAKE-STARTER-USE-GLFW-GLAD "Use GLAD from GLFW" ON )

if( GLFW-CMAKE-STARTER-USE-GLFW-GLAD )
    include_directories("${GLFW_SOURCE_DIR}/deps")
    set( GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h" )
endif()
include_directories(
        "Linking/include"
)

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()


#files
file(GLOB SOURCES *.cpp *.c imgui/*)

set( GLFW-CMAKE-STARTER-SRC
        main.cpp
        )

add_executable( OPENGL_TEST WIN32 ${SOURCES} ${GLAD_GL})
target_link_libraries( OPENGL_TEST
        ${OPENGL_LIBRARIES}
        glfw
)
if( MSVC )
    if(${CMAKE_VERSION} VERSION_LESS "3.6.0")
        message( "\n\t[ WARNING ]\n\n\tCMake version lower than 3.6.\n\n\t - Please update CMake and rerun; OR\n\t - Manually set 'GLFW-CMake-starter' as StartUp Project in Visual Studio.\n" )
    else()
        set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT GLFW-CMake-starter )
    endif()
endif()
