#pragma once 
#include <vector>

#include "IFF.h"
#include "Object3D.h"
#include "Vector3D.h"

class OBJ_group {

	

	// Data
	private:
		std::string Name;
		std::string Material;
		std::vector<Vector3D> Vertices;
		std::vector<Object3D::Face> Faces;

	// Methods

	public:

		// Initializer
		OBJ_group();

		// Getters
		std::string name    () { return Name; }
		std::string material() { return Material; }
		std::vector<Vector3D> &points  () { return Vertices; }
		std::vector<Object3D::Face>& faces  () { return Faces;    }
		
		// Setters
		void set_name    (std::string n) {     Name = n; }
		void set_material(std::string m) { Material = m; };
		
		// Add Geometry
		void add_points( std::vector<Vector3D>  &p );
		void add_faces ( std::vector<Object3D::Face> &polygons );
		void add_faces ( std::vector<Object3D::Face> &polygons, std::string objectName );
		void add_faces ( std::vector<Object3D::Face> &polygons, std::string objectName, std::string materialName );
};