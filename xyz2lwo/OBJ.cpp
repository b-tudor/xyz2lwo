#include "OBJ.h"
#include "OBJ_group.h"
#include "Sphere.h"

#include <algorithm>

//  CONSTRUCTORS / DESTRUCTORS  ///////////////////////////////////////////////////////////////////////////////////////

OBJ::~OBJ() {}
OBJ:: OBJ() {}



void OBJ::write(std::string filename) {
	// loop over groups
	//     write vertices, record offset
	// loop over groups
	//     write group names
	//     write materials
	//     write faces, adding group offset to vertices indices
}



void OBJ::add_group(OBJ_group og) {
	groups.push_back(og);
}



/*
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
*/

/*
void LWOB_Builder::add_surface(Chunk_SURF s) {

	Chunk_SURF * surf = new Chunk_SURF();

	*surf = s;

	lw_object.add_chunk(*surf);
}
*/


