TEMPLATE = lib
TARGET = qrefuse

QT = core

HEADERS = include/force/force.h
          include/force/forceitem.h
	  include/force/forcesimulator.h
	  include/force/rungekuttaintegrator.h

SOURCES = src/force/force.cpp
          src/force/forceitem.cpp
	  src/force/forcesimulator.cpp
	  src/force/rungekuttaintegrator.cpp
