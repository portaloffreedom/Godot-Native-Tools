cmake_minimum_required(VERSION 3.0.2)
project(godot_tools)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(thirdparty/godot-cpp/)

if(MSVC)
    # Force to always compile with W4
    if(CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
        string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
    endif()
elseif(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
endif()

set(GODOT_TOOLS_SRC
	src/gdlibrary.cpp
	src/free_camera_controller.cpp
)
set(GODOT_TOOLS_HEADERS
	src/free_camera_controller.h
)

set(BUILD_PATH ${CMAKE_SOURCE_DIR}/bin)

add_library(godot_tools SHARED ${GODOT_TOOLS_SRC} ${GODOT_TOOLS_HEADERS})
set_property(TARGET godot_tools PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(godot_tools
    ${GODOT_CPP_LIB}
    godot-cpp
)

# create the library directly in the right folder
set_target_properties(godot_tools PROPERTIES
	LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)