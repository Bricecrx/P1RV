#ifndef VERTEX_H
#define VERTEX_H

#include <Windows.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <glew.h>
#include <freeglut.h>
#include "math_3d.h"
#include "util.h"
#include <time.h>

class Vertex {
public:
	Vector3f pos;
	Vector2f tex;

	Vertex() {}

	Vertex(const Vector3f& pos_, const Vector2f& tex_) {
		pos = pos_;
		tex = tex_;
	}

};


#endif