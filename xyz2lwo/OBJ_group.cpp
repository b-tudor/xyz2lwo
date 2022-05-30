#include "OBJ_group.h"

#include "IFF.h"


void OBJ_group::add_points( std::vector<Vector3D> points ) {

	for( auto p:points )
		vertices.push_back(p);
}



void OBJ_group::add_faces(std::vector<IFF::Face> faces) {

	add_faces(faces, "Default");

}
void OBJ_group::add_faces(std::vector<IFF::Face> polygons, std::string surfaceID) {

	set_material(surfaceID);
	for (auto p : polygons)
		faces.push_back(p);
	
}