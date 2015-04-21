TEMPLATE = app
CONFIG += console
CONFIG += c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    turingmachine.cpp \
    processingunit.cpp \
    head.cpp \
    tape.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    turingmachine.h \
    processingunit.h \
    head.h \
    tape.h \
    exception.h \
    instruction.h

