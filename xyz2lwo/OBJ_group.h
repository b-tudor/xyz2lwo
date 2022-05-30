#pragma once 
#include <vector>

#include "IFF.h"
#include "Vector3D.h"

class OBJ_group {

	// Data
	private:
		std::string Name;
		std::string Material;
		std::vector<Vector3D> vertices;
		std::vector<IFF::Face> faces;

	// Methods

	public:
		// Getters
		std::string name    () { return Name; }
		std::string material() { return Material; }
		// Setters
		void set_name    (std::string n) {     Name = n; }
		void set_material(std::string m) { Material = m; };
		
		// Add Geometry
		void add_points( std::vector<Vector3D> p );
		void add_faces ( std::vector<IFF::Face>     f );
		void add_faces ( std::vector<IFF::Face> f, std::string surfaceID );
};