#include "LWOB_Builder.h"
#include "Sphere.h"

#include <algorithm>

//  CONSTRUCTORS / DESTRUCTORS  ///////////////////////////////////////////////////////////////////////////////////////

LWOB_Builder::~LWOB_Builder() {}
LWOB_Builder:: LWOB_Builder() {
	
	point_limit = 0;
	new_pnt_chunk = false;

	tag_strings.add_tag_string("Default");
	lw_object.add_chunk(tag_strings);
	lw_object.add_chunk(layer_data);
	
	lwob.add_chunk(lw_object);
	
}



void LWOB_Builder::write(std::string filename) {
	bounding_box.set_HI(point_data.get_HI());
	bounding_box.set_LO(point_data.get_LO());
	lwob.write(filename);
}



void LWOB_Builder::add_points( std::vector<Vector3D> points ) {

	Chunk_PNTS * ckPoints = new Chunk_PNTS();
	Chunk_BBOX * ckBounds = new Chunk_BBOX();

	new_pnt_chunk = true;
	lw_object.add_chunk( * ckPoints );
	
	for (auto r : points) {
		ckPoints->add_point(r);
	}

	ckBounds->set_HI( ckPoints->get_HI() );
	ckBounds->set_LO( ckPoints->get_LO() );
	lw_object.add_chunk( bounding_box );
}


void LWOB_Builder::add_faces(std::vector<Object3D::Face> &faces) {
	add_faces( faces, "Default" );
}
void LWOB_Builder::add_faces(std::vector<Object3D::Face> &faces, std::string surfaceID) {

	Chunk_POLS* ckPolys = new Chunk_POLS();
	Chunk_PTAG* ckPolySurfs = new Chunk_PTAG();

	lw_object.add_chunk(*ckPolys);
	lw_object.add_chunk(*ckPolySurfs);

	int surfIdx = get_surface_index_by_name(surfaceID);

	for( auto& f:faces ) {

		IFF::Face iffFace = f;
		ckPolys->add_face(iffFace);
		ckPolySurfs->add_surface(surfIdx);
	}
}
void LWOB_Builder::add_faces( std::vector<IFF::Face> &faces ) {
	add_faces(faces, "Default");
}
void LWOB_Builder::add_faces( std::vector<IFF::Face> &faces, std::string surfaceID ) {

	Chunk_POLS * ckPolys     = new Chunk_POLS();
	Chunk_PTAG * ckPolySurfs = new Chunk_PTAG();

	lw_object.add_chunk(*ckPolys);
	lw_object.add_chunk(*ckPolySurfs);

	int surfIdx = get_surface_index_by_name(surfaceID);

	for (unsigned int i = 0; i < faces.size(); i++) {
		ckPolys->add_face(faces[i]);
		ckPolySurfs->add_surface(surfIdx);
	}
}



void LWOB_Builder::add_object(Object3D obj, std::string ID) {
	add_points( obj.points );
	add_faces(  obj.faces, ID );
}



int LWOB_Builder::get_surface_index_by_name( std::string name ) {

	int idx = -1;

	for( unsigned int i=0; i<tag_strings.tag_strings.size(); i++ ) {
		if( ! name.compare(tag_strings.tag_strings[i]) ) {
			idx = i;
			break;
		}
	}

	if (idx < 0) 
		idx = tag_strings.add_tag_string(name);
		
	return idx;
}



void LWOB_Builder::add_surface(Chunk_SURF s) {

	Chunk_SURF * surf = new Chunk_SURF();

	*surf = s;

	lw_object.add_chunk(*surf);
}



