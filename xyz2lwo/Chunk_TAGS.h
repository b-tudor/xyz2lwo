#pragma once
#include <fstream>
#include <string>
#include "Chunk.h"
#include "IFF.h"
#include "Vector3D.h"


class Chunk_TAGS : public Chunk
{
public:
	Chunk_TAGS();
	~Chunk_TAGS();

	std::vector<std::string> tag_strings;

public:
	
	unsigned long   chunk_data_size();
	inline size_t chunk_buffer_size() { return chunk_data_size() + 8; };
	inline IFF::uLONG  chunk_data_size_BigE() { return IFF::encode_BigEndian_32_unsigned(chunk_data_size()); }

	void write(std::ofstream &oFile);

	inline int add_tag_string( std::string s ) { tag_strings.push_back(s); return (int) tag_strings.size() - 1; }

};

