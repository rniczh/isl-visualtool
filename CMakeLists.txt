cmake_minimum_required(VERSION 3.10)

set(DEFAULT_BUILD_TYPE "Debug")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${DEFAULT_BUILD_TYPE}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${DEFAULT_BUILD_TYPE}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

project(islvis VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

FILE(GLOB ISLOBJS isl/.libs/*.o)
SET_SOURCE_FILES_PROPERTIES(
  ${ISLOBJS}
  PROPERTIES
  EXTERNAL_OBJECT true
  GENERATED true
  )

FILE(GLOB SRCS src/*.cc)

if(NOT PYTHON_EXECUTABLE)
  if(NumPy_FIND_QUIETLY)
    find_package(PythonInterp QUIET)
  else()
    find_package(PythonInterp)
    set(__numpy_out 1)
  endif()
endif()

if (PYTHON_EXECUTABLE)
  # Find out the include path
  execute_process(
    COMMAND "${PYTHON_EXECUTABLE}" -c
    "from __future__ import print_function\ntry: import numpy; print(numpy.get_include(), end='')\nexcept:pass\n"
    OUTPUT_VARIABLE __numpy_path)
  # And the version
  execute_process(
    COMMAND "${PYTHON_EXECUTABLE}" -c
    "from __future__ import print_function\ntry: import numpy; print(numpy.__version__, end='')\nexcept:pass\n"
    OUTPUT_VARIABLE __numpy_version)
elseif(__numpy_out)
  message(STATUS "Python executable not found.")
endif(PYTHON_EXECUTABLE)

find_path(PYTHON_NUMPY_INCLUDE_DIR numpy/arrayobject.h
  HINTS "${__numpy_path}" "${PYTHON_INCLUDE_PATH}" NO_DEFAULT_PATH)

if(PYTHON_NUMPY_INCLUDE_DIR)
  set(PYTHON_NUMPY_FOUND 1 CACHE INTERNAL "Python numpy found")
endif(PYTHON_NUMPY_INCLUDE_DIR)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(NumPy REQUIRED_VARS PYTHON_NUMPY_INCLUDE_DIR
  VERSION_VAR __numpy_version)


find_package(PythonLibs 3)

# library
add_library(islvis SHARED
  ${SRCS}
  ${ISLOBJS}
  )

target_include_directories(islvis PRIVATE
  ${PYTHON_INCLUDE_DIRS}
  ${PYTHON_NUMPY_INCLUDE_DIR}
  )

target_include_directories(islvis PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/include"
  "${PROJECT_SOURCE_DIR}/isl"
  "${PROJECT_SOURCE_DIR}/isl/include"
  "${PROJECT_SOURCE_DIR}/matplotlib-cpp"
  )

target_link_libraries(islvis
  ${PYTHON_LIBRARIES}
  gmp
  )

# executable
add_executable(test_isl
  ${SRCS}
  ${ISLOBJS}
  )
target_include_directories(test_isl PRIVATE
  ${PYTHON_INCLUDE_DIRS}
  ${PYTHON_NUMPY_INCLUDE_DIR}
  )

target_include_directories(test_isl PUBLIC
  "${PROJECT_BINARY_DIR}"
  "${PROJECT_SOURCE_DIR}/include"
  "${PROJECT_SOURCE_DIR}/isl"
  "${PROJECT_SOURCE_DIR}/isl/include"
  "${PROJECT_SOURCE_DIR}/matplotlib-cpp"
  )
target_link_libraries(test_isl ${PYTHON_LIBRARIES} gmp)
