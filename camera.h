/* Ce fichier contient l'impl�mentation d'une classe cam�ra qui facilitera la compr�hension de notre code principal */

#ifndef CAMERA_H
#define CAMERA_H

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
#include "world_transform.h"

class Camera {
protected:
	Vector3f m_pos;
	Vector3f m_target;
	Vector3f m_up;
	float m_speed = 1.0f;

	int m_windowWidth;
	int m_windowHeight;

	//Pour la transformation du rep�re de la cam�ra
	float m_AngleH;
	float m_AngleV;

	//Pour g�rer le cas des bords d'�cran
	bool m_OnUpperEdge;
	bool m_OnLowerEdge;
	bool m_OnLeftEdge;
	bool m_OnRightEdge;

	Vector2i m_mousePos;

public:
	
	void Init();
	void Update();
	
	Camera(int WindowWidth, int WindowHeight); //Constructeur d�fini dans le cpp
	Camera(int WindowWidth, int WindowHeight, const Vector3f& Pos, const Vector3f& Target, const Vector3f& Up);

	//Setteurs
	void SetPosition(float x, float y, float z);
	void OnKeyBoard(unsigned char key);
	void OnMouse(int x, int y);
	void OnRender();
	Matrix4f GetMatrix();

	const Vector3f& GetPos() const
	{
		return m_pos;
	}

	const Vector3f& GetTarget() const
	{
		return m_target;
	}

	const Vector3f& GetUp() const
	{
		return m_up;
	}
};





#endif