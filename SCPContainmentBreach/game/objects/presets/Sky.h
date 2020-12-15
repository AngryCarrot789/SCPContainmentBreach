#ifndef HF_HEADERNAME
#define HF_HEADERNAME
#include "../../render/Mesh.h"
#include "../../render/Shader.h"
class Sky {
public:
    Sky() {
        mesh = new Mesh("quad.obj");
        shader = new Shader("sky");
    }
    ~Sky() {
        delete(mesh);
        delete(shader);
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