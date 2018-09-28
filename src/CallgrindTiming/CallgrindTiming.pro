TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

## Need to include boost
#INCLUDEPATH += /usr/local/include

## Needed to include Eigen
#LIBS += -L/usr/local/lib -lblas -llapack -larmadillo

#QMAKE_CFLAGS += -std=c++11 -I /usr/local/include
#QMAKE_CXXFLAGS += -std=c++11 -I /usr/local/include
#QMAKE_CXXFLAGS_RELEASE += -std=c++11 -I /usr/local/include


# Removes flags
QMAKE_CFLAGS -= -O
QMAKE_CXXFLAGS -= -O
QMAKE_CXXFLAGS_RELEASE -= -O
QMAKE_CFLAGS -= -O1
QMAKE_CXXFLAGS -= -O1
QMAKE_CXXFLAGS_RELEASE -= -O1
QMAKE_CFLAGS -= -O2
QMAKE_CXXFLAGS -= -O2
QMAKE_CXXFLAGS_RELEASE -= -O2
QMAKE_CFLAGS -= -O2Fast
QMAKE_CXXFLAGS -= -O2Fast
QMAKE_CXXFLAGS_RELEASE -= -O2Fast
QMAKE_CFLAGS -= -O3
QMAKE_CXXFLAGS -= -O3
QMAKE_CXXFLAGS_RELEASE -= -O3

# Vectorization(and more) enabling
#QMAKE_CFLAGS += -O3
#QMAKE_CXXFLAGS += -O3
#QMAKE_CXXFLAGS_RELEASE += -O3

## Specific processor optimization
#QMAKE_CFLAGS += -march=native
#QMAKE_CXXFLAGS += -march=native
#QMAKE_CXXFLAGS_RELEASE += -march=native
