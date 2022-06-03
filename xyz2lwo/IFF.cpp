#include "IFF.h"
#include "Chunk.h"

#include <algorithm>
#include <cstring>
#include <iostream>
#include <fstream>


//  CONSTRUCTORS / DESTRUCTORS  ///////////////////////////////////////////////////////////////////////////////////////

IFF::~IFF() {}
IFF:: IFF() {
	initialize();
}





//  STATIC METHODS & VARIABLES  ///////////////////////////////////////////////////////////////////////////////////////

IFF::EndianType IFF::endian = EndianType::UNINITIALIZED;



bool IFF::initialize() {

	bool ok = true;

	if (endian == EndianType::UNINITIALIZED) {

		if (sizeof(uBYTE) != 1) {
			std::cerr << "Incompatible UBYTE width: Type definition for UBYTE (default \"unsigned char\") must evaluate to a 1 byte data type." << std::endl;
			ok = false;
		}
		if (sizeof(uWORD) != 2) {
			std::cerr << "Incompatible WORD width: Type definition for WORD (default \"short\") must evaluate to an 2 byte data type." << std::endl;
			ok = false;
		}
		if (sizeof(uLONG) != 4) {
			std::cerr << "Incompatible LONG width: Type definition for LONG (default \"long\") must evaluate to an 4 byte data type." << std::endl;
			ok = false;
		}


		// Determine if system is Big Endian or Little Endian

		uLONG endian_test = 1145258561; // same as "ABCD" or "DCBA", depending on byte ordering
		char *test = (char *)&endian_test;

		if (!strncmp("ABCD", test, 4))
			endian = EndianType::LITTLE;
		else if (!strncmp("DCBA", test, 4))
			endian = EndianType::BIG;
		else {
			std::cerr << "Incompatible BYTE order:\nThis machine appears to utilize an unfamiliar byte ordering (It does not appear to be the common Big Endian or Little Endian ordering)." << std::endl;
			ok = false;
		}

	}

	if (!ok)
		throw "incompatible system error";

	return true;
}


bool IFF::system_is_big_endian() {

	if (endian == EndianType::UNINITIALIZED)
		initialize();

	return endian == EndianType::BIG;
}
bool IFF::system_is_little_endian() {

	if (endian == EndianType::UNINITIALIZED)
		initialize();

	return endian == EndianType::LITTLE;
}


IFF::uLONG IFF::IDTag( const char *id ) {
	
	char ID[4] = { 0 }; // buffer pre-populated with 0's
	uLONG bits = 0;

	// Copy id characters into buffer until EOL. Trailing characters are left as 0
	for (int i = 0; i < 4; i++)
		if( ! (ID[i] = id[i]))
			break;
	
	memcpy(  (void*) &bits,  (void*) ID,  (size_t) 4 );

	return bits;
}

IFF::uWORD IFF::order_bits_iff16( const uWORD bits ) {
	return system_is_big_endian()   ?   bits  :  ((bits & 0xff) << 8) | ((bits & 0xff00) >> 8);
}
IFF::uLONG IFF::order_bits_iff32( const uLONG bits ) {
	return system_is_big_endian()   ?   bits  :  ((bits & 0xff) << 24) | ((bits & 0xff00) << 8) | ((bits & 0xff0000) >> 8) | ((bits & 0xff000000) >> 24);
}


IFF::uWORD IFF::encode_BigEndian_16( const short shorty          ) {
	uWORD bits = 0;
	memcpy( (void*) &bits, (void*) &shorty, sizeof(bits));
	return order_bits_iff16(bits);
}
IFF::uWORD IFF::encode_BigEndian_16_unsigned( const unsigned short shorty ) {
	uWORD bits = 0;
	memcpy((void*)&bits, (void*)&shorty, sizeof(bits));
	return order_bits_iff16(bits);
}


IFF::uLONG IFF::encode_BigEndian_32_long    ( const long l           ) {
	uLONG bits = 0;
	memcpy((void*)&bits, (void*)&l, sizeof(bits));
	return order_bits_iff32(bits);
}
IFF::uLONG IFF::encode_BigEndian_32_unsigned( const unsigned long ul ) {
	uLONG bits = 0;
	memcpy((void*)&bits, (void*)&ul, sizeof(bits));
	return order_bits_iff32(bits);
}
IFF::uLONG IFF::encode_BigEndian_32_float   ( const float ieee754    ) {
	uLONG bits = 0;
	memcpy((void*)&bits, (void*)&ieee754, sizeof(bits));
	return order_bits_iff32(bits);
}
IFF::uLONG IFF::encode_BigEndian_32_double  ( const double d         ) {
	float ieee754 = (float) d;
	uLONG bits = 0;
	memcpy((void*)&bits, (void*)&ieee754, sizeof(bits));
	return order_bits_iff32(bits);
}






//  PUBLIC METHODS  ///////////////////////////////////////////////////////////////////////////////////////////////////

void IFF::write(std::string filename) {

	int nSections = (int) chunks.size();
	if (nSections == 0)
		return; // Nothing to write

	// open the file
	std::ofstream outFile(filename, std::ios::binary | std::ios::out);

	// write the data sections
	for_each(chunks.begin(), chunks.end(), [&outFile](Chunk * ck) {
		ck->write(outFile);
	});
	

	// close file
	outFile.close();
}