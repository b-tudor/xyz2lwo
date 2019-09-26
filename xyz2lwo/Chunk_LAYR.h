#pragma once
#include <fstream>
#include "Chunk.h"
#include "IFF.h"
#include "Vector3D.h"


class Chunk_LAYR : public Chunk
{
public:
	Chunk_LAYR();
	~Chunk_LAYR();

	Vector3D pivotPoint;

	static const size_t bufferSize = 26; // enough space for all data + 2 character null layer-name
	IFF::uBYTE buffer[bufferSize] = { 0 };

	void write(std::ofstream &oFile);
	
	inline unsigned long  chunk_data_size() { return 18; } // 16 bytes for layer data + assumed null layer name {"00"}
	inline size_t chunk_buffer_size() { return 26; } // 16 bytes for layer data + assumed null layer name {"00"} + 8 bytes for header
	inline IFF::uLONG  chunk_data_size_BigE() { return IFF::encode_BigEndian_32_unsigned( chunk_data_size()); }
	//inline IFF::uLONG chunk_buffer_size_BigE() { return IFF::encode_BigEndian_32_unsigned(chunk_buffer_size()); }
};

