#pragma once
#include <fstream>
#include "Chunk.h"
#include "IFF.h"
#include "Vector3D.h"


class Chunk_BBOX : public Chunk
{
public:
	Chunk_BBOX();
	~Chunk_BBOX();

	IFF::uLONG buffer[8]; // LO: x,y,z -> 2,3,4    HI: x,y,z -> 5,6,7

	void write(std::ofstream &oFile);
	
	inline unsigned long  chunk_data_size()   { return 24; }; // 12 bytes per point, 2 points (6 x 32-bit IEEE754 coords)
	inline size_t chunk_buffer_size()   { return 32; }; // 12 bytes per point, 2 points (6 x 32-bit IEEE754 coords) + 8 byte header
	inline IFF::uLONG  chunk_data_size_BigE() { return IFF::encode_BigEndian_32_unsigned( chunk_data_size()); }
	//inline IFF::uLONG chunk_size_BigE() { return IFF::encode_BigEndian_32_unsigned(chunk_size()); }

	void set_HI( Vector3D v );
	void set_LO( Vector3D v );

};

