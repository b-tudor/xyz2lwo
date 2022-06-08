#pragma once
#include "OBJ_group.h"
#include "Object3D.h"
#include "Vector3D.h"

#include <vector>


// Wavefront OBJ file specs
// Source: https://all3dp.com/1/obj-file-format-3d-printing-cad/
// 
// # Comment - anything on a line that follows a '#' is interpreted as a comment.
// 
// v x y z - vertex command
//   v 1.000000 2.000000 3.000000
// vertices are the points that make up polygons and they are automatically assigned a number (by which they are
// later referred) based on the order in which they appear in the file. The first vertex in a file is vertex 1.
// 
// vn x y z - vertex normal command
//   vn -3.000000 -2.000000 -1.000000
// specifies the vector normal to a surface. The surface with which it is associated is assigned using the f
// command. vn is often omitted in favor of the default normal which is deduced based upon the order the vertices
// appear in the f command, by which the vertices are grouped into a face.
// 
// vt u v [w] - vertex texture command
//   vt 0.00000 0.50000
// When grouped with a vertex in a face (via f command), they inicate the x y coords in a texture map, expressed
// as a fraction of the map's width and height. Accordingly, the values of u and v have to be between 0 and 1, inclusive.
// 
// f v1[/vt1][/vn1] v2[/vt2][/vn2] v3[/vt3][/vn3] ...   - face command
//   f 1 2 3
//   f 4/1 5/3 7/2 9/9
//   f 4/1/3 23/6/3 102/18/43
// Specify the vertices that make up a face/polygon. Triangles will have three vertices listed, rectangles 4, and so on...
// The face command references vertices, vertex normals and vertex texture commands that appeared prior in the file, and 
// each of these are referenced as an implicit number, that is assigned based on the order in which they appear in the 
// file. Each set of vectors/points has its own numeration and they all start with 1.
//
// g name  - the group command
//   g myObject
// Group commands specify sub-object groupings. All face commands that follow will be in the same group. Useful for
// reusing a particular piece of information, such as a material type, for a select part of an object.
// 
// usemtl name - use material command
//   usemtl copper
// Allows you to name a material to be used. All following f commands will use the the same material until another 
// usemtl command appears.
//
// 
// A typical obj file will appear in the following order:
// # List all the vertices (below are vertices 1, 2 & 3)
// v 0.00 0.00 0.00 
// v 1.00 2.00 3.00
// v 4.00 0.00 0.00
// # list all the normals (below is normal 1)
// vn 0.000000 -0.832050 0.554700
// # all the texture commands are listed
// vt 0.0 0.0
// vt 0.5 0.5
// vt 0.5 0.0
// # a group is defined and the material for that group is specified
// g JustATriangle
// usemtl granite
// # list all the f commands
// f 1/1 2/2 3/3


// To generate an OBJ file, instantiate a group object and add vertices and faces to it. Then use the write
// command of the OBJ_Builder and and add it to the OBJ_Builder. 



class WavefrontOBJ
{
	private:

		enum class outMode {MSDOS, UNIX};
	// Data
		std::vector<OBJ_group> groups;
		outMode outputMode;

	// Methods
	public:
		 WavefrontOBJ();
		~WavefrontOBJ();

		inline void setOutputMode_Unix() { outputMode = outMode::UNIX;  }
		inline void setOutputMode_MSDOS(){ outputMode = outMode::MSDOS; }
		void write(std::string filename); // Generate the output file
		void add_object(Object3D o, std::string ID);
		void add_group(OBJ_group);
		
};


