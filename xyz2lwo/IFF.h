#pragma once
#include <string>
#include <vector>

class Chunk;

class IFF
{

	// Types
	public:
		enum endian_type { UNINITIALIZED = -1, LITTLE = 0, BIG = 1 };
		typedef unsigned char  uBYTE;  //  8-bits unsigned
		typedef unsigned short uWORD;  // 16-bits unsigned 
		typedef unsigned long  uLONG;  // 32-bits unsigned

		typedef struct _face {
			unsigned short vertex_count;
			unsigned short vertex[4];            // indices of points in most recent PNTS chunk
		} Face;



	// Data
	protected:
		static bool initialized;
		static endian_type endian;
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

