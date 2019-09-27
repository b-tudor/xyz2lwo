#include "Chunk_TAGS.h"
#include <algorithm>
#include <cstring>
#include <limits.h>

Chunk_TAGS::~Chunk_TAGS(){}
Chunk_TAGS:: Chunk_TAGS() {
	ck_ID = IFF::IDTag("TAGS");
}



void Chunk_TAGS::write(std::ofstream &outFile) {
	
	IFF::uBYTE *buffer = (IFF::uBYTE *) calloc(chunk_buffer_size(), sizeof(IFF::uBYTE));
	IFF::uLONG *longBuffer = (IFF::uLONG *) buffer;
	
	longBuffer[0] = ck_ID;
	longBuffer[1] = chunk_data_size_BigE();

	int i = 8;
	for_each( tag_strings.begin(), tag_strings.end(), [&i,buffer](std::string s) {
		strcpy((char *)&(buffer[i]), s.c_str());
		size_t len = s.size();
		i += (int)( len + ((len%2) ? 1 : 2));
	});

	outFile.write( (char*) buffer, (size_t) chunk_buffer_size() );
	free(buffer);
}



unsigned long Chunk_TAGS::chunk_data_size() {

	int sz = 0;
	for_each(tag_strings.begin(), tag_strings.end(), [&sz](std::string s) {
		int length = (int) s.size();
		sz += (length % 2)  ?  (length + 1):(length + 2);
	});

	return sz;
};