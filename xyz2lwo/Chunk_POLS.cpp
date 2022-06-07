#include "Chunk_POLS.h"
#include <algorithm>
#include <limits.h>

Chunk_POLS::~Chunk_POLS(){}
Chunk_POLS:: Chunk_POLS() {
	ck_ID = IFF::IDTag("POLS");
}



void Chunk_POLS::write(std::ofstream &outFile) {

	
	IFF::uWORD *shortBuffer = (IFF::uWORD *) calloc(chunk_buffer_size(), sizeof(IFF::uBYTE));
	IFF::uLONG *longBuffer  = (IFF::uLONG *) shortBuffer;
	

	longBuffer[0] = ck_ID;
	longBuffer[1] = chunk_data_size_BigE();
	longBuffer[2] = IFF::IDTag("FACE");
	

	int i = 6;
	for_each(faces.begin(), faces.end(), [&i, &shortBuffer](IFF::Face f) {
		shortBuffer[i++] = IFF::encode_BigEndian_16_unsigned( f.vertex_count ); // The number of vertices (These spheres are formed exclusively from triangles)
		for( int j=0; j<f.vertex_count; j++ )
			shortBuffer[i++] = IFF::encode_BigEndian_16_unsigned( f.vertex[j] );
	});

	size_t sz = (size_t)chunk_buffer_size();
	outFile.write( (char*) shortBuffer, (size_t)chunk_buffer_size());
	free(shortBuffer);
}



unsigned long Chunk_POLS::chunk_data_size() {
	// guaranteed two bytes for every poly record (short indicating face count for poly)
	// + four bytes for data identifier ('FACE')
	unsigned long size = (unsigned long) faces.size() * 2 + 4; 
	// 2 bytes for every vertex in every poly record
	for( auto f:faces )
		size += 2 * f.vertex_count;
	return size;
}