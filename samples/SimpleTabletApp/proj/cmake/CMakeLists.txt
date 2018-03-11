cmake_minimum_required( VERSION 2.8 FATAL_ERROR )
set( CMAKE_VERBOSE_MAKEFILE ON )
set( CMAKE_CXX_STANDARD 17 )

project( SimpleTabletApp )

get_filename_component( CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../Cinder" ABSOLUTE )
get_filename_component( APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../.." ABSOLUTE )
get_filename_component( ARG_ASSETS_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../../assets" ABSOLUTE )

include( "${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake" )

set( SRC_FILES
	${APP_PATH}/src/SimpleTabletApp.cpp
)

set( RESOURCE_FILES

)

function(makeGroups fileList)
	foreach(FILE ${fileList}) 
	    # Get the directory of the source file
	    get_filename_component(PARENT_DIR "${FILE}" DIRECTORY)
	    # Remove common directory prefix to make the group
	    string(REPLACE "${APP_PATH}" "" GROUP "${PARENT_DIR}")
	    # Make sure we are using windows slashes
	    string(REPLACE "/" "\\" GROUP "${GROUP}")
	    source_group("${GROUP}" FILES "${FILE}")
	endforeach()
endfunction()

makeGroups("${SRC_FILES}")
makeGroups("${RESOURCE_FILES}")

set( INC_PATHS
	${APP_PATH}
	${APP_PATH}/src
)

get_filename_component( JUNK_PATH "${APP_PATH}/../../../Cinder-Tablet" ABSOLUTE )
message(${JUNK_PATH})

get_filename_component( blockModuleDir2 "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../Cinder-Tablet/proj/cmake" ABSOLUTE )
message(${blockModuleDir2})

set( BLOCK_FILES
    ../../../../../Cinder-Tablet
	#Blocks/PSDLite
)

set( LIB_FILES

)

if( APPLE AND ( TARGET_OS_IPHONE OR TARGET_IPHONE_SIMULATOR ) )
	find_library(UIKIT UIKit)
	if(NOT UIKIT)
  		message(FATAL_ERROR "UIKit library not found")
	endif()
	set( LIB_FILES
		"-framework UIKit"
	)
	#message(${UIKIT_INCLUDE_DIR})
endif()

ci_make_app(
    INCLUDES    ${INC_PATHS}
	SOURCES     ${SRC_FILES}
	LIBRARIES   ${LIB_FILES}
	BLOCKS      ${BLOCK_FILES}
	RESOURCES   ${RESOURCE_FILES}
	CINDER_PATH ${CINDER_PATH}
)

#target_compile_options( PaintApp PUBLIC "-std=c++14" )
