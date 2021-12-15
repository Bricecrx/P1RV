#include "lightingtechnique.h"

void DirectionalLight::CalcLocalDirection(const Matrix4f& World)
{
    Matrix3f World3f(World);  // Initialize using the top left corner

    // Inverse local-to-world transformation using transpose
    // (assuming uniform scaling)
    Matrix3f WorldToLocal = World3f.Transpose();

    LocalDirection = WorldToLocal * WorldDirection;

    LocalDirection = LocalDirection.Normalize();
}


LightingTechnique::LightingTechnique()
{
}

bool LightingTechnique::Init()
{
    //Vérifie qu'on hérite bien de la classe mère
    if (!Technique::Init()) {
        return false;
    }

    //Vérifie qu'on a bien le bon type de shaders
    if (!AddShader(GL_VERTEX_SHADER, "lighting.vs")) {
        return false;
    }
    if (!AddShader(GL_FRAGMENT_SHADER, "lighting.fs")) {
        return false;
    }


    if (!Finalize()) {
        return false;
    }

    //On récupère les variables uniformes
    WVPLoc = GetUniformLocation("gWVP");
    samplerLoc = GetUniformLocation("gSampler");
    samplerSpecularExponentLoc = GetUniformLocation("gSamplerSpecularExponent");
    materialLoc.AmbientColor = GetUniformLocation("gMaterial.AmbientColor");
    materialLoc.DiffuseColor = GetUniformLocation("gMaterial.DiffuseColor");
    materialLoc.SpecularColor = GetUniformLocation("gMaterial.SpecularColor");
    dirLightLoc.Color = GetUniformLocation("gDirectionalLight.Color");
    dirLightLoc.AmbientIntensity = GetUniformLocation("gDirectionalLight.AmbientIntensity");
    dirLightLoc.Direction = GetUniformLocation("gDirectionalLight.Direction");
    dirLightLoc.DiffuseIntensity = GetUniformLocation("gDirectionalLight.DiffuseIntensity");
    CameraLocalPosLoc = GetUniformLocation("gCameraLocalPos");

    //On vérifie qu'on a bien récupéré (une seconde fois car déjà fait dans la fonction GetUniformLocation définie dans la classe Technique)
    if (WVPLoc == 0xFFFFFFFF ||
        samplerLoc == 0xFFFFFFFF ||
        samplerSpecularExponentLoc == 0xFFFFFFFF ||
        materialLoc.AmbientColor == 0xFFFFFFFF ||
        materialLoc.DiffuseColor == 0xFFFFFFFF ||
        materialLoc.SpecularColor == 0xFFFFFFFF ||
        CameraLocalPosLoc == 0xFFFFFFFF ||
        dirLightLoc.Color == 0xFFFFFFFF ||
        dirLightLoc.DiffuseIntensity == 0xFFFFFFFF ||
        dirLightLoc.Direction == 0xFFFFFFFF ||
        dirLightLoc.AmbientIntensity == 0xFFFFFFFF)
    {
        return false;
    }

    return true;
}

void LightingTechnique::SetWVP(const Matrix4f& WVP)
{
    glUniformMatrix4fv(WVPLoc, 1, GL_TRUE, (const GLfloat*)WVP.m);
}


void LightingTechnique::SetTextureUnit(unsigned int TextureUnit)
{
    glUniform1i(samplerLoc, TextureUnit);
}

void LightingTechnique::SetSpecularExponentTextureUnit(unsigned int TextureUnit) {
    glUniform1i(samplerSpecularExponentLoc, TextureUnit);
}

void LightingTechnique::SetDirectionalLight(const DirectionalLight& Light)
{
    glUniform3f(dirLightLoc.Color, Light.Color.x, Light.Color.y, Light.Color.z);
    glUniform1f(dirLightLoc.AmbientIntensity, Light.AmbientIntensity);
    Vector3f LocalDirection = Light.GetLocalDirection();
    glUniform3f(dirLightLoc.Direction, LocalDirection.x, LocalDirection.y, LocalDirection.z);
    glUniform1f(dirLightLoc.DiffuseIntensity, Light.DiffuseIntensity);
}

void LightingTechnique::SetCameraLocalPos(const Vector3f& CameraLocalPos) {
    glUniform3f(CameraLocalPosLoc, CameraLocalPos.x, CameraLocalPos.y, CameraLocalPos.z);
}


void LightingTechnique::SetMaterial(const Material& material)
{
    glUniform3f(materialLoc.AmbientColor, material.AmbientColor.r, material.AmbientColor.g, material.AmbientColor.b);
    glUniform3f(materialLoc.DiffuseColor, material.DiffuseColor.r, material.DiffuseColor.g, material.DiffuseColor.b);
    glUniform3f(materialLoc.SpecularColor, material.SpecularColor.r, material.SpecularColor.g, material.SpecularColor.b);
}