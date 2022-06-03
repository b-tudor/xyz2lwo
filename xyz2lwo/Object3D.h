#pragma once 
#include "Vector3D.h"

#include <vector>

class Object3D
{
	public:

		typedef struct _face {
			unsigned short vertex_count;
			unsigned short vertex[4]; // We will only consider triangular and rectangular polygons            
		} Face;


		std::vector<Vector3D> points;
		std::vector<Face> faces;

		std::vector<Vector3D>* point_data() { return &points; }
		std::vector<Face>*     face_data () { return &faces;  }
};