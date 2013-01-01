PROJECT(BasicGL)

CMAKE_MINIMUM_REQUIRED(VERSION 2.4.0)

FIND_PACKAGE(Qt4 REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)

OPTION(INSTALL_DOC "Set to OFF to skip build/install Documentation" ON)
OPTION(USE_DOT "Set to ON to perform diagram generation with graphviz" OFF)
OPTION(USE_LATEX "Set to ON to build latex documentation" OFF)
OPTION(USE_CHM "Set to ON to build CHM Windows documentation" OFF)

IF (INSTALL_DOC)
INCLUDE("generateDoc.cmake")
GENERATE_DOCUMENTATION(${PROJECT_SOURCE_DIR}/basicgl.dox.in)
ENDIF()

ADD_SUBDIRECTORY(src)

