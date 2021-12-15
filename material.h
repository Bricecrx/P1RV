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

#include <assimp/Importer.hpp>      // C++ importer interface
#include <assimp/scene.h>       // Output data structure
#include <assimp/postprocess.h> // Post processing flags


class Material {

public:
    aiColor3D AmbientColor = aiColor3D(0.0f, 0.0f, 0.0f);
    aiColor3D DiffuseColor = aiColor3D(0.0f, 0.0f, 0.0f);
    aiColor3D SpecularColor = aiColor3D(0.0f, 0.0f, 0.0f);
    
    /*
    Vector3f AmbientColor = Vector3f(0.0f, 0.0f, 0.0f);
    Vector3f DiffuseColor = Vector3f(0.0f, 0.0f, 0.0f);
    Vector3f SpecularColor = Vector3f(0.0f, 0.0f, 0.0f);
    */

    // TODO: need to deallocate these
    Texture* pDiffuse = nullptr; // base color of the material
    Texture* pSpecularExponent = nullptr;
};


#endif
