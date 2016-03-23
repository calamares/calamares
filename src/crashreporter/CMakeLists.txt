PROJECT( CrashReporter )
cmake_policy(SET CMP0017 NEW)

set(CALAMARES_CRASH_REPORTER_TARGET calamares_crash_reporter)

list(APPEND crashreporter_SOURCES main.cpp)
list(APPEND crashreporter_RC resources.qrc)

qt5_wrap_ui( crashreporter_UI_HEADERS ${crashreporter_UI} )
qt5_add_resources( crashreporter_RC_RCC ${crashreporter_RC} )


if(BUILD_RELEASE)
    set(CRASHREPORTER_RELEASE_CHANNEL "release")
else()
    set(CRASHREPORTER_RELEASE_CHANNEL "nightly")
endif()

set(CRASHREPORTER_SUBMIT_URL "https://calamares.io/oops/addreport.php")
set(CRASHREPORTER_ICON ":/squid.svg")
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/CrashReporterConfig.h.in
               ${CMAKE_CURRENT_BINARY_DIR}/CrashReporterConfig.h)


include_directories(${CMAKE_CURRENT_BINARY_DIR}
    ../../libcalamares
    ../../libcalamaresui
    ../../thirdparty/libcrashreporter-qt/src
)

add_executable( ${CALAMARES_CRASH_REPORTER_TARGET}
    ${crashreporter_SOURCES}
    ${crashreporter_HEADERS_MOC}
    ${crashreporter_UI_HEADERS}
    ${crashreporter_RC_RCC}
)

target_link_libraries( ${CALAMARES_CRASH_REPORTER_TARGET}
    ${CALAMARES_LIBRARIES}
    crashreporter-gui
    ${QT_LIBRARIES}
)

set_target_properties(${CALAMARES_CRASH_REPORTER_TARGET} PROPERTIES AUTOMOC ON)
install(TARGETS ${CALAMARES_CRASH_REPORTER_TARGET} RUNTIME DESTINATION ${CMAKE_INSTALL_LIBEXECDIR})

qt5_use_modules(${CALAMARES_CRASH_REPORTER_TARGET} Widgets Network)
