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
        main.cpp \
        #$${files(src/*.cpp, true)}
        src/Components/meshcomponent.cpp \
        src/Objects/cubemesh.cpp \
        src/Objects/objectmanager.cpp \
        src/Camera/camera.cpp \
        src/game.cpp \
        src/keyboardmanager.cpp

HEADERS += \
        #$${files(src/*.h, true)} \
        src/Components/component.h \
        src/Components/meshcomponent.h \
        src/Objects/color.h \
        src/Objects/cubemesh.h \
        src/Objects/gameobject.h \
        src/Objects/objectmanager.h \
        src/Objects/transform.h \
        src/Camera/camera.h \
        src/game.h \
        src/keyboardmanager.h

INCLUDEPATH += src/
