#ifndef HF_HEADERNAME
#define HF_HEADERNAME
#include "../../render/Presets.h"
class Sky {
public:
    Sky() {
        mesh = PRESETS.Meshes.Quad;
        shader = PRESETS.Shaders.Sky;
    }
    ~Sky() { }

    void Draw(Camera* cam) {
        glDepthMask(GL_FALSE);
        const Matrix4 mvp = cam->projection.Inverse();
        const Matrix4 mv = cam->worldView.Inverse();
        shader->Use();
        shader->SetMVP(mvp.m, mv.m);
        mesh->Draw();
        glDepthMask(GL_TRUE);
    }

private:
    Mesh* mesh;
    Shader* shader;
};

#endif