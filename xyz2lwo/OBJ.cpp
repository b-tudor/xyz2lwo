#include "OBJ.h"


#include <fstream>
#include <iomanip>
#include <iostream>

#include "OBJ_group.h"
#include "Sphere.h"

#include <algorithm>

//  CONSTRUCTORS / DESTRUCTORS  ///////////////////////////////////////////////////////////////////////////////////////

OBJ::~OBJ() {}
OBJ:: OBJ() {}




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


void OBJ::write(std::string filename) {

	int nGroups = (int) groups.size();
	if( nGroups == 0)
		return; // Nothing to write
	
	// offset is an array of numbers that will be added to the vertex IDs when writing f commands since
	// all f's pull from the same master list of vertices, but in this code all groups have references
	// to their own local vertices (starting at 0)
	std::vector<int> offset;
	// The offset for the first group of vertices is 1, since the numbering of vertices starts at 1 in.OBJ files.
	offset.push_back(1);
	// This 1 will propogate down thru all the remaining offsets when we compute the cumulative offset for each group.
	 


	// open the file
	//std::ofstream outFile(filename, std::ios::binary | std::ios::out);

	// Write all the data sections
	
	// Write all the vertices for all groups
	for (auto& g : groups) {

		// Retrieve how many vertices are in this group, so we will know how much this group will contribute
		// to the offsets of the vertex IDs for all groups that follow. 
		offset.push_back( (int) g.points().size() );

		for (auto& p : g.points())
			std::cout << std::fixed << std::setprecision(6) << "v " << p.x() << " " << p.y() << " " << p.z() << "\n";
	}
	
	// Compute cumulative offset
	// The vertices of each group's faces appear in the .OBJ file's vertex list after the vertices of all the groups
	// before it. Each group is self-contained and doesn't know about the vertices of any other group. So... when a 
	// group references its own vertex 1 (for example), the vertex it means (wrt the final .OBJ file) is the first 
	// one in the block of vertices that were added on its behalf. These vertices appears in the final list of vertices
	// AFTER all the vertices of the groups that were added first. Ergo, we add the quantity of vertices that were
	// written for all groups that appeared first in the file to the vertex IDs of a given group in order to shift
	// the "window" of vertices referenced by a group of f commands down by the number of prior vertices. For example,
	// if the first group in a file has 5 vertices, its f commands will number those vertices 1, 2, 3, 4 & 5. If there
	// is a second group added to the file, and it has 3 vertices, in the final .OBJ file, the f commands for that
	// second group will be referenced by the IDs 6, 7 & 8.
	for( int i=1; i<nGroups; i++ )
		offset[i] += offset[i-1];	

	// Write the faces
	int groupNo = -1;
	for( auto& g : groups ) {

		groupNo++; // Used to index into the correct offset when referring to vertices

		std::cout << "g "      << g.name()     << "\n";
		std::cout << "usemtl " << g.material() << "\n";

		for( auto& f : g.faces()) {
			std::cout << "f ";
			for(int i=0; i<f.vertex_count; i++ )
				std::cout << f.vertex[i] + offset[groupNo] << " ";
			std::cout << "\n";
		}
	}
	
	// close file
	//outFile.close();
}