#include "GameObject.h"
GameObject::GameObject() :
    pos(0.0f),
    euler(0.0f),
    scale(1.0f) {
    doesDebugDraw = true;
}

void GameObject::Reset() {
    SetPosition(Vector3::Zero());
    SetScale(Vector3::Zero());
    euler.SetZero();
}

void GameObject::Draw(Camera* cam) {
    if (shader && mesh) {
        const Matrix4 mv = WorldToLocal().Transposed();
        const Matrix4 mvp = cam->Matrix() * LocalToWorld();
        shader->Use();
        if (texture) {
            texture->Use();
        }
        shader->SetMVP(mvp.m, mv.m);
        mesh->Draw();
    }
}

Vector3 GameObject::Forward() const {
    return
        -(Matrix4::CreateRotationZ(euler.z) *
          Matrix4::CreateRotationX(euler.x) *
          Matrix4::CreateRotationY(euler.y)
          ).ZAxis();
}

void GameObject::DebugDraw(Camera* cam)
{
    if (doesDebugDraw) {
        //DebugDrawCube(cam, pos, scale);
    }
}

Matrix4 GameObject::LocalToWorld() {
    return
        Matrix4::CreateTranslation(pos) *
        Matrix4::CreateRotationY(euler.y) *
        Matrix4::CreateRotationX(euler.x) *
        Matrix4::CreateRotationZ(euler.z) *
        Matrix4::CreateScale(scale);
}

Matrix4 GameObject::WorldToLocal() {
    return
        Matrix4::CreateScale(1.0f / scale) *
        Matrix4::CreateRotationZ(-euler.z) *
        Matrix4::CreateRotationX(-euler.x) *
        Matrix4::CreateRotationY(-euler.y) *
        Matrix4::CreateTranslation(-pos);
}