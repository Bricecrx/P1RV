#ifndef TECHNIQUE_H
#define TECHNIQUE_H

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
#include "pipeline.h"
#include "world_transform.h"
#include "camera.h"
#include "stb_image.h"
#include "texture.h"
#include <list>

class Technique
{
private:

    typedef std::list<GLuint> ShaderObjList;
    ShaderObjList m_shaderObjList;

protected:

    bool AddShader(GLenum ShaderType, const char* pFilename);

    bool Finalize();

    GLint GetUniformLocation(const char* pUniformName);

    GLuint m_shaderProg;

public:

    Technique();

    virtual ~Technique();

    virtual bool Init();

    void Enable();
};

#endif
