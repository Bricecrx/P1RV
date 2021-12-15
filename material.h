#ifndef OGLDEV_MATERIAL_H
#define OGLDEV_MATERIAL_H

#include <stdio.h>
#include <string>
#include <math.h>
#include <glew.h>
#include <freeglut.h>
#include "math_3d.h"
#include "util.h"
#include <time.h>
#include "vertex.h"
#include "pipeline.h"
#include "world_transform.h"
#include "camera.h"
#include "stb_image.h"
#include "texture.h"
#include "technique.h"
#include "lightingtechnique.h"


class Material {

public:
    Vector3f AmbientColor = Vector3f(0.0f, 0.0f, 0.0f);
    Vector3f DiffuseColor = Vector3f(0.0f, 0.0f, 0.0f);
    Vector3f SpecularColor = Vector3f(0.0f, 0.0f, 0.0f);

    // TODO: need to deallocate these
    Texture* pDiffuse = nullptr; // base color of the material
    Texture* pSpecularExponent = nullptr;
};


#endif
