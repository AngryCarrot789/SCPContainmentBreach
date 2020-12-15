#ifndef HF_CUBE
#define HF_CUBE

#include "../GameObject.h"

class Cube : public GameObject
{
public:
    Cube() {
        mesh = PRESETS.Meshes.Cube;
        shader = PRESETS.Shaders.Texture;
        texture = PRESETS.Textures.Electromagnet;
    }
};

#endif