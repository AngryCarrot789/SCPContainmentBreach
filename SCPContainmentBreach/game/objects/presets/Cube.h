#ifndef HF_CUBE
#define HF_CUBE

#include "../PhysicalGameObject.h"

class Cube : public PhysicalGameObject
{
public:
    Cube() {
        mesh = PRESETS.Meshes.Cube;
        shader = PRESETS.Shaders.Texture;
        texture = PRESETS.Textures.Electromagnet;

        useGravity = false;
    }
};

#endif