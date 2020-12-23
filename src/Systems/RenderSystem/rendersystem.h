#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "baserenderer.h"
#include "OpenGL/openglrenderer.h"
#include <memory>

class RenderSystem
{
public:
    static RenderSystem& Instance();

    template<class T, class ...TArgs>
    void CreateRenderer(TArgs&&... args){
        renderer = std::make_unique<T>(std::forward<TArgs>(args)...);
    }
    BaseRenderer* GetRender();

private:
    std::unique_ptr<BaseRenderer> renderer;
    static RenderSystem* selfInstance;
    RenderSystem();
};

#endif // RENDERSYSTEM_H
