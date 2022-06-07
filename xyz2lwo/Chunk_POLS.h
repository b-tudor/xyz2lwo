#pragma once
#include <fstream>
#include "Chunk.h"
#include "IFF.h"
#include "Vector3D.h"

// EVENTUALLY, this class will need to be amended to handle index numbers N, such that
//    1024  <=  N  <=  16,777,216


// FACE sub-chunks (of the POLS chunk) describe polygons. The face of the polygon is the side for which the points are 
// would appear to be listed in a clockwise direction. The polygons are described as a 2-byte number quantifying the 
// number of points that make up the face. The 6 highest bits of this number act as flags in CURV-type polygons, so the 
// total number of points making up a polygon are effectively limited to 1023 (although setting the first byte to 0xFF, 
// indicates that the next three bytes comprise the index. Making the number of points in a polygon 16.8M. Objects that 
// need more than 16.8M points can be stored across several PNTS & POLS chunks. 


class Chunk_POLS : public Chunk
{
public:

	Chunk_POLS();
	~Chunk_POLS();

protected:

	std::vector<IFF::Face> faces;

public:
	
	// Each triangle in FACE is 8 bytes: a uSHORT (2 bytes) stating how many vertices the next polygon contains (3), 
	// followed by that many uSHORTs (which are indices into the previous PNTS chunk).
	unsigned long chunk_data_size(); // Size of the data contained in the chunk
	inline size_t chunk_buffer_size()  { return chunk_data_size() + 8; }; 
	inline IFF::uLONG  chunk_data_size_BigE() { return IFF::encode_BigEndian_32_unsigned(chunk_data_size()); }
	//inline IFF::uLONG chunk_buffer_size_BigE() { return IFF::encode_BigEndian_32_unsigned(chunk_buffer_size()); }

	void write(std::ofstream &oFile);

	void add_face(IFF::Face face) { faces.push_back(face); };

};