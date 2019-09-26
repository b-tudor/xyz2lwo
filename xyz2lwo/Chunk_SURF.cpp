#include "Chunk_SURF.h"
#include <algorithm>
#include <limits.h>

Chunk_SURF::~Chunk_SURF() {};
Chunk_SURF::Chunk_SURF(std::string id, std::string par) {

	ck_ID = IFF::IDTag("SURF");

	surface_name = id;
	parent_name = par;

	has_color = false;
	color.set(0, 0, 0);
	color_env = 0;

	luminosity.set  ( "LUMI", 0.0, false, 0);
	diffuse.set     ( "DIFF", 0.0, false, 0);
	specularity.set ( "SPEC", 0.0, false, 0);
	reflection.set  ( "REFL", 0.0, false, 0);
}



void Chunk_SURF::write(std::ofstream &outFile) {
	// IFF::uBYTE bf[1000];
	// std::memset(bf, '\8', 1000);
	IFF::uBYTE *buffer_start = (IFF::uBYTE *) calloc(chunk_buffer_size(), sizeof(IFF::uBYTE));
	IFF::uBYTE *buffer = buffer_start;
	IFF::uWORD *wordBuffer = nullptr; 
	IFF::uLONG *longBuffer = (IFF::uLONG *) buffer;

	longBuffer[0] = ck_ID;
	longBuffer[1] = chunk_data_size_BigE();
	buffer += 8;
	
	strcpy( (char *) buffer, surface_name.c_str());
	size_t len = surface_name.size();
	buffer += len + ((len%2) ? 1 : 2);

	if (parent_name.size() > 0) {
		strcpy( (char *) buffer, parent_name.c_str());
		len = parent_name.size();
		buffer += len + ((len % 2) ? 1 : 2);
	} else 
		buffer += 2;

	if (has_color) {
		strncpy((char *) buffer, "COLR", 4); 
		buffer += 4;
		wordBuffer = (IFF::uWORD *) buffer;
		wordBuffer[0] = IFF::encode_BigEndian_16_unsigned(14);
		longBuffer = (IFF::uLONG *)( wordBuffer + 1);
		longBuffer[0] = IFF::encode_BigEndian_32_double( color.x());
		longBuffer[1] = IFF::encode_BigEndian_32_double( color.y());
		longBuffer[2] = IFF::encode_BigEndian_32_double( color.z());
		buffer += 14;
		wordBuffer = (IFF::uWORD *) buffer;
		wordBuffer[0] = IFF::encode_BigEndian_16_unsigned(color_env); 
		buffer += 2;
	}

	if (diffuse.has_prop) {
		memset_simple_surf_prop(buffer, diffuse );
		buffer += 12;
	}

	if (specularity.has_prop) {
		memset_simple_surf_prop(buffer, specularity );
		buffer += 12;
	}

	if (luminosity.has_prop) {
		memset_simple_surf_prop(buffer, luminosity );
		buffer += 12;
	}

	if (reflection.has_prop) {
		memset_simple_surf_prop(buffer, reflection);
		buffer += 12; 
	}
	
	outFile.write( (char*) buffer_start, (size_t) chunk_buffer_size() );
}



unsigned long Chunk_SURF::chunk_data_size() {

	unsigned int surfID_sz = (unsigned int) surface_name.size();
	unsigned int  parID_sz = (unsigned int) parent_name.size();
	
	if (surfID_sz > 0) 
		surfID_sz += (surfID_sz % 2) ? 1 : 2;
	else {
		// Surf ID is required, so if it doesn't we make one
		surfID_sz = 8;
		surface_name = "Default";
	}


	if (parID_sz > 0)
		parID_sz += (parID_sz % 2) ? 1 : 2;
	else
		parID_sz = 2;

	unsigned long ckSize = surfID_sz + parID_sz;

	if (has_color)
		ckSize += 20;
	
	if (luminosity.has_prop)
		ckSize += 12;
	
	if (diffuse.has_prop)
		ckSize += 12;
	
	if (specularity.has_prop)
		ckSize += 12;

	if (reflection.has_prop)
		ckSize += 12;

	return ckSize;
}



void Chunk_SURF::set_color(int r, int g, int b) {

	if (r <   0) r =   0;
	if (r > 255) r = 255;
	if (g <   0) g =   0;
	if (g > 255) g = 255;
	if (b <   0) b =   0;
	if (b > 255) b = 255;

	const double max = 255;
	set_color( r/max, g/max, b/max);
}
void Chunk_SURF::set_color( double r, double g, double b ) {
	Vector3D color(r, g, b);
	set_color(color);
}
void Chunk_SURF::set_color(Vector3D rgb) {
	if(  rgb.x()>=0  &&  rgb.y()>=0  &&  rgb.z()>=0  &&  rgb.x()<=1  &&  rgb.y()<=1  &&  rgb.z()<=1 ) {
		has_color = true;
		color = rgb;
	}
}
void Chunk_SURF::set_luminosity(double l) {
	luminosity.has_prop = true;
	luminosity.value = l;
}
void Chunk_SURF::set_diffuse(double d) {
	diffuse.has_prop = true;
	diffuse.value = d;
}
void Chunk_SURF::set_specularity(double s) {
	specularity.has_prop = true;
	specularity.value = s;
}
void Chunk_SURF::set_reflection(double r) {
	reflection.has_prop = true;
	reflection.value = r;
}



void Chunk_SURF::memset_simple_surf_prop(IFF::uBYTE *buffer_start, simple_surf_prop surfProp ) {

	IFF::uWORD *size = (IFF::uWORD *)(buffer_start + 4);
	IFF::uLONG *value = (IFF::uLONG *)(buffer_start + 6);
	IFF::uWORD *flag = (IFF::uWORD *)(buffer_start + 10);

	strncpy((char*)buffer_start, (char*) surfProp.CkID, 4);
	*size = IFF::encode_BigEndian_16_unsigned(6);
	*value = IFF::encode_BigEndian_32_float( (float) surfProp.value);
	*flag = IFF::encode_BigEndian_16_unsigned( (int) surfProp.envelope);
}



Chunk_SURF & Chunk_SURF::operator=(const Chunk_SURF rhs) {

	surface_name = rhs.surface_name;
	parent_name  = rhs.parent_name;

	has_color = rhs.has_color;
	color     = rhs.color;

	diffuse.has_prop = rhs.diffuse.has_prop;
	diffuse.value    = rhs.diffuse.value;
	diffuse.envelope = rhs.diffuse.envelope;

	luminosity.has_prop = rhs.luminosity.has_prop;
	luminosity.value    = rhs.luminosity.value;
	luminosity.envelope = rhs.luminosity.envelope;

	specularity.has_prop = rhs.specularity.has_prop;
	specularity.value    = rhs.specularity.value;
	specularity.envelope = rhs.specularity.envelope;

	reflection.has_prop = rhs.reflection.has_prop;
	reflection.value    = rhs.reflection.value;
	reflection.envelope = rhs.reflection.envelope;

	return (*this);
}