#ifndef HF_HEADERNAME
#define HF_HEADERNAME
#include "../../render/presets/Presets.h"
class Sky {
public:
    Sky() {
        mesh = QUAD;
        shader = SKY;
    }

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