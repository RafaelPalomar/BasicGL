
INCLUDE(${QT_USE_FILE})

SET(QT_USE_QTGUI TRUE)
SET(QT_USE_OPENGL TRUE)

FIND_LIBRARY(GLU_LIBRARY GLU "/usr/lib")

INCLUDE_DIRECTORIES(
  ${QT_QTOPENGL_INCLUDE_DIR}
  ${QT_QTGUI_INCLUDE_DIR})

SET(BasicGL_SRCS
  main.cpp
  mainwindow.cpp
  centralwidget.cpp
  glwidget.cpp
  colorwidget.cpp
  lightingwidget.cpp
  texturewidget.cpp
  fxwidget.cpp
  )

SET(BasicGL_MOC_HDRS
  mainwindow.h
  centralwidget.h
  glwidget.h
  colorwidget.h
  lightingwidget.h
  texturewidget.h
  fxwidget.h
  )

QT4_WRAP_CPP(BasicGL_MOC_SRCS ${BasicGL_MOC_HDRS})

IF(UNIX)
  ADD_EXECUTABLE(basicGL ${BasicGL_SRCS} ${BasicGL_MOC_SRCS})
ELSEIF(APPLE)
  ADD_EXECUTABLE(basicGL MACOSX_BUNDLE ${BasicGL_SRCS} ${BasicGL_MOC_SRCS})
ELSEIF(WIN32)
  ADD_EXECUTABLE(basicGL WIN32 ${BasicGL_SRCS} ${BasicGL_MOC_SRCS})
ENDIF()

TARGET_LINK_LIBRARIES(basicGL ${QT_LIBRARIES} ${QT_QTOPENGL_LIBRARIES} ${GLU_LIBRARY})
