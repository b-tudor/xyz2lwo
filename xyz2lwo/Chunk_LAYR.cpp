#include "Chunk_LAYR.h"
#include <algorithm>

Chunk_LAYR::~Chunk_LAYR(){}
Chunk_LAYR:: Chunk_LAYR() {
	ck_ID = IFF::IDTag("LAYR");
	pivotPoint.set(0, 0, 0);
}



void Chunk_LAYR::write(std::ofstream &outFile) {

	// buffer and long_buffer are indexes into the same data block, just with different granularity
	IFF::uLONG *long_buffer = (IFF::uLONG *) buffer;
	long_buffer[0] = ck_ID;
	long_buffer[1] = chunk_data_size_BigE();
 	buffer     [8] = 0; // lyrID    (i.e. long_buffer[ 2 ])
	buffer     [9] = 0; // flg      (i.e. long_buffer[2.5])
	long_buffer[3] = IFF::encode_BigEndian_32_double( pivotPoint.x() );
	long_buffer[4] = IFF::encode_BigEndian_32_double( pivotPoint.y() );
	long_buffer[5] = IFF::encode_BigEndian_32_double( pivotPoint.z() );
	// buffer[24,25] <-- these should already be 0. If layer nameing is later supported, a string will go here.
	outFile.write( (char*) buffer, chunk_buffer_size() );
}
