TEMPLATE = lib
TARGET = qrefuse
VERSION = 0.1.1

QT = core

INCLUDEPATH += ./include

HEADERS = include/force/force.h \
		include/force/dragforce.h \
		include/force/springforce.h \
		include/force/nbodyforce.h \
		include/force/forceitem.h \
		include/force/forcesimulator.h \
		include/force/spring.h \
		include/force/rungekuttaintegrator.h

SOURCES = src/force/force.cpp \
		src/force/dragforce.cpp \
		src/force/springforce.cpp \
		src/force/nbodyforce.cpp \
		src/force/forceitem.cpp \
		src/force/forcesimulator.cpp \
		src/force/rungekuttaintegrator.cpp

DESTDIR = lib
UI_DIR = build/ui
MOC_DIR = build/moc
OBJECTS_DIR = build/obj
RCC_DIR = build/rcc
