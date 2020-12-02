TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

win32{
    LIBS += -lmingw32
    LIBS += -lopengl32 -lGLEW32 -lGLU32
    LIBS += -L"..\libs"
    INCLUDEPATH += "..\include"
}
unix{
    LIBS += -lGL -lGLEW -lGLU
}
LIBS += -lSDL2main -lSDL2 -lSDL2_image

SOURCES += \
        camera.cpp \
        cubemesh.cpp \
        game.cpp \
        main.cpp \
        objectmanager.cpp

HEADERS += \
    camera.h \
    cubemesh.h \
    game.h \
    mesh.h \
    glIncludes.h \
    objectmanager.h \
    physics.h \
    transform.h
