TEMPLATE = lib
TARGET = qrefuse
VERSION = 0.1.1

QT = core

INCLUDEPATH += ./include

HEADERS = include/force/force.h \
          include/force/forceitem.h \
	  include/force/forcesimulator.h \
          include/force/spring.h \
	  include/force/rungekuttaintegrator.h

SOURCES = src/force/force.cpp \
          src/force/forceitem.cpp \
	  src/force/forcesimulator.cpp \
	  src/force/rungekuttaintegrator.cpp

DESTDIR = build
UI_DIR = build/ui
MOC_DIR = build/moc
OBJECTS_DIR = build/obj
RCC_DIR = build/rcc
