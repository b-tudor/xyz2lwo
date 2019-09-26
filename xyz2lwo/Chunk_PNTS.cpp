#include "Chunk_PNTS.h"
#include <algorithm>
#include <limits.h>

Chunk_PNTS::~Chunk_PNTS(){}
Chunk_PNTS:: Chunk_PNTS() {
	ck_ID = IFF::IDTag("PNTS");
	for (int i = 0; i < 3; i++) {
		hi[i] = -1e50; // smaller than smallest float possible
		lo[i] =  1e50; // larger than largest float possible
		// LWO2 point data is in float, so starting with the high point lower than possible
		// for a float will ensure that ANY float will be big enough to take the "top spot". 
		// Vice-versa for lowest point. 
	}
}



void Chunk_PNTS::write(std::ofstream &outFile) {

	IFF::uLONG *buffer = (IFF::uLONG *) calloc(chunk_buffer_size(), sizeof(IFF::uBYTE));

	buffer[0] = ck_ID;
	buffer[1] = chunk_data_size_BigE();

	int i = 2;
	for_each(points.begin(), points.end(), [&i,buffer](Vector3D r) {
		buffer[i++] = IFF::encode_BigEndian_32_double( r.x());
		buffer[i++] = IFF::encode_BigEndian_32_double( r.y());
		buffer[i++] = IFF::encode_BigEndian_32_double( r.z());
	});

	outFile.write( (char*) buffer, (size_t) chunk_buffer_size() );
	free(buffer);
}




void Chunk_PNTS::add_point(Vector3D point) { 
	points.push_back(point); 
	
	float current_point[3];
	current_point[0] = (float) point.x();
	current_point[1] = (float) point.y();
	current_point[2] = (float) point.z();

	// See if there are any new records as far as greatest / lowest seen x, y or z coordinates
	for (int i = 0; i < 3; i++) {
		if ( current_point[i] > hi[i] )
			hi[i] = current_point[i];
		if ( current_point[i] < lo[i] )
			lo[i] = current_point[i];
	}
}




