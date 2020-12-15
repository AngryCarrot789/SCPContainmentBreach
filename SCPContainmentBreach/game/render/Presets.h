#ifndef HF_PRESETTHINGS
#define HF_PRESETTHINGS

#include "Shader.h"
#include "Mesh.h"
#include "Texture.h"

class PresetMeshes
{
public:
	PresetMeshes() {}
	Mesh* Quad;
	Mesh* Cube;
	Mesh* Tunnel;
	Mesh* Ground;
	Mesh* TeaPot;
	Mesh* Bunny;

	void Dispose() {
		delete(Quad);
		delete(Cube);
		delete(Tunnel);
		delete(Ground);
		delete(TeaPot);
		delete(Bunny);
	}
};

class PresetShaders
{
public:
	PresetShaders() {}
	Shader* Sky;
	Shader* Pink;
	Shader* Texture;

	void Dispose() {
		delete(Sky);
		delete(Pink);
		delete(Texture);
	}
};

class PresetTextures
{
public:
	PresetTextures() {}
	Texture* Electromagnet;
	Texture* CheckerboardGrey;
	Texture* CheckerboardGreen;
	Texture* Gold;
	Texture* White;

	void Dispose() {
		delete(Electromagnet);
		delete(CheckerboardGrey);
		delete(CheckerboardGreen);
		delete(Gold);
		delete(White);
	}
};

class Presets
{
public:
	Presets() { }

	PresetMeshes Meshes;
	PresetShaders Shaders;
	PresetTextures Textures;

	void Dispose() {
		Meshes.Dispose();
		Shaders.Dispose();
		Textures.Dispose();
	}
};

extern Presets PRESETS;

#endif // !HF_PRESETTHINGS