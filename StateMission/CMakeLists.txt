cmake_minimum_required(VERSION 3.10)

project(StateMission
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# ---------- LIBRARY ----------
add_library(StateMission STATIC
    src/state_mission.cpp
)

# Alias chuẩn
add_library(StateMission::StateMission ALIAS StateMission)

# Include path cho build & install
target_include_directories(StateMission
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# ---------- INSTALL LIB ----------
install(TARGETS StateMission
    EXPORT StateMissionTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# ---------- INSTALL HEADERS ----------
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# ---------- EXPORT TARGET ----------
install(EXPORT StateMissionTargets
    FILE StateMissionTargets.cmake
    NAMESPACE StateMission::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/StateMission
)

# ---------- CONFIG FILE ----------
configure_package_config_file(
    cmake/StateMissionConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/StateMissionConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/StateMission
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/StateMissionConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/StateMissionConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/StateMissionConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/StateMission
)
