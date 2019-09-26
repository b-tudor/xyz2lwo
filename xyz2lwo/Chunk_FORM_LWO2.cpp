#include <algorithm>
#include "Chunk_FORM_LWO2.h"
#include "IFF.h"




Chunk_FORM_LWO2::~Chunk_FORM_LWO2() {}
Chunk_FORM_LWO2:: Chunk_FORM_LWO2() {
	buffer[0] = ck_ID = IFF::IDTag("FORM");
	buffer[1] = 0; // FORM size
	buffer[2] = IFF::IDTag("LWO2");
}




void Chunk_FORM_LWO2::write( std::ofstream & outFile ) {

	buffer[1] = chunk_data_size_BigE();
	outFile.write((char*) & buffer, bufferSize * sizeof(IFF::uLONG) );
	for_each(chunks.begin(), chunks.end(), [&outFile](Chunk *chunk) {
		chunk->write(outFile);
	});
}




unsigned long Chunk_FORM_LWO2::chunk_data_size() {

	unsigned long size = 4; // Starting with 4 to include the data type ID Tag: "LWO2"
	for_each(chunks.begin(), chunks.end(), [&size](Chunk * ck) {
		size += (unsigned long) ck->chunk_buffer_size(); 
	});

	return size; 
}