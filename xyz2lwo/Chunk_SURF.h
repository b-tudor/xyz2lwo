#pragma once
#include <fstream>
#include <string>
#include "Chunk.h"
#include "IFF.h"
#include "Vector3D.h"


class Chunk_SURF : public Chunk
{
public:

	~Chunk_SURF();
	Chunk_SURF() :Chunk_SURF("Default") {};
	Chunk_SURF(std::string id) :Chunk_SURF(id, "") {};
	Chunk_SURF(std::string id, std::string par);
	
	typedef struct _simple_surf_prop {
		IFF::uBYTE CkID[4];
		bool has_prop;
		double value;
		int envelope;

		void set(const char id[4], const double val) { set(id, val, true, 0); }
		void set(const char id[4], const double val, const bool hasProp, const int env) {
			std::memset((void *) CkID, 0, 4);
			std::strncpy( (char*) CkID, (char*) id, 4);
			has_prop = hasProp;
			value = val;
			envelope = env;
		}
	} simple_surf_prop;

	std::string surface_name;
	std::string parent_name;

	bool has_color;
	Vector3D color;
	int color_env;

	/*
	bool has_luminosity;
	double luminosity;
	int luminosity_env;

	bool has_diffuse;
	double diffuse;
	int diffuse_env;

	bool has_specularity;
	double specularity;
	int specularity_env;
	*/

	simple_surf_prop luminosity;
	simple_surf_prop diffuse;
	simple_surf_prop specularity;
	simple_surf_prop reflection;
	


public:
	
	Chunk_SURF & operator=(const Chunk_SURF rhs);

	unsigned long   chunk_data_size();
	inline size_t chunk_buffer_size() { return chunk_data_size() + 8; };
	inline IFF::uLONG  chunk_data_size_BigE() { return IFF::encode_BigEndian_32_unsigned(chunk_data_size()); }

	void write(std::ofstream &oFile);

	void set_surf_name(std::string id) { surface_name = id; }
	void set_parent_surf(std::string p) { parent_name = p; }
	void set_color(int r, int g, int b);
	void set_color(double r, double g, double b);
	void set_color(Vector3D rgb);
	void set_luminosity(double l);
	void set_diffuse(double d);
	void set_specularity(double s);
	void set_reflection(double r);

	//static void encode_surf_1float_subCk(IFF::uBYTE *buffer_start, const char id[4], float val, IFF::uWORD env_flag );
	static void memset_simple_surf_prop(IFF::uBYTE *buffer_start, simple_surf_prop surfProp );
};

