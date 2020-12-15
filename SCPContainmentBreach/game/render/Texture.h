#ifndef HF_TEXTURE
#define HF_TEXTURE

#include "GL/glew.h"

// Careful when deleting texture pointers because some are contained in PRESETS.Textures
class Texture {
public:
	Texture(const char* fname, int rows, int cols);

	void Use();

private:
	GLuint texId;
	bool is3D;
};

#endif