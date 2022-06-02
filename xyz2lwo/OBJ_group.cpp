#include "IFF.h"
#include "OBJ_group.h"

OBJ_group::OBJ_group() {
	Name = "Default";
	Material = "Default";
}

void OBJ_group::add_points( std::vector<Vector3D> &points ) {

	// transfer the passed-in points into the .OBJ's data
	for( auto p:points )
		Vertices.push_back(p);
}




// Transfer the passed-in points into the .OBJ's data. Each polygon references the
// points in "vertices" by number, where the numbering of the vertices starts at 1












void OBJ_group::add_faces(std::vector<IFF::Face>& FacesToAdd) {
	add_faces(FacesToAdd, "Default");
}
void OBJ_group::add_faces(std::vector<IFF::Face>& FacesToAdd, std::string objectName) {
	add_faces(FacesToAdd, objectName, objectName);
}
void OBJ_group::add_faces(std::vector<IFF::Face>& FacesToAdd, std::string objectName, std::string materialName) {
	set_name(objectName);
	set_material(materialName);
	for (auto f : FacesToAdd)
		Faces.push_back(f);
}