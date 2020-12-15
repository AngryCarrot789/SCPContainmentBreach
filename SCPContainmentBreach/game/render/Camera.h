#ifndef HF_CAMERA
#define HF_CAMERA

#include "../../math/Matrix4.h"

class Camera {
public:
  Camera();

  Matrix4 InverseProjection() const;

  Matrix4 Matrix() const;

  void SetSize(int w, int h, float n, float f, float fov);
  void SetPositionOrientation(const Vector3& pos, float rotX, float rotY);

  void UseViewport() const;

  void ClipOblique(const Vector3& pos, const Vector3& normal);

  Matrix4 projection;
  Matrix4 worldView;

  int width;
  int height;
  float cam_near;
  float cam_far;
};

#endif