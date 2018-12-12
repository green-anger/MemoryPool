set( HEADERS_ROOT "${CMAKE_CURRENT_SOURCE_DIR}" )

set( HDRS
    ${HEADERS_ROOT}/MemPool.hpp
)

add_library( memory_pool INTERFACE )

target_include_directories( memory_pool INTERFACE ${HEADERS_ROOT} )
