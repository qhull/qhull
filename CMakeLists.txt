project(qhull)
cmake_minimum_required(VERSION 2.6)


set(QHULL_VERSION "2010.1.next")

if(INCLUDE_INSTALL_DIR)
else()
set(INCLUDE_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/include)
endif()
if(LIB_INSTALL_DIR)
else()
set(LIB_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/lib)
endif()
if(BIN_INSTALL_DIR)
else()
set(BIN_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/bin)
endif()
if(DOC_INSTALL_DIR)
else()
set(DOC_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/share/doc/packages/qhull)
endif()

message(STATUS)
message(STATUS "========== qhull Build Information ==========")
message(STATUS "Build Version: ${QHULL_VERSION}")
message(STATUS "Install Prefix (CMAKE_INSTALL_PREFIX): ${CMAKE_INSTALL_PREFIX}")
message(STATUS "Binary Directory (BIN_INSTALL_DIR): ${BIN_INSTALL_DIR}")
message(STATUS "Library Directory (LIB_INSTALL_DIR): ${LIB_INSTALL_DIR}")
message(STATUS "Include Directory (INCLUDE_INSTALL_DIR): ${INCLUDE_INSTALL_DIR}")
message(STATUS "Documentation Directory (DOC_INSTALL_DIR): ${DOC_INSTALL_DIR}")
message(STATUS)
message(STATUS "To change any of these options, override them using -D{OPTION_NAME} on the commandline.")
message(STATUS "To build and install qhull, run \"make\" and \"make install\"")
message(STATUS)


add_subdirectory(src)


install(DIRECTORY html/ DESTINATION ${DOC_INSTALL_DIR})
