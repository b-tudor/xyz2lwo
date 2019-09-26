#pragma once
#include <fstream>
#include <vector>
#include "Chunk.h"


class Chunk_FORM_LWO2 : public Chunk
{
public:
	Chunk_FORM_LWO2();
	~Chunk_FORM_LWO2();
	
	inline void add_chunk(Chunk &ck) { chunks.push_back(&ck); };
	
	unsigned long  chunk_data_size();
	inline size_t chunk_buffer_size() { return chunk_data_size() + 8; }; // include 8 byte FORM header
	inline IFF::uLONG  chunk_data_size_BigE() { return IFF::encode_BigEndian_32_unsigned( chunk_data_size()); };
	//inline IFF::uLONG chunk_buffer_size_BigE() { return IFF::encode_BigEndian_32_unsigned(chunk_total_size()); };
	virtual void  write( std::ofstream &outFile );

private: 
	const static size_t bufferSize = 3;
	IFF::uLONG buffer[3];

	std::vector<Chunk *> chunks;
};

