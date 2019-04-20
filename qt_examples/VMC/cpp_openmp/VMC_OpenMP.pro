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

#CONFIG += \
#    vmcsystem.h \
#    wavefunctions/wavefunction.h \
#    wavefunctions/helium.h \
#    wavefunctions/twoparticlenoninteractingwf.h
#PRECOMPILED_HEADER += \
#    vmcsystem.h \
#    wavefunctions/wavefunction.h \
#    wavefunctions/helium.h \
#    wavefunctions/twoparticlenoninteractingwf.h

LIBS += -L/usr/local/lib -larmadillo
INCLUDEPATH += /usr/local/include


#QMAKE_CXX = /usr/bin/g++
#QMAKE_LINK = /usr/bin/g++

# Adds O3 optimizations
QMAKE_CFLAGS += -O3
QMAKE_LFLAGS += -O3
QMAKE_CXXFLAGS += -O3
QMAKE_CXXFLAGS_RELEASE += -O3

# Adds processor specific optimizations
QMAKE_CFLAGS += -march=native
QMAKE_LFLAGS += -march=native
QMAKE_CXXFLAGS += -march=native
QMAKE_CXXFLAGS_RELEASE += -march=native

QMAKE_CXXFLAGS += -std=c++11
QMAKE_CFLAGS += -std=c++11
QMAKE_LFLAGS += -std=c++11

# Adding OpenMP. Xpreprocessor needed on latest mac OS.
QMAKE_CXXFLAGS += -Xpreprocessor
QMAKE_CFLAGS += -Xpreprocessor
QMAKE_LFLAGS += -Xpreprocessor

# OpenMP flags
QMAKE_CXXFLAGS += -fopenmp
QMAKE_CFLAGS += -fopenmp
QMAKE_LFLAGS += -fopenmp

LIBS += -lomp
