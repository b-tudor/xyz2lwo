#include "OBJ_group.h"

#include "IFF.h"


void OBJ_group::add_points( std::vector<Vector3D> points ) {

	// transfer the passed-in points into the .OBJ's data
	for( auto p:points )
		vertices.push_back(p);
}



void OBJ_group::add_faces(std::vector<IFF::Face> faces) {

	add_faces(faces, "Default");

}
void OBJ_group::add_faces(std::vector<IFF::Face> polygons, std::string surfaceID) {

	// Transfer the passed-in points into the .OBJ's data. Each polygon references the
	// points in "vertices" by number, where the numbering of the vertices starts at 1
	set_material(surfaceID);
	for (auto p : polygons)
		faces.push_back(p);
	
}