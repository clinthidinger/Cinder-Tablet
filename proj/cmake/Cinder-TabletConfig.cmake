if( NOT TARGET Cinder-Tablet )
    get_filename_component( Cinder-Tablet_INC_PATH "${CMAKE_CURRENT_LIST_DIR}/../../include" ABSOLUTE )
    get_filename_component( Cinder-Tablet_SOURCE_PATH "${CMAKE_CURRENT_LIST_DIR}/../../src" ABSOLUTE )

    set( Cinder-Tablet_INCLUDES
        ${Cinder-Tablet_INC_PATH}/CinderTablet.h
        ${Cinder-Tablet_INC_PATH}/TabletData.h
        ${Cinder-Tablet_INC_PATH}/CinderTabletApp.h
    )

    set( Cinder-Tablet_SOURCES
        ${Cinder-Tablet_SOURCE_PATH}/CinderTablet.cpp
        ${Cinder-Tablet_SOURCE_PATH}/CinderTabletApp.cpp
    )

    source_group( "src" FILES ${Cinder-Tablet_SOURCES} )
    source_group( "include" FILES ${Cinder-Tablet_INCLUDES} )

    if( CINDER_MAC )
        set( Cinder-Tablet_OSX_INCLUDES
            ${Cinder-Tablet_INC_PATH}/osx/TabletCocoa.h
        )
        set( Cinder-Tablet_OSX_SOURCES
            ${Cinder-Tablet_SOURCE_PATH}/osx/TabletCocoa.mm
        )
        list( APPEND Cinder-Tablet_INCLUDES
            ${Cinder-Tablet_OSX_INCLUDES}
        )
        list( APPEND Cinder-Tablet_SOURCES
            ${Cinder-Tablet_OSX_SOURCES}
        )
        source_group( "src\\osx" FILES ${Cinder-Tablet_OSX_SOURCES} )
        source_group( "include\\osx" FILES ${Cinder-Tablet_OSX_INCLUDES} )
    elseif( CINDER_MSW ) 
        set( Cinder-Tablet_WINTAB_INCLUDES
            ${Cinder-Tablet_INC_PATH}/wintab/TabletWinTab.h
        )
        set( Cinder-Tablet_WINTAB_SOURCES
            ${Cinder-Tablet_SOURCE_PATH}/wintab/TabletWinTab.cpp
        )
        list( APPEND Cinder-Tablet_INCLUDES
            ${Cinder-Tablet_WINTAB_INCLUDES}
        )
        list( APPEND Cinder-Tablet_SOURCES
            ${Cinder-Tablet_WINTAB_SOURCES}
        )
        source_group( "src\\wintab" FILES ${Cinder-Tablet_WINTAB_SOURCES} )
        source_group( "include\\wintab" FILES ${Cinder-Tablet_WINTAB_INCLUDES} )
    elseif( CINDER_COCOA_TOUCH ) #IOS
    endif()

    list( APPEND Cinder-Tablet_LIBRARIES
        ${Cinder-Tablet_INCLUDES}
        ${Cinder-Tablet_SOURCES}
    )

    add_library( Cinder-Tablet ${Cinder-Tablet_LIBRARIES} )
    target_include_directories( Cinder-Tablet PUBLIC "${CINDER_PATH}/include" ${Cinder-Tablet_INC_PATH} )

endif()
