#include "WavefrontOBJ.h"


#include <fstream>
#include <iomanip>
#include <iostream>


#include "OBJ_group.h"
#include "Sphere.h"

#include <algorithm>

//  CONSTRUCTORS / DESTRUCTORS  ///////////////////////////////////////////////////////////////////////////////////////

WavefrontOBJ::~WavefrontOBJ() {
	#ifdef WIN32
		outputMode = outMode::MSDOS;
	#else	
		outputMode = outMode::UNIX;
	#endif
}
WavefrontOBJ:: WavefrontOBJ() {}




void WavefrontOBJ::add_group(OBJ_group og) {
	groups.push_back(og);
}


void WavefrontOBJ::add_object(Object3D obj, std::string ID) {
	OBJ_group oGroup;
	oGroup.add_points( obj.points );
	oGroup.add_faces ( obj.faces, ID );
	add_group( oGroup );
}


void WavefrontOBJ::write(std::string filename ) {
	
	// Sort out the EOL character based on the desired style of text file output
	const char CRNL[3] = { (char) 0x0d, (char) 0x0a, (char) 0x00 }; // 
	const char *EOL = nullptr;
	if( outputMode == outMode::MSDOS )
		EOL = CRNL;       // MS-DOS gets the full carriage return + newline output sequence
	else
	if( outputMode == outMode::UNIX  )
		EOL = &(CRNL[1]); // Unix output just gets the Newline character only




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
	std::ofstream outFile( filename, std::ofstream::out );
	if(!outFile) {
		std::cout << "Unable to open output file: " << filename << "\nOutput file was not written." << std::endl;
		return;
	}

	// Write all the data sections
	
	// Write all the vertices for all groups
	for (auto& g : groups) {

		// Retrieve how many vertices are in this group, so we will know how much this group will contribute
		// to the offsets of the vertex IDs for all groups that follow. 
		offset.push_back( (int) g.points().size() );

		for (auto& p : g.points())
			outFile << std::fixed << std::setprecision(6) << "v " << p.x() << " " << p.y() << " " << p.z() << EOL;
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

		outFile << "g " << g.name() << EOL;
		if(g.smooth())
			outFile << "s " << groupNo << EOL;
		outFile << "usemtl " << g.material() << EOL;

		for( auto& f : g.faces()) {
			outFile << "f ";
			for(int i=0; i<f.vertex_count; i++ )
				outFile << f.vertex[i] + offset[groupNo] << " ";
			outFile << EOL;
		}
	}
	
	// close file
	outFile.close();
}