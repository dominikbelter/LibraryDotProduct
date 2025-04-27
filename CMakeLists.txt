# cmake requirements
cmake_minimum_required(VERSION 3.28)

# Build options have to be before PROJECT(...)
SET(CMAKE_CONFIGURATION_TYPES "Debug;Release" CACHE PATH "Configuration types")
SET(CMAKE_BUILD_TYPE "Release" CACHE PATH "Current build configuration")

# Example Project configuration
PROJECT(DOTPRODUCT_LIBRARY)
SET(CMAKE_CXX_FLAGS "-std=c++17")

# Folders
SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

# Settings
INCLUDE_DIRECTORIES("${CMAKE_SOURCE_DIR}/include")

# core libraries
option(BUILD_LIB_DOTPRODUCT "Build Lib DotProduct" ON)
mark_as_advanced(BUILD_LIB_DOTPRODUCT)

# demos
option(BUILD_LIB_DOTPRODUCT_DEMO "Build LIB DotProduct Demo" ON)
mark_as_advanced(BUILD_LIB_DOTPRODUCT_DEMO)

find_package(Python3 COMPONENTS Interpreter Development REQUIRED)
include_directories(${Python3_INCLUDE_DIRS})

find_package(pybind11 REQUIRED)

# Executable output directory
SET(RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin${OUTPUT_DIRECTORY_POSTFIX} CACHE PATH "Executable output directory")
mark_as_advanced(RUNTIME_OUTPUT_DIRECTORY)

# Dynamic library output directory
SET(LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/bin${OUTPUT_DIRECTORY_POSTFIX} CACHE PATH "Dynamic library output directory")
mark_as_advanced(LIBRARY_OUTPUT_DIRECTORY)

# Static library output directory
SET(ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/lib${OUTPUT_DIRECTORY_POSTFIX} CACHE PATH "Static library output directory")
mark_as_advanced(ARCHIVE_OUTPUT_DIRECTORY)

SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${RUNTIME_OUTPUT_DIRECTORY})
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${LIBRARY_OUTPUT_DIRECTORY})
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${ARCHIVE_OUTPUT_DIRECTORY})
foreach(CONFIGURATION_TYPE ${CMAKE_CONFIGURATION_TYPES})
	string(TOUPPER ${CONFIGURATION_TYPE} CONFIGURATION_TYPE)
	SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY_${CONFIGURATION_TYPE} ${RUNTIME_OUTPUT_DIRECTORY})
	SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY_${CONFIGURATION_TYPE} ${LIBRARY_OUTPUT_DIRECTORY})
	SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${CONFIGURATION_TYPE} ${ARCHIVE_OUTPUT_DIRECTORY})
endforeach(CONFIGURATION_TYPE CMAKE_CONFIGURATION_TYPES)

if (MSVC)
  SET (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /EHsc")
endif()

# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")
if(WIN32 AND NOT CYGWIN)
  set(DEF_INSTALL_CMAKE_DIR CMake)
else()
  set(DEF_INSTALL_CMAKE_DIR CMake)
endif()
set(INSTALL_CMAKE_DIR ${DEF_INSTALL_CMAKE_DIR} CACHE PATH "Installation directory for CMake files")

# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE CMAKE)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()

# Create the DotProductConfig.cmake
file(RELATIVE_PATH REL_INCLUDE_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_INCLUDE_DIR}")
file(RELATIVE_PATH REL_LIB_DIR "${INSTALL_CMAKE_DIR}"
   "${INSTALL_LIB_DIR}")

set(CONF_INCLUDE_DIRS "${RELATIVE_PATH}" "${CMAKE_SOURCE_DIR}")

set(CONF_LIB_DIRS "${RELATIVE_PATH}" "/build/lib")

configure_file(DotProductConfig.cmake.in
  "${CMAKE_SOURCE_DIR}/DotProductConfig.cmake" @ONLY)

# ... for the install tree
set(CONF_INCLUDE_DIRS "${CONF_INCLUDE_DIRS}/include")
set(CONF_LIB_DIRS "${CMAKE_SOURCE_DIR}/build/lib")

configure_file(DotProductConfig.cmake.in
  "${CMAKE_SOURCE_DIR}/DotProductConfig.cmake" @ONLY)

# Install the DotProductConfig.cmake
install(FILES
  "${CMAKE_SOURCE_DIR}/DotProductConfig.cmake"
  DESTINATION "${INSTALL_CMAKE_DIR}" COMPONENT dev)


###############################################################################
#
# DotProduct library
#
###############################################################################

if(BUILD_LIB_DOTPRODUCT)
        file(GLOB DOTPRODUCT_SOURCES
            "${CMAKE_SOURCE_DIR}/src/DotProduct/*.cpp"
        )
        file(GLOB DOTPRODUCT_HEADERS
            "${CMAKE_SOURCE_DIR}/include/DotProduct/*.h"
        )

        ADD_LIBRARY(DotProduct STATIC ${DOTPRODUCT_SOURCES} ${DOTPRODUCT_HEADERS})
#        TARGET_LINK_LIBRARIES(DotProduct Utilities)
        INSTALL(TARGETS DotProduct RUNTIME DESTINATION bin LIBRARY DESTINATION bin ARCHIVE DESTINATION lib)
        INSTALL(FILES ${DOTPRODUCT_HEADERS} DESTINATION include/DotProduct/)
endif(BUILD_LIB_DOTPRODUCT)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

# Compile it with position independent code
target_compile_options(DotProduct PRIVATE -fPIC)

# Create Python module
pybind11_add_module(DotProductModule
    bindings/bindings.cpp
)

target_link_libraries(DotProductModule PRIVATE DotProduct)

###############################################################################
#
# Dotproduct DEMO executables
#
###############################################################################

if(BUILD_LIB_DOTPRODUCT_DEMO)
        SET(DEMO_SOURCES ./main.cpp)
        ADD_EXECUTABLE(dotProductTest ${DEMO_SOURCES})
        TARGET_LINK_LIBRARIES(dotProductTest DotProduct Python3::Python)
        INSTALL(TARGETS dotProductTest RUNTIME DESTINATION bin)
endif(BUILD_LIB_DOTPRODUCT_DEMO)
