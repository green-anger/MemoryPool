cmake_minimum_required( VERSION 3.0 )
project( MemoryPool )

set( CMAKE_CXX_STANDARD 11)
set( CMAKE_CXX_STANDARD_REQUIRED ON )
if ( MSVC )
    add_compile_options( "/std:c++11" )
else()
    add_compile_options( -std=c++11 )
endif()

option( BUILD_EXAMPLES OFF )

add_subdirectory( lib )

if ( ${BUILD_EXAMPLES} )
    add_subdirectory( examples )
endif()
