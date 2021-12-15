#ifndef PIPELINE_H
#define PIPELINE_H

#include <Windows.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <glew.h>
#include <freeglut.h>
#include "math_3d.h"
#include "util.h"
#include <time.h>
#include "vertex.h"

class Pipeline {
private:
    Vector3f m_scale;
    Vector3f m_worldPos;
    Vector3f m_rotateInfo;
    Matrix4f m_transformation;

public:

    //Constructeurs
    Pipeline() {
        this -> m_scale = Vector3f(0, 0, 0);
        this->m_worldPos = Vector3f(0, 0, 0);
        this->m_rotateInfo = Vector3f(0, 0, 0);
        this->m_transformation = Matrix4f();
    }

    Pipeline(Vector3f a, Vector3f b, Vector3f c) {
        this->m_scale = Vector3f(a.x, a.y, a.z);
        this->m_rotateInfo = Vector3f(b.x, b.y, b.z);
        this->m_worldPos = Vector3f(c.x, c.y, c.z);
        this->m_transformation = Matrix4f();
    }

    //Setteurs
    void Scale(float ScaleX, float ScaleY, float ScaleZ);
    void WorldPos(float x, float y, float z);
    void Rotate(float RotateX, float RotateY, float RotateZ);

    //Getteurs
    const Matrix4f GetTrans();
};






#endif