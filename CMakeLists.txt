cmake_minimum_required(VERSION 3.18)
project(SM_sign)
# MESSAGE(STATUS "operation system is ${CMAKE_SYSTEM}")

set(CMAKE_CXX_STANDARD 11)
AUX_SOURCE_DIRECTORY(utils DIR_UTILS)
SET(UTILS_PATH ${DIR_UTILS})
AUX_SOURCE_DIRECTORY(src DIR_SRCS)
SET(SRC_PATH ${DIR_SRCS})
SET(LIB_PATH ${CMAKE_CURRENT_LIST_DIR}/lib)
SET(CMAKE_BUILD_TYPE Debug)
# find_package(OpenSSL REQUIRED)
# include_directories(/mnt/d/Documents/Chores/homework/NSS/main/local/gmssl/include)
include_directories(inc)
# add_executable(${PROJECT_NAME} ${SRC_PATH} ${DIR_UTILS})
# target_link_libraries(${PROJECT_NAME} ${LIB_PATH}/openssl/libcrypto.so.1.1)
# target_link_libraries(${PROJECT_NAME} ${LIB_PATH}/openssl/libssl.so.1.1)

# MESSAGE(STATUS ${UTILS_PATH})


# file( GLOB UTILS_SOURCES utils/*.cc )
# MESSAGE(STATUS "${UTILS_SOURCES}")
# foreach( testsourcefile ${UTILS_SOURCES} )
#     get_filename_component( testname ${testsourcefile} NAME_WE)
#     MESSAGE(STATUS ${testname})
#     add_executable( ${testname} ${testsourcefile})
#     # Make sure YourLib is linked to each app
#     target_link_libraries(${testname} ${LIB_PATH}/openssl/libcrypto.so.1.1)
#     target_link_libraries(${testname} ${LIB_PATH}/openssl/libssl.so.1.1)
# endforeach( testsourcefile ${UTILS_SOURCES} )


# AUX_SOURCE_DIRECTORY(tools DIR_TOOLS)
# SET(TOOL_PATH ${DIR_TOOLS})
# file( GLOB TOOLS_SOURCES tools/*.cc )
# # MESSAGE(STATUS "${TOOLS_SOURCES}")
# foreach( testsourcefile ${TOOLS_SOURCES} )
#     get_filename_component( testname ${testsourcefile} NAME_WE)
#     MESSAGE(STATUS ${testname})
#     add_executable( ${testname} ${testsourcefile} ${UTILS_PATH})
#     # Make sure YourLib is linked to each app
#     target_link_libraries(${testname} ${LIB_PATH}/openssl/libcrypto.so.1.1)
#     target_link_libraries(${testname} ${LIB_PATH}/openssl/libssl.so.1.1)
# endforeach( testsourcefile ${TOOLS_SOURCES} )

FIND_PACKAGE(SWIG REQUIRED)
INCLUDE(${SWIG_USE_FILE})
FIND_PACKAGE(PythonLibs)
INCLUDE_DIRECTORIES(${PYTHON_INCLUDE_PATH})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
SET(CMAKE_SWIG_FLAGS "")
SET_SOURCE_FILES_PROPERTIES(utils/sm.i PROPERTIES CPLUSPLUS ON)
# SET_SOURCE_FILES_PROPERTIES(src/keygen.i PROPERTIES SWIG_FLAGS "-includeall")
SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-rpath -Wl,${LIB_PATH}")

# SET_SOURCE_FILES_PROPERTIES(keygen.i PROPERTY CPLUSPLUS ON)
SWIG_ADD_LIBRARY(
    mod_sm
    TYPE MODULE
    LANGUAGE python
    SOURCES utils/sm.i utils/sm.cc utils/key.cc
    )

SWIG_LINK_LIBRARIES(
    mod_sm
    ${PYTHON_LIBRARIES}
    ${LIB_PATH}/openssl/libcrypto.a
    ${LIB_PATH}/openssl/libssl.a
)
set(CMAKE_SKIP_BUILD_RPATH FALSE)

# when building, don't use the install RPATH already
# (but later on when installing)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH "${CMAKE_INSTALL_PREFIX}/lib")

# add the automatically determined parts of the RPATH
# which point to directories outside the build tree to the install RPATH
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

SET_TARGET_PROPERTIES(mod_sm PROPERTIES INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
SET_TARGET_PROPERTIES(mod_sm PROPERTIES CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
SET(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
# INSTALL(TARGETS ${PROJECT_NAME} DESTINATION lib)
INSTALL(TARGETS mod_sm DESTINATION lib/python3.8/site-packages)
# INSTALL(FILES lib/openssl/libcrypto.so.1.1 DESTINATION lib)
# INSTALL(FILES lib/openssl/libssl.so.1.1 DESTINATION lib)
INSTALL(FILES ${CMAKE_CURRENT_BINARY_DIR}/sm.py DESTINATION lib/python3.8/site-packages)
INSTALL(FILES src/sm.ipynb DESTINATION lib/python3.8/site-packages)


# siwg_link_library(
#     keygen
#     /mnt/d/Documents/Chores/homework/NSS/main/local/gmssl/lib/libcrypto.so.1.1
#     /mnt/d/Documents/Chores/homework/NSS/main/local/gmssl/lib/libssl.so.1.1
# )
# set(DEPEND_LIB_DIR /mnt/d/Documents/Chores/homework/NSS/main/local/gmssl)
# link_directories(
#     ./
#     ${DEPEND_LIB_DIR}
# )
# include_directories(
#     ${DEPEND_LIB_DIR}/include 
#     ./inc
#     /usr/include/python3.8
# )
# add_library(keygen SHARED utils/keygen.cpp)
# target_link_libraries(
#     keygen
#     dl
#     rt
#     pthread
# )
# EXECUTE_PROCESS( COMMAND swig -c++ -python -outdir ${PROJECT_BINARY_DIR} -o ${PROJECT_BINARY_DIR}/mod_sm_wrap.cxx  ${PROJECT_SOURCE_DIR}/src/keygen.i)
# add_library(mod_sm SHARED ${PROJECT_BINARY_DIR}/mod_sm_wrap.cxx)
# target_link_libraries(
#     mod_sm
#     keygen
#     python3.8
# )

# set_target_properties(mod_sm PROPERTIES PREFIX "-")