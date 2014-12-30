TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    ../model/model.cpp \
    ../model/settings.cpp \
    ../model/square.cpp \
    ../model/fitness.cpp \
    ../model/mutation.cpp \
    ../model/population.cpp \
    ../model/reproduction.cpp \
    ../model/selection.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ../model/fitness.h \
    ../model/model.h \
    ../model/mutation.h \
    ../model/population.h \
    ../model/reproduction.h \
    ../model/settings.h \
    ../model/square.h \
    ../model/selection.h

QMAKE_CXXFLAGS += -std=c++11
