#pragma once
#include <fstream>
#include "IFF.h"

// Chunks are often in the following format
//
// +------------------------------------------------------------------------------------------
// | Chunk ID, 4 bytes (e.g. POLS)
// +------------------------------------------------------------------------------------------
// | Chunk size, 4 bytes (size, in bytes, of ALL  data that follows (to the end of the chunk
// | this value should be returned by: chunk_data_size(), but chunk_data_size_BigE() should 
// | used for writing this value in a file, to ensure it is encoded correctly.
// +------------------------------------------------------------------------------------------
// | Data ID, 4 bytes (e.g. FACE)
// +------------------------------------------------------------------------------------------
// | DATA
// |
// | The length of this section is the number of bytes listed in Chunk size section, minus
// | the 4 bytes used to ID the data.
// |
// |  .
// |  .
// |  .
// |
// +------------------------------------------------------------------------------------------


// The size of the entire chunk (used, e.g. to allocate a buffer to hold the entire data structure, tags
// headers, and all, should be returned by the function: chunk_total_size()

class Chunk
{
public:
	Chunk();
	virtual ~Chunk() = 0;
	
	virtual void write(std::ofstream &outFile )   = 0;
	virtual unsigned long chunk_data_size()       = 0;
	virtual IFF::uLONG    chunk_data_size_BigE()  = 0;
	virtual size_t        chunk_buffer_size()     = 0;
	//virtual IFF::uLONG    chunk_size_BigE()     = 0;

protected:
	IFF::uLONG ck_ID;
};
