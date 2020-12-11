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

INCLUDEPATH += src/

SOURCES += \
        main.cpp \
        #$${files(src/*.cpp, true)}
        src/Components/meshcomponent.cpp \
        src/Components/physicscomponent.cpp \
        src/Managers/keyboardmanager.cpp \
        src/Managers/objectmanager.cpp \
        src/Objects/camera.cpp \
        src/Objects/gameobject.cpp \
        src/Objects/game.cpp

HEADERS += \
        #$${files(src/*.h, true)} \
        examplegame.h \
        src/Components/component.h \
        src/Components/meshcomponent.h \
        src/Components/physicscomponent.h \
        src/Managers/keyboardmanager.h \
        src/Managers/objectmanager.h \
        src/Objects/camera.h \
        src/Objects/color.h \
        src/Objects/gameobject.h \
        src/Objects/transform.h \
        src/Objects/game.h \
        src/Utils/utils.h \
        src/glIncludes.h \
        src/Utils/utils.h
