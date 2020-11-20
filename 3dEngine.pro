TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

win32{
    LIBS += -lmingw32
    LIBS += -lopengl32
    LIBS += -L"..\libs"
    INCLUDEPATH += "..\include"
}
unix{
    LIBS += -lGL
}
LIBS += -lSDL2main -lSDL2 -lSDL2_image -lGLEW -lGLU

SOURCES += \
        cubemesh.cpp \
        game.cpp \
        main.cpp

HEADERS += \
    cubemesh.h \
    game.h \
    mesh.h
