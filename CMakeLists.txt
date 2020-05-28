# used features:
#   FindPython3 (3.12+)
#   MSVC_RUNTIME_LIBRARY (3.15+)
#   FindOpenMP (3.12+)
cmake_minimum_required(VERSION 3.15)

# tldr; this is required when setting MSVC_RUNTIME_LIBRARY (/MT, /MD, ...) property
# see also: https://cmake.org/cmake/help/latest/policy/CMP0091.html#policy:CMP0091
cmake_policy(SET CMP0091 NEW)


project(array LANGUAGES CXX)


include_directories(include)

set(HEADERS
  include/cmesh_array.hpp
  include/calc.hpp
)

set(CPP_SOURCES
  src/only_cpp.cpp
)

set(PYTHON_SOURCES
  src/py_module.cpp
)


# Python3 (NB: you can use Python3_ROOT_DIR cmake var as a hint)
find_package(Python3 COMPONENTS Development REQUIRED)
# add python module; this implies handling of .pyd/.so ext and include dirs/link libraries
Python3_add_library(py_array MODULE ${HEADERS} ${PYTHON_SOURCES})

add_executable(only_cpp_array ${HEADERS} ${CPP_SOURCES})
set_target_properties(only_cpp_array PROPERTIES LINKER_LANGUAGE CXX)

### properties

set_target_properties(
    only_cpp_array
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ../bin
    LIBRARY_OUTPUT_DIRECTORY ../bin
    RUNTIME_OUTPUT_DIRECTORY ../bin
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

set_target_properties(
    py_array
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ../bin
    LIBRARY_OUTPUT_DIRECTORY ../bin
    RUNTIME_OUTPUT_DIRECTORY ../bin
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)
target_compile_definitions(py_array PRIVATE PYTHON_BUILD=1) 

if (WIN32)
  # use /MT[d] instead of /MD[d]
  set_property(TARGET py_array PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
  set_property(TARGET only_cpp_array PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()


### dependencies

# pybind11
include_directories(lib/pybind11/include)
