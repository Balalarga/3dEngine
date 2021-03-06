TEMPLATE = app
CONFIG += console c++17
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
        src/Components/cameracomponent.cpp \
        src/Components/meshcomponent.cpp \
        src/Components/physicscomponent.cpp \
        src/Objects/gameobject.cpp \
        src/Objects/game.cpp \
        src/Systems/FileSystem/filesystem.cpp \
        src/Systems/RenderSystem/baserenderer.cpp \
        src/Systems/RenderSystem/openglrenderer.cpp \
        src/Systems/InputSystem/inputsystem.cpp \
        src/Systems/RenderSystem/Shader/openglshader.cpp \
        src/Systems/objectsystem.cpp \
        src/Systems/RenderSystem/rendersystem.cpp \
        src/Utils/utils.cpp

HEADERS += \
        #$${files(src/*.h, true)} \
        sandboxgame.h \
        src/Components/basecomponent.h \
        src/Components/cameracomponent.h \
        src/Components/components.h \
        src/Components/meshcomponent.h \
        src/Components/physicscomponent.h \
        src/Objects/gameobject.h \
        src/Objects/transform.h \
        src/Objects/game.h \
        src/Systems/FileSystem/filesystem.h \
        src/Systems/InputSystem/keycodes.h \
        src/Systems/RenderSystem/baserenderer.h \
        src/Systems/RenderSystem/Shader/baseshader.h \
        src/Systems/RenderSystem/openglrenderer.h \
        src/Systems/InputSystem/inputsystem.h \
        src/Systems/RenderSystem/Shader/openglshader.h \
        src/Systems/objectsystem.h \
        src/Systems/RenderSystem/rendersystem.h \
        src/Systems/systems.h \
        src/Utils/utils.h \
        src/glIncludes.h \
        src/Utils/utils.h

DISTFILES +=
