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


class Chunk_PTAG: public Chunk
{
public:

	Chunk_PTAG();
	~Chunk_PTAG();

protected:

	std::vector<int> surface_associations;

public:
	
	// Each assignment in SURF is 4 bytes: a uSHORT (2 bytes) giving the index of the polygon being referenced (an index into the most
	// recent POLS chunk), followed by a 2nd uSHORT giving the surface assignment for this polygon, as an index into the TAGS chunk.
	inline unsigned long chunk_data_size()    { return (unsigned long) surface_associations.size() * 4 + 4;  }; // 4 bytes per assignment + 'SURF'
	inline IFF::uLONG  chunk_data_size_BigE() { return IFF::encode_BigEndian_32_unsigned(chunk_data_size()); }
	inline size_t chunk_buffer_size()  { return surface_associations.size() * 4 + 12; }; // 4 bytes per assignment + header ('PTAGxxxxSURF')
	
	void write(std::ofstream &oFile);

	inline void add_surface( int i ) { surface_associations.push_back(i); };
	bool assign_surface(unsigned int polyID, int surfID );

};