#-------------------------------------------------
#
# Project created by QtCreator 2020-04-15T13:30:28
#
#-------------------------------------------------
#####################################################
# directory and machine specific items here
#####################################################
linebreak="---------------------------------------------------------------"


sourcepath=""
includepath=""
imagepath=""
type=""

linux {
    sourcepath="../src"
    includepath="../include"
} else {
    sourcepath="../src"
    includepath="../include"
}

message($$linebreak)
message("qmake sourcepath:      $$sourcepath")
message("qmake includepath:     $$includepath")
message($$linebreak)

#####################################################


QT      += core gui
QT      += network
QT      += widgets
QT      += xml
QT      += concurrent
QT      += serialport
QT      += sql


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
CONFIG  += console
CONFIG  +=declarative_debug
CONFIG  +=c++11


TARGET = VMM_database_browser
TEMPLATE = app

INCLUDEPATH += $$includepath
DEPENDPATH  += $$includepath

OBJECTS_DIR += ./objects/
MOC_DIR     += ./moc/
RCC_DIR     += ./rcc/
UI_DIR      += ./ui/

linux {
    QMAKE_CXXFLAGS += -std=c++11
} else {
    QMAKE_CXXFLAGS += -stdlib=libc++
    QMAKE_CXXFLAGS += -std=c++11
    QMAKE_LFLAGS   += -stdlib=libc++
}

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES +=  $$sourcepath/main.cpp \
            $$sourcepath/mainwindow.cpp \
            $$sourcepath/databasehandler.cpp \
            $$sourcepath/dbwindow.cpp \
            $$sourcepath/qcustomplot.cpp \
            $$sourcepath/filterdialog.cpp

HEADERS +=  $$includepath/mainwindow.h \
            $$includepath/databasehandler.h \
            $$includepath/dbwindow.h \
            $$includepath/qcustomplot.h \
            $$includepath/filterdialog.h \
            $$includepath/PolyonmialRegression.h

FORMS   +=  $$sourcepath/dbwindow.ui \

RESOURCES +=

DISTFILES +=
