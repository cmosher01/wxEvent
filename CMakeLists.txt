cmake_minimum_required(VERSION 3.22.1)

set(CMAKE_VERBOSE_MAKEFILE TRUE CACHE BOOL "Echo make commands.")

set(CMAKE_BUILD_TYPE RelWithDebInfo)
set(CMAKE_FIND_PACKAGE_PREFER_CONFIG TRUE)



project(wxEvent
    VERSION 0.0.1
    LANGUAGES CXX
    DESCRIPTION "wx event study"
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_FOURCC wxev)
set(PROJECT_VENDOR nu.mine.mosher)
set(CPACK_PACKAGE_VENDOR "${PROJECT_VENDOR}")
set(CPACK_PACKAGE_CONTACT "cmosher01@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION "${PROJECT_DESCRIPTION}")

set(sources
app.cpp
frame.cpp
)
list(TRANSFORM sources PREPEND src/)

set(resources
foobar.png
)
list(TRANSFORM resources PREPEND "share/Resources/")

if(WIN32)
    set(CMAKE_INSTALL_PREFIX "C:/Program Files/${PROJECT_NAME}")
    unset(CPACK_PACKAGING_INSTALL_PREFIX)
elseif(APPLE)
    unset(CMAKE_INSTALL_PREFIX)
    unset(CPACK_PACKAGING_INSTALL_PREFIX)
else()
    set(CMAKE_INSTALL_PREFIX "/opt/${CPACK_PACKAGE_VENDOR}/${PROJECT_NAME}")
    set(CPACK_PACKAGING_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")
endif()

include(GNUInstallDirs)

add_executable(${PROJECT_NAME} WIN32 MACOSX_BUNDLE ${sources} ${resources})

target_include_directories(${PROJECT_NAME} BEFORE PUBLIC include)

find_package(wxWidgets REQUIRED COMPONENTS base core)
include(${wxWidgets_USE_FILE})
target_link_libraries(${PROJECT_NAME} PRIVATE ${wxWidgets_LIBRARIES})




set_target_properties(${PROJECT_NAME} PROPERTIES RESOURCE "${resources}")

include(InstallRequiredSystemLibraries)

if(APPLE)
    set_target_properties(${PROJECT_NAME} PROPERTIES
        MACOSX_BUNDLE_INFO_PLIST ${PROJECT_BINARY_DIR}/Info.plist)
    install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        BUNDLE DESTINATION .)
    configure_file(share/FixBundle.cmake.in ${PROJECT_BINARY_DIR}/FixBundle.cmake @ONLY)
    install(SCRIPT ${PROJECT_BINARY_DIR}/FixBundle.cmake)
elseif(WIN32)
    install(TARGETS ${PROJECT_NAME}
        RUNTIME_DEPENDENCIES
            DIRECTORIES ${CMAKE_SYSTEM_LIBRARY_PATH}
            PRE_EXCLUDE_REGEXES "api-ms-" "ext-ms-"
            POST_EXCLUDE_REGEXES ".*system32/.*\\.dll"
        BUNDLE DESTINATION .
        RESOURCE DESTINATION share/Resources)
else()
    install(TARGETS ${PROJECT_NAME}
        RUNTIME_DEPENDENCIES
            DIRECTORIES ${CMAKE_SYSTEM_LIBRARY_PATH}
        RESOURCE DESTINATION share/Resources)
endif()

set(CPACK_GENERATOR ZIP)

set(CPACK_GENERATOR ${CPACK_GENERATOR} TGZ 7Z)
if(APPLE)
    set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PROJECT_VERSION}-macOS")
    configure_file(share/Info.plist.in ${PROJECT_BINARY_DIR}/Info.plist)
    set(CPACK_GENERATOR ${CPACK_GENERATOR} DragNDrop)
elseif(WIN32)
    set(CPACK_GENERATOR ${CPACK_GENERATOR} NSIS)
else()
    set(CPACK_GENERATOR ${CPACK_GENERATOR} DEB)
endif()

include(CPack)
