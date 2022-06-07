#pragma once

#include "Object3D.h"

#include <string>
#include <vector>

class Chunk;

class IFF
{

	// Types
	public:

		enum class EndianType { UNINITIALIZED = -1, LITTLE = 0, BIG = 1 };
		typedef uint8_t   uBYTE;  //  8-bits unsigned (must be an 8 bit type)
		typedef uint16_t  uWORD;  // 16-bits unsigned (must be a 16 bit type)
		typedef uint32_t  uLONG;  // 32-bits unsigned (must be a 32 bit type)
		

		typedef struct _Face {
			
			public:
				unsigned short vertex_count;
				unsigned short vertex[4];     // indices of points in most recent PNTS chunk

				// Conversion constructor from Object3D::Face to IFF:Face
				_Face(Object3D::Face f) {
					vertex_count = f.vertex_count;
					vertex[0] = f.vertex[0];
					vertex[1] = f.vertex[1];
					vertex[2] = f.vertex[2];
					vertex[3] = f.vertex[3];
				} 
		} Face;


	// Data
	protected:
		static bool initialized;
		static EndianType endian;
		std::vector<Chunk *> chunks;



	// Methods
	public:
		IFF();
		~IFF();

		inline void add_chunk(Chunk & ck) { chunks.push_back( &ck ); };
		void write(std::string filename);
		



	// Static Methods
		static bool initialize();
		static bool system_is_big_endian();
		static bool system_is_little_endian();

		static uLONG IDTag(const char *id);

		inline static uWORD order_bits_iff16(const uWORD bits);
		inline static uLONG order_bits_iff32(const uLONG bits);

		static uWORD encode_BigEndian_16(const short shorty);
		static uWORD encode_BigEndian_16_unsigned(const unsigned short shorty);
		
		static uLONG encode_BigEndian_32_long    ( const long l           );
		static uLONG encode_BigEndian_32_unsigned( const unsigned long ul );
		static uLONG encode_BigEndian_32_float   ( const float ieee754    );
		static uLONG encode_BigEndian_32_double  ( const double dbl       );

};

