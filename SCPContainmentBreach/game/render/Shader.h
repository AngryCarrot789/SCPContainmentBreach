#ifndef HF_SHADER
#define HF_SHADER

#include "GL/glew.h"
#include <vector>
#include <string>
#include <iostream>
#include "../../standard.h"

class Shader {
public:
  Shader(const char* name);
  ~Shader();

  void Use();
  void SetMVP(const float* mvp, const float* mv);

private:
  GLuint LoadShader(const char* fname, GLenum type);

  std::vector<string_t> attribs;
  GLuint vertId;
  GLuint fragId;
  GLuint progId;
  GLuint mvpId;
  GLuint mvId;
};

#endif