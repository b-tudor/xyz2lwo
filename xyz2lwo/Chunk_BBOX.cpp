#include "Chunk_BBOX.h"
#include <algorithm>

Chunk_BBOX::~Chunk_BBOX(){}
Chunk_BBOX:: Chunk_BBOX() {
	ck_ID = buffer[0] = IFF::IDTag("BBOX");
	for( int i=1; i<8; i++ )
		buffer[i] = 0;
}



void Chunk_BBOX::write(std::ofstream &outFile) {
	buffer[1] = chunk_data_size_BigE();
	outFile.write( (char*) & buffer, chunk_buffer_size()); // 2 points @ 12 bytes per point + 8 byte header
}



void Chunk_BBOX::set_HI(Vector3D v) {
	buffer[5] = IFF::encode_BigEndian_32_double( v.x() );
	buffer[6] = IFF::encode_BigEndian_32_double( v.y() );
	buffer[7] = IFF::encode_BigEndian_32_double( v.z() );
}



void Chunk_BBOX::set_LO(Vector3D v) {
	buffer[2] = IFF::encode_BigEndian_32_double( v.x() );
	buffer[3] = IFF::encode_BigEndian_32_double( v.y() );
	buffer[4] = IFF::encode_BigEndian_32_double( v.z() );
}