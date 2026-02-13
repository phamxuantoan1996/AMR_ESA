cmake_minimum_required(VERSION 3.10)

project(ExecutorMission
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find dependency
# find_package(StateAMR REQUIRED)
find_package(StateMission REQUIRED)
find_package(MissionJob REQUIRED)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# ---------- LIBRARY ----------
add_library(ExecutorMission STATIC
    src/executor_mission.cpp
)

# Alias chuẩn
add_library(ExecutorMission::ExecutorMission ALIAS ExecutorMission)

# Include path cho build & install
target_include_directories(ExecutorMission
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../include_common>
        # $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../EventBus/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

target_link_libraries(ExecutorMission
    PUBLIC 
    # StateAMR::StateAMR 
    StateMission::StateMission
    MissionJob::MissionJob
)

# ---------- INSTALL LIB ----------
install(TARGETS ExecutorMission
    EXPORT ExecutorMissionTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# ---------- INSTALL HEADERS ----------
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# ---------- EXPORT TARGET ----------
install(EXPORT ExecutorMissionTargets
    FILE ExecutorMissionTargets.cmake
    NAMESPACE ExecutorMission::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ExecutorMission
)

# ---------- CONFIG FILE ----------
configure_package_config_file(
    cmake/ExecutorMissionConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/ExecutorMissionConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ExecutorMission
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/ExecutorMissionConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/ExecutorMissionConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/ExecutorMissionConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ExecutorMission
)
