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
LIBS += -lSDL2main -lSDL2 -lSDL2_image

SOURCES += \
        game.cpp \
        main.cpp \
        mesh.cpp \
        shaderprogram.cpp \
        window.cpp

HEADERS += \
    game.h \
    glLibs.h \
    mesh.h \
    shaderprogram.h \
    window.h
