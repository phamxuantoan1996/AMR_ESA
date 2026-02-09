cmake_minimum_required(VERSION 3.10)

project(StateAMR
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)

# ---------- LIBRARY ----------
add_library(StateAMR STATIC
    src/state_amr.cpp
)

# Alias chuẩn
add_library(StateAMR::StateAMR ALIAS StateAMR)

# Include path cho build & install
target_include_directories(StateAMR
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

# ---------- INSTALL LIB ----------
install(TARGETS StateAMR
    EXPORT StateAMRTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

# ---------- INSTALL HEADERS ----------
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

# ---------- EXPORT TARGET ----------
install(EXPORT StateAMRTargets
    FILE StateAMRTargets.cmake
    NAMESPACE StateAMR::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/StateAMR
)

# ---------- CONFIG FILE ----------
configure_package_config_file(
    cmake/StateAMRConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/StateAMRConfig.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/StateAMR
)

write_basic_package_version_file(
    ${CMAKE_CURRENT_BINARY_DIR}/StateAMRConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY SameMajorVersion
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/StateAMRConfig.cmake
    ${CMAKE_CURRENT_BINARY_DIR}/StateAMRConfigVersion.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/StateAMR
)
