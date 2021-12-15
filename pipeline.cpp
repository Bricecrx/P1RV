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

void Pipeline::Scale(float ScaleX, float ScaleY, float ScaleZ) {
	Matrix4f ret = Matrix4f(ScaleX, 0, 0, 0,
							0, ScaleY, 0, 0,
							0, 0, ScaleZ, 0,
							0, 0, 0, 1);
	m_transformation = ret * m_transformation;
}

void Pipeline::Rotate(float RotateX, float RotateY, float RotateZ) {
	Matrix4f retX = Matrix4f(1, 0, 0, 0,
		0, cos(ToRadian(RotateX)), -sin(ToRadian(RotateX)), 0,
		0, sin(ToRadian(RotateX)), cos(ToRadian(RotateX)), 0,
		0, 0, 0, 1);
	Matrix4f retY = Matrix4f(cos(ToRadian(RotateY)), 0, -sin(ToRadian(RotateY)), 0,
		0, 1, 0, 0,
		sin(ToRadian(RotateY)), 0, cos(ToRadian(RotateY)), 0,
		0, 0, 0, 1);
	Matrix4f retZ = Matrix4f(cos(ToRadian(RotateZ)), -sin(ToRadian(RotateZ)), 0, 0,
		sin(ToRadian(RotateZ)), cos(ToRadian(RotateZ)), 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1);
	m_transformation = retX * retY * retZ * m_transformation;
}

void Pipeline::WorldPos(float x, float y, float z) {
	Matrix4f ret = Matrix4f(1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0, 0, 0, 1);
	m_transformation = ret * m_transformation;
}

const Matrix4f Pipeline::GetTrans() {
	Matrix4f ret = Matrix4f();
	Scale(m_scale.x, m_scale.y, m_scale.z);
	Rotate(m_rotateInfo.x, m_rotateInfo.y, m_rotateInfo.z);
	WorldPos(m_worldPos.x, m_worldPos.y, m_worldPos.z);
	ret = m_transformation;
	return ret;
}