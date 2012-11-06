cmake_minimum_required(VERSION 2.8.5)
project(zlcore)

# Check to ensure that we are running as part of the
# root CMakeLists.txt file.
if(NOT DEFINED IS_ROOT)
  message(FATAL_ERROR "You must generate the CMake files as part of the root directory.")
endif(NOT DEFINED IS_ROOT)

set(${PROJECT_NAME}_UnixInclude "${ROOT_DIR}/src/zlcore/" PARENT_SCOPE)
include_directories("${ROOT_DIR}/src/")
set(CMAKE_CURRENT_SOURCE_DIR "${ROOT_DIR}/src/zlcore/")
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

moai_manual(library
  ${SRC_FILES}
  )

moai_needs(tlsf)