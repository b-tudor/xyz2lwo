#pragma once
#include "IFF.h"
#include "Chunk_BBOX.h"
#include "Chunk_FORM_LWO2.h"
#include "Chunk_LAYR.h"
#include "Chunk_PNTS.h"
#include "Chunk_POLS.h"
#include "Chunk_PTAG.h"
#include "Chunk_SURF.h"
#include "Chunk_TAGS.h"
#include "Vector3D.h"

#include <vector>


// Chunks should be added in this order:
//	1) Chunk_TAGS
//	2) Chunk_LAYR
//	3) Chunk_PNTS
//	4) Chunk_BBOX
//	5) Chunk_POLS

// Chunk_TAGS: Different surface types will need tag_strings to differentiate them (by a name). Tag_strings just lists the
//             named surfaces/materials in a file.
// Chunk_LAYR: Layer data is not super important, but the output file should include one. It technically assigns objects to
//             layers, (think Photoshop), but that functionality is not implemented as of now.
// Chunk_PNTS: Point data is just a list of points to which the polygon data in a POLS chunk will refer (by index)
// Chunk_BBOX: This chunk lists the bottom-left-front most and top-right-rear most point in the lists of points
// Chunk_POLS: This chunk lists the polygons that are constructed via indexes into the most recent PNTS chunk
// Chunk_PTAG: The PTAG chunk associates tags with polygons. In this case, it identifies which surface is assigned to each
//             polygon. The first number in each pair is a 0-based index into the most recent POLS chunk, and the second is
//             a 0-based index into the TAGS chunk.
// Chunk_SURF: The SURF chunk adopts a name from the TAGS chunk, and assigns surface properties to that name. 

// Point



class LWOB_Builder
{

	// Data
		IFF lwob;
		Chunk_FORM_LWO2 lw_object;

		Chunk_LAYR      layer_data;
		Chunk_TAGS      tag_strings;
		Chunk_PNTS      point_data;
		Chunk_POLS      face_data;
		Chunk_BBOX      bounding_box;

		int point_limit;
		bool new_pnt_chunk;
		
		

	// Methods
	public:
		LWOB_Builder();
		~LWOB_Builder();

		void write(std::string filename);
		void add_points( std::vector<Vector3D> points );
		void add_faces( std::vector<IFF::Face> faces );
		void add_faces( std::vector<IFF::Face> faces, std::string surfaceID ); 
		void add_surface(Chunk_SURF surf );
		int  get_surface_index_by_name(std::string name);
		
		inline void add_tag(std::string tag) { tag_strings.add_tag_string(tag); }
};

// Ok I've generated the points on my sphereO
// Ok I've generated the points on sphereC

// lw_object.add_surface_id( "Atom.O" );
// lw_object.add_surface_id( "Atom.C" );

// lw_object.add_points( sphereO_point_array )
// lw_object.add_faces( sphereO_face_array, "Atom.O" )
// lw_object.add_faces( sphereO_some_other_face_array, "some_other_surface_name" );

// lw_object.add_points( sphereC_point_array );
// lw_object.add_faces( sphereC_face_array, "Atom.C" )


