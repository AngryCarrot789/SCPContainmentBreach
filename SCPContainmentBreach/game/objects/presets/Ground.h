#ifndef HF_GROUND
#define HF_GROUND

#include "../GameObject.h"

class Ground : public GameObject
{
public:
    Ground() {
        mesh = new Mesh("ground.obj");
        shader = new Shader("texture");
        texture = new Texture("checker_green.bmp", 1, 1);
        scale = Vector3(10, 1, 10);
    }
    virtual ~Ground() {}
};

#endif