#pragma once
#include <fstream>
#include "Chunk.h"
#include "IFF.h"
#include "Vector3D.h"


class Chunk_PNTS : public Chunk
{
public:
	Chunk_PNTS();
	~Chunk_PNTS();

protected:
	std::vector<Vector3D> points;

	// track the highest & lowest dimensions used in the x, y and z coordinates to construct a bounding box
	double hi[3];
	double lo[3];

public:
	
	inline unsigned long  chunk_data_size() { return (unsigned long) points.size() * 12;     }; // 12 bytes per point (3 x 32-bit IEEE754 floats)
	inline size_t chunk_buffer_size() { return points.size() * 12 + 8; }; // 12 bytes per point (3 x 32-bit IEEE754 floats) + header
	inline IFF::uLONG  chunk_data_size_BigE() { return IFF::encode_BigEndian_32_unsigned(chunk_data_size()); }
	//inline IFF::uLONG chunk_total_size_BigE() { return IFF::encode_BigEndian_32_unsigned(chunk_buffer_size()); }

	void write(std::ofstream &oFile);

	void add_point(Vector3D point);
	inline Vector3D get_HI() { return Vector3D(hi[0], hi[1], hi[2]); };
	inline Vector3D get_LO() { return Vector3D(lo[0], lo[1], lo[2]); };

};

