#ifndef TEXTURE_H
#define TEXTURE_H

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

#ifdef USE_IMAGE_MAGICK
#include <ImageMagick-6/Magick++.h>
#endif

class Texture
{
public:
    Texture(GLenum TextureTarget, const std::string& FileName);

    // Should be called once to load the texture
    bool Load();

    // Must be called at least once for the specific texture unit
    void Bind(GLenum TextureUnit);

private:
    std::string m_fileName;
    GLenum m_textureTarget;
    GLuint m_textureObj;
};


#endif  /* TEXTURE_H */
