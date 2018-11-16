TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    vmcsystem.cpp \
    wavefunctions/wavefunction.cpp \
    wavefunctions/helium.cpp \
    wavefunctions/twoparticlenoninteractingwf.cpp

HEADERS += \
    vmcsystem.h \
    wavefunctions/wavefunction.h \
    wavefunctions/helium.h \
    wavefunctions/twoparticlenoninteractingwf.h

LIBS += -L/usr/local/lib -larmadillo
INCLUDEPATH += /usr/local/include


QMAKE_CFLAGS += -O3
QMAKE_LFLAGS += -O3
QMAKE_CXXFLAGS += -O3
QMAKE_CXXFLAGS_RELEASE += -O3
