/* Contient la définition de la classe worldtransform, qui va synthétiser de nombreuses informations */

#ifndef WORLD_TRANSFORM_H
#define WORLD_TRANSFORM_H

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
//#include "pipeline.h"

class WorldTrans {
protected:
	float m_scale = 1.0f;
	Vector3f m_rotation = Vector3f(0.0f,0.0f,0.0f);
	Vector3f m_pos = Vector3f(0.0f,0.0f,0.0f);

public:
	WorldTrans() {}

	void SetScale(float s);
	void SetRotation(float x, float y, float z); //On pourrait surcharger pour le faire aussi avec un vecteur, fixe les angles de rotation sur chaque axe
	void SetPosition(float x, float y, float z); //Idem

	void Rotate(float x, float y, float z); //idem, ajoute ou enlève des angles de rotation sur chaque axe
	Matrix4f GetMatrix();

	Matrix4f GetReversedTranslationMatrix() const;
	Matrix4f GetReversedRotationMatrix() const;

	float GetScale() const { return m_scale; }
	Vector3f GetPos() const { return m_pos; }
	Vector3f GetRotation() const { return m_rotation; }


};











#endif