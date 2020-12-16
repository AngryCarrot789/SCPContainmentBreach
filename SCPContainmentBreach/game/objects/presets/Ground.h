#ifndef HF_GROUND
#define HF_GROUND

#include "../PhysicalGameObject.h"

class Ground : public PhysicalGameObject
{
public:
    Ground() {
        //mesh = new Mesh("ground.obj");
        //shader = new Shader("texture");
        //texture = new Texture("checker_green.bmp", 1, 1);
        mesh = PRESETS.Meshes.Ground;
        shader = PRESETS.Shaders.Texture;
        texture = PRESETS.Textures.CheckerboardGreen;
        scale = Vector3(20.0f, 0.001f, 20.0f);
        useGravity = false;
    }
    virtual ~Ground() {}
};

#endif