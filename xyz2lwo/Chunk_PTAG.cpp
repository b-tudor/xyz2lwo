#include "Chunk_PTAG.h"
#include <algorithm>
#include <limits.h>

Chunk_PTAG::~Chunk_PTAG(){}
Chunk_PTAG:: Chunk_PTAG() {
	ck_ID = IFF::IDTag("PTAG");
}



void Chunk_PTAG::write(std::ofstream &outFile) {

	size_t sz = chunk_buffer_size();
	IFF::uWORD *shortBuffer = (IFF::uWORD *) calloc( sz, sizeof(IFF::uBYTE));
	IFF::uLONG *longBuffer  = (IFF::uLONG *) shortBuffer;
	

	longBuffer[0] = ck_ID;
	longBuffer[1] = chunk_data_size_BigE();
	longBuffer[2] = IFF::IDTag("SURF");
	

	unsigned int sbIdx = 6;
	for( unsigned int i=0; i<surface_associations.size(); i++ ) {
		shortBuffer[sbIdx++] = IFF::encode_BigEndian_16(i);
		shortBuffer[sbIdx++] = IFF::encode_BigEndian_16(surface_associations[i]);
	}

	outFile.write( (char*) shortBuffer, sz );
	free(shortBuffer);
}



bool Chunk_PTAG::assign_surface(unsigned int polyID, int surfID ) {
	 
	if(  (polyID<0)  ||  (polyID >= surface_associations.size())  )
		return false;

	surface_associations[polyID] = surfID;
	return true;
}