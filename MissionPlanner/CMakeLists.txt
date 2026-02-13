cmake_minimum_required(VERSION 3.10)

project(MissionPlanner
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependency
find_package(MissionJob REQUIRED)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# ---------- LIBRARY ----------
add_library(MissionPlanner STATIC
    src/mission_planner.cpp
)

# Alias chuẩn
add_library(MissionPlanner::MissionPlanner ALIAS MissionPlanner)

# Include path cho build & install
target_include_directories(MissionPlanner
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include_common>
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../EventBus/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(MissionPlanner
    PUBLIC 
    MissionJob::MissionJob
)

# ---------- INSTALL LIB ----------
install(TARGETS MissionPlanner
    EXPORT MissionPlannerTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# ---------- INSTALL HEADERS ----------
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# ---------- EXPORT TARGET ----------
install(EXPORT MissionPlannerTargets
    FILE MissionPlannerTargets.cmake
    NAMESPACE MissionPlanner::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MissionPlanner
)

# ---------- CONFIG FILE ----------
configure_package_config_file(
    cmake/MissionPlannerConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/MissionPlannerConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MissionPlanner
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/MissionPlannerConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/MissionPlannerConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/MissionPlannerConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/MissionPlanner
)
