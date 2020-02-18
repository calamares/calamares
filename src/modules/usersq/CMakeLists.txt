find_package( Qt5 COMPONENTS Core REQUIRED )
find_package( Crypt REQUIRED )

# Add optional libraries here
set( USER_EXTRA_LIB )
set( _users ${CMAKE_CURRENT_SOURCE_DIR}/../usersq )

include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui ${CMAKE_CURRENT_SOURCE_DIR}/../../libcalamares ${_users} )


find_package( LibPWQuality )
set_package_properties(
    LibPWQuality PROPERTIES
    PURPOSE "Extra checks of password quality"
)

if( LibPWQuality_FOUND )
    list( APPEND USER_EXTRA_LIB ${LibPWQuality_LIBRARIES} )
    include_directories( ${LibPWQuality_INCLUDE_DIRS} )
    add_definitions( -DCHECK_PWQUALITY -DHAVE_LIBPWQUALITY )
endif()

include_directories( ${PROJECT_BINARY_DIR}/src/libcalamaresui )

calamares_add_plugin( usersq
    TYPE viewmodule
    EXPORT_MACRO PLUGINDLLEXPORT_PRO
    SOURCES
		Config.cpp
        CreateUserJob.cpp
        SetPasswordJob.cpp
        UsersQmlViewStep.cpp
        SetHostNameJob.cpp
        CheckPWQuality.cpp
    RESOURCES
        users.qrc
    LINK_PRIVATE_LIBRARIES
        calamaresui
        ${CRYPT_LIBRARIES}
        ${USER_EXTRA_LIB}
    SHARED_LIB
)

add_executable( usersqmltest qmlmain.cpp Config.cpp UsersQmlViewStep.cpp CreateUserJob.cpp SetPasswordJob.cpp SetHostNameJob.cpp CheckPWQuality.cpp )
target_link_libraries( usersqmltest PRIVATE calamaresui Qt5::Core Qt5::Network Qt5::DBus ${CRYPT_LIBRARIES} ${USER_EXTRA_LIB})
set_target_properties( usersqmltest
    PROPERTIES
        ENABLE_EXPORTS TRUE
        RUNTIME_OUTPUT_NAME usersqmltest
)
calamares_automoc( usersqmltest )
calamares_autouic( usersqmltest )
