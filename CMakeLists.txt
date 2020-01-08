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

add_library(${PROJECT_NAME} SHARED ${GODOT_TOOLS_SRC} ${GODOT_TOOLS_HEADERS})
set_property(TARGET ${PROJECT_NAME} PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(${PROJECT_NAME}
    ${GODOT_CPP_LIB}
    godot-cpp
)

# create the library directly in the right folder
set_target_properties(${PROJECT_NAME} PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
    
set(BITS 32)
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(BITS 64)
endif(CMAKE_SIZEOF_VOID_P EQUAL 8)

string(TOLOWER ${CMAKE_SYSTEM_NAME} SYSTEM_NAME)
# string(TOLOWER ${CMAKE_BUILD_TYPE} BUILD_TYPE)

if(ANDROID)
	# Added the android abi after system name
	set(SYSTEM_NAME ${SYSTEM_NAME}.${ANDROID_ABI})
	# Android does not have the bits at the end if you look at the main godot repo build
	set_property(TARGET ${PROJECT_NAME} PROPERTY OUTPUT_NAME "${PROJECT_NAME}.${SYSTEM_NAME}")
else()
	set_property(TARGET ${PROJECT_NAME} PROPERTY OUTPUT_NAME "${PROJECT_NAME}.${SYSTEM_NAME}.${BITS}")
endif()
