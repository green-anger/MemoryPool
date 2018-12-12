add_executable( simple main.cpp Profiler.cpp Profiler.h )
include_directories( ${CMAKE_CURRENT_SOURCE_DIR} )
target_link_libraries( simple memory_pool )
