cmake_minimum_required(VERSION 3.10)

project(MissionJob
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependency
# find_package(StateAMR REQUIRED)
# find_package(StateMission REQUIRED)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# ---------- LIBRARY ----------
add_library(MissionJob STATIC
    src/mission_job.cpp
)

# Alias chuẩn
add_library(MissionJob::MissionJob ALIAS MissionJob)

# Include path cho build & install
target_include_directories(MissionJob
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include_common>
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../EventBus/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# target_link_libraries(MissionJob
#     PUBLIC 
#     StateAMR::StateAMR 
#     StateMission::StateMission
# )

# ---------- INSTALL LIB ----------
install(TARGETS MissionJob
    EXPORT MissionJobTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# ---------- INSTALL HEADERS ----------
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# ---------- EXPORT TARGET ----------
install(EXPORT MissionJobTargets
    FILE MissionJobTargets.cmake
    NAMESPACE MissionJob::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MissionJob
)

# ---------- CONFIG FILE ----------
configure_package_config_file(
    cmake/MissionJobConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MissionJobConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MissionJob
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MissionJobConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/MissionJobConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/MissionJobConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MissionJob
)
