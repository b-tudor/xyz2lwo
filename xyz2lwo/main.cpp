#include "args.h"
#include "LWOB_Builder.h"
#include "Chemical_Data.h"  // https://github.com/b-tudor/Chemical_Data
#include "Chunk_SURF.h"
#include "Sphere.h"
#include "Tube.h"

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>

const int tessellation_depth = 3;

bool draw_bonds = false;
const int bond_side_count = 10;
bool is_bond(int i, int j, double dist2);

int main( int argc, char * argv[] )
{
	

	typedef struct _xyzAtom {
		int atomic_number;
		std::string atomic_symbol;
		double x;
		double y;
		double z;
		double radius;
	} xyzAtom;
	int atom_count = 0;
	xyzAtom in;
	std::vector<xyzAtom> atom_list;
	
	

	// Read atoms and coords from a file
	if (argc != 2) {
		std::cout << "Usage: xyz2lwo filename.xyz" << std::endl;
		exit(EXIT_FAILURE);
	}

	
	std::ifstream infile(argv[1]);
	if( ! infile ) 
		return 0;

	infile >> atom_count;
	std::cout << atom_count << std::endl;
	std::string line;
	std::getline(infile, line);
	std::getline(infile, line);


	int ac = atom_count;
	while (ac-- && (infile >> in.atomic_symbol >> in.x >> in.y >> in.z)) {
		in.atomic_number = Chemical_Data::atomic_number(in.atomic_symbol);
		in.radius        = 0.08 * Chemical_Data::atomic_radius_empirical(in.atomic_number);
		atom_list.push_back(in);
	}


		

	LWOB_Builder lwob;
	int count = 0;
	// Add the atoms to the file
	std::for_each(atom_list.begin(), atom_list.end(), [&lwob,&count](xyzAtom a) {
		if (++count % 50) return;
		std::cout << count << std::endl;
		Vector3D r(a.x, a.y, a.z);
		Sphere s(r, a.radius, tessellation_depth);
		lwob.add_points(s.points);
		lwob.add_faces(s.faces, a.atomic_symbol);
	});



	// Append bonds to the file (if requested)
	if( draw_bonds) 
		for (int i = 0; i < atom_count - 1; i++)
			for (int j = i + 1; j < atom_count; j++) {
				double dX = atom_list[i].x - atom_list[j].x;
				double dY = atom_list[i].y - atom_list[j].y;
				double dZ = atom_list[i].z - atom_list[j].z;
				double dist2 = dX * dX + dY * dY + dZ * dZ;

				if (is_bond(atom_list[i].atomic_number, atom_list[j].atomic_number, dist2)) {
					// make a bond between atom i and atom j
					Vector3D I(atom_list[i].x, atom_list[i].y, atom_list[i].z);
					Vector3D J(atom_list[j].x, atom_list[j].y, atom_list[j].z);
					Tube bond(I, J, 0.08, bond_side_count);
					lwob.add_points(bond.points);
					lwob.add_faces(bond.faces, "bond");
					//std::cout << i << " ~~ " << j << std::endl;
				}
			}



	// Add surfaces to the file
	Chunk_SURF surf_C("C");
	surf_C.set_color(50, 61, 52);
	surf_C.set_diffuse(1.0);
	surf_C.set_luminosity(0.0);
	surf_C.set_specularity(1.0);
	surf_C.set_reflection(0.05);
	lwob.add_surface(surf_C);

	Chunk_SURF surf_N("N");
	surf_N.set_color(0.26, 0.46, 0.835);
	surf_N.set_diffuse(1.0);
	surf_N.set_luminosity(0.0);
	surf_N.set_specularity(1.0);
	surf_N.set_reflection(0.05);
	lwob.add_surface(surf_N);
	
	Chunk_SURF surf_H("H");
	surf_H.set_color(250, 250, 255);
	surf_H.set_diffuse(1.0);
	surf_H.set_luminosity(0.0);
	surf_H.set_specularity(1.0);
	surf_H.set_reflection(0.05);
	lwob.add_surface(surf_H);

	Chunk_SURF surf_Ca("Ca");
	surf_Ca.set_color(104, 196, 106);
	surf_Ca.set_diffuse(1.0);
	surf_Ca.set_luminosity(0.0);
	surf_Ca.set_specularity(1.0);
	surf_Ca.set_reflection(0.05);
	lwob.add_surface(surf_Ca);

	Chunk_SURF surf_O("O");
	surf_O.set_color(250, 10, 2);
	surf_O.set_diffuse(1.0);
	surf_O.set_luminosity(0.0);
	surf_O.set_specularity(1.0);
	surf_O.set_reflection(0.05);
	lwob.add_surface(surf_O);



	if (draw_bonds) {
		Chunk_SURF surf_bond("bond");
		surf_bond.set_color(0, 200, 40);
		surf_bond.set_diffuse(1.0);
		surf_bond.set_luminosity(0.0);
		surf_bond.set_specularity(1.0);
		surf_bond.set_reflection(0.05);
		lwob.add_surface(surf_bond);
	}

		


	/*

	lwob.add_points( s.points );
	lwob.add_faces ( s.faces, "Atom.H" );


	Vector3D r2(0.5, 0.0, 0.0);
	Sphere s2(r2, 0.5, 4);
	lwob.add_points(s2.points);
	lwob.add_faces(s2.faces, "Atom.O" );
	*/


	lwob.write("test.lwo");
	
	return 0;
}



bool is_bond(int i, int j, double dist2) {
	
	double len = -1;

	double covalent_radius_i = Chemical_Data::covalent_radius(i);
	double covalent_radius_j = Chemical_Data::covalent_radius(j);
	double bond_length = (covalent_radius_i + covalent_radius_j) * 1.03; // giving a 3% tolerance here
	double bond_len2 = bond_length * bond_length;

	if (dist2 < bond_len2)
		return true;
	else
		return false;

}