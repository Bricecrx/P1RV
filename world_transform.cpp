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

void WorldTrans::SetScale(float s) {
	m_scale = s;
}

void WorldTrans::SetRotation(float x, float y, float z) {
	m_rotation.x = x;
	m_rotation.y = y;
	m_rotation.z = z;
}

void WorldTrans::SetPosition(float x, float y, float z) {
	m_pos.x = x;
	m_pos.y = y;
	m_pos.z = z;
}

void WorldTrans::Rotate(float x, float y, float z) {
	m_rotation.x += x;
	m_rotation.y += y;
	m_rotation.z += z;
}

Matrix4f WorldTrans::GetMatrix() {
	
	//Scale Matrix
	Matrix4f Scale;
	Scale.InitScaleTransform(m_scale, m_scale, m_scale); //On utilise des fonctions pré écrites

	//Rotation matrix
	Matrix4f Rotation;
	Rotation.InitRotateTransform(m_rotation.x, m_rotation.y, m_rotation.z);

	//Translation matrix
	Matrix4f Translation;
	Translation.InitTranslationTransform(m_pos.x, m_pos.y, m_pos.z);

	//Final matrix
	Matrix4f WorldTransfo;
	WorldTransfo = Translation * Rotation * Scale;
	return WorldTransfo;
}

Matrix4f WorldTrans::GetReversedTranslationMatrix() const
{
	Matrix4f ReversedTranslation;
	ReversedTranslation.InitTranslationTransform(m_pos.Negate().x, m_pos.Negate().y, m_pos.Negate().z);
	return ReversedTranslation;
}


Matrix4f WorldTrans::GetReversedRotationMatrix() const
{
	Matrix4f ReversedRotation;
	ReversedRotation.InitRotateTransformZYX(-m_rotation.x, -m_rotation.y, -m_rotation.z);
	return ReversedRotation;
}
