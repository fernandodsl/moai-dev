cmake_minimum_required(VERSION 2.8.5)
project(uslscore)

# Check to ensure that we are running as part of the
# root CMakeLists.txt file.
if(NOT DEFINED IS_ROOT)
  message(FATAL_ERROR "You must generate the CMake files as part of the root directory.")
endif(NOT DEFINED IS_ROOT)

set(${PROJECT_NAME}_UnixInclude "${ROOT_DIR}/src/uslscore/" PARENT_SCOPE)
include_directories("${ROOT_DIR}/src/")
include_directories("${ROOT_DIR}/3rdparty/")
set(CMAKE_CURRENT_SOURCE_DIR "${ROOT_DIR}/src/uslscore/")
file(GLOB SRC_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

moai_manual(library
  ${SRC_FILES}
)
moai_needs(expat)
moai_needs(pthread)
moai_needs(rt)
moai_needs(zlcore)
moai_needs(lua-lib)
moai_needs(ooid)
