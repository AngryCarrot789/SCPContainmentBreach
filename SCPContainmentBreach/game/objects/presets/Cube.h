#ifndef HF_CUBE
#define HF_CUBE

#include "../GameObject.h"

class Cube : public GameObject
{
public:
    Cube() {
        mesh = new Mesh("cube.obj");
        shader = new Shader("texture");
        texture = new Texture("electromagnet.bmp", 1, 1);
        scale = Vector3(1, 1, 1);
    }
    virtual ~Cube() {}
};

#endif