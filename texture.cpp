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

Texture::Texture(GLenum TextureTarget, const std::string& FileName)
{
    m_textureTarget = TextureTarget;
    m_fileName = FileName;
}


bool Texture::Load()
{
    stbi_set_flip_vertically_on_load(1); //Pour que l'image soit représentée dans le sens habituel (axes t,s)
    int width = 0, height = 0, bpp = 0;
    unsigned char* image_data = stbi_load(m_fileName.c_str(), &width, &height, &bpp, 0); //bpp = bits per pixel

    //Check pour une erreur et renvoie un message d'erreur adapté si besoin.
    if (!image_data) {
        printf("Can't load texture from '%s' - %s\n", m_fileName.c_str(), stbi_failure_reason());
        exit(0);
    }
    printf("Width %d, height %d, bpp %d\n", width, height, bpp);

    //On crée la texture et on la lie à sa cible, de la même manière qu'un buffer
    glGenTextures(1, &m_textureObj);

    //Lie la texture crée pour modifier les paramètres
    glBindTexture(m_textureTarget, m_textureObj);

    //On ne gère que le cas des textures 2D dans cette classe (pas de 1D ou de 3D)
    if (m_textureTarget == GL_TEXTURE_2D) {
        glTexImage2D(m_textureTarget, 0, GL_RGB, 2048, 2048, 0, GL_RGB, GL_UNSIGNED_BYTE, image_data); //(2d texture, mipmapping, color format of the texture, width and height of the image used, must be 0 always, type of texture, loaded image data   
    }
    else {
        printf("Support for texture target %x is not implemented\n", m_textureTarget);
        exit(1);
    }

    //Paramètres de la texture
    glTexParameterf(m_textureTarget, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //Si redimensionnement, interpolation linéaire
    glTexParameterf(m_textureTarget, GL_TEXTURE_MAG_FILTER, GL_LINEAR); //Idem
    glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameterf(m_textureTarget, GL_TEXTURE_WRAP_T, GL_REPEAT);

    //Délie la textrue
    glBindTexture(m_textureTarget, 0);

    //Libère la mémoire liée à l'image dans le stbi
    stbi_image_free(image_data);

    return true;
}

void Texture::Bind(GLenum TextureUnit)
{
    glActiveTexture(TextureUnit);
    glBindTexture(m_textureTarget, m_textureObj);
}