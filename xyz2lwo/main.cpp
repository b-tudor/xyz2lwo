#include "args.h"
#include "Chemical_Data.h"  // https://github.com/b-tudor/Chemical_Data
#include "Chunk_SURF.h"
#include "FileGenerator3D.h"
#include "LWOB_Builder.h"
#include "WavefrontOBJ.h"
#include "Sphere.h"
#include "Tube.h"

#include <algorithm>
#include <iomanip>
#include <iostream>
#include <fstream>
#include <sstream>


// Data structure used to describe atoms
typedef struct _xyzAtom {
	int atomic_number = 0;
	std::string atomic_symbol;
	double x = 0;
	double y = 0;
	double z = 0;
	double radius = 0;
} xyzAtom;

const int bond_side_count = 10;           // Number of sides in tube objects that form ball-and-stick bonds

EOL_Mode determineEOLstyle(std::string filename);




int main( int argc, char * argv[] )
{
	// Get filename and user settings from the command line ////////////////////////////////////////////
	params in;
	processArgs(argc, argv, in); 
	// Create aliases for param data for ease of reference:
	const bool&              bonds = in.draw_bonds;         // Are we drawings ball-and-stick style sticks?
	const bool&          tessDepth = in.tessellation_depth; // Recursive levels of triangular sphere approximation
	const File_Mode        outMode = in.output_mode;
	const EOL_Mode         eolMode = in.newline_mode;       // Will text files mark EOL with LF or CR/LF
	const std::string& outFilename = in.outputFile;         // output file name
	

	std::cout << "Output  mode: " << ((in. output_mode == File_Mode::LWO       ) ? "LWO\n" : "OBJ\n");
	std::cout << "Newline mode: " << ((in.newline_mode == EOL_Mode::DEFAULT) ? "DEFAULT\n" : ((in.newline_mode == EOL_Mode::CRLF) ? "MS-DOS\n" : "UNIX\n" ));


	if (in.newline_mode == EOL_Mode::DEFAULT) {
		// Discover NewLine encoding of the input file
		in.newline_mode = EOL_Mode::LF;
	}



	// Read the atomic coordinates from the input file //////////////////////////////////////////////////
	std::ifstream infile(in.inputFile);
	if (!infile) {
		std::cout << "Could not open input file: " << in.inputFile << "\nExiting...\n";
		return 0;
	}

	int atom_count = 0;
	std::vector<xyzAtom> atom_list;

	infile >> atom_count;
	std::string line;
	std::getline( infile, line );
	std::getline( infile, line );

	xyzAtom in_data;
	int ac = atom_count;
	while (ac-- && (infile >> in_data.atomic_symbol >> in_data.x >> in_data.y >> in_data.z)) {
		in_data.atomic_number = Chemical_Data::atomic_number(in_data.atomic_symbol);
		in_data.radius        = Chemical_Data::atomic_radius_empirical(in_data.atomic_number);
		atom_list.push_back(in_data);
	}
	

	// Declare/Initialize the object that will create our output file. If output is a .lwo file, eol doesn't matter.
	// If output is an .obj file, then we use whatever the user explicitly set. If the user didn't set anything (i.e.
	// the EOL mode is set to DEFAULT), then we attempt to preserve whatever style was used in the input file. 
	FileGenerator3D outFile( outMode, (outMode==File_Mode::OBJ && eolMode==EOL_Mode::DEFAULT) ? determineEOLstyle(in.inputFile) : eolMode );

	

	int count = 0;
	// Add the atoms to the file
	
	for( auto atom : atom_list ) {
		std::cout << "\rProcessing atoms: " << std::fixed << std::setprecision(1) << std::setw(5) << ++count * 100.0 / (double)atom_count << "%";
		Vector3D r(atom.x, atom.y, atom.z);

		int depth = in.tessellation_depth;
		if (atom.radius > 1.00)
			depth += 1;
		if (in.draw_bonds && (atom.atomic_number > 1))
			atom.radius *= 0.8;
		if (atom.atomic_number == 54 || atom.atomic_number == 36 || atom.atomic_number == 10 || atom.atomic_number == 18) {
			depth = 2;
			atom.radius = 0.25;
		}
		Sphere atomicSphere(r, atom.radius, depth);
		
		// Store points based on the desired output type

		// Add atomic geometry to the output file
		outFile.add_object( atomicSphere, atom.atomic_symbol);
	}

	std::cout << "\rProcessing atoms: done.   \n";


	// Append bonds to the file (if requested)
	if (in.draw_bonds) {
		for (int i = 0; i < atom_count - 1; i++) {
			std::cout << "\rProcessing bonds: " << std::fixed << std::setprecision(1) << std::setw(5) << +i * 100.0 / (double)atom_count << "%";
			for (int j = i + 1; j < atom_count; j++) {
				double dX = atom_list[i].x - atom_list[j].x;
				double dY = atom_list[i].y - atom_list[j].y;
				double dZ = atom_list[i].z - atom_list[j].z;
				double dist2 = dX * dX + dY * dY + dZ * dZ;

				if (Chemical_Data::is_bonded_covalent2(atom_list[i].atomic_number, atom_list[j].atomic_number, dist2)) {
					// make atom bond between atom i and atom j
					Vector3D I(atom_list[i].x, atom_list[i].y, atom_list[i].z);
					Vector3D J(atom_list[j].x, atom_list[j].y, atom_list[j].z);
					Tube bond(I, J, 0.08, bond_side_count);

					// Add bond geometry to the appropriate data structure (as determined by output type)
					outFile.add_object(bond, "bond" );
				} 
			} // for j
		} // for i
		std::cout << "\rProcessing bonds: done.   \n";
	}
/*
	if (out_mode == File_Mode::LWO) {

		// Add surfaces to the file
		Chunk_SURF surf_C("C");
		surf_C.set_color(50, 61, 52);
		surf_C.set_diffuse(1.0);
		surf_C.set_luminosity(0.0);
		surf_C.set_specularity(1.0);
		surf_C.set_reflection(0.05);
		lwob.add_surface(surf_C);

		Chunk_SURF surf_N("N");
		surf_N.set_color(8, 132, 210);
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

		Chunk_SURF surf_Cu("Cu");
		surf_Cu.set_color(189, 103, 30);
		surf_Cu.set_diffuse(1.0);
		surf_Cu.set_luminosity(0.0);
		surf_Cu.set_specularity(1.0);
		surf_Cu.set_reflection(0.05);
		lwob.add_surface(surf_Cu);

		Chunk_SURF surf_F("F");
		surf_F.set_color(58, 226, 97);
		surf_F.set_diffuse(1.0);
		surf_F.set_luminosity(0.0);
		surf_F.set_specularity(1.0);
		surf_F.set_reflection(0.05);
		lwob.add_surface(surf_F);

		Chunk_SURF surf_Ge("Ge");
		surf_Ge.set_color(58, 226, 97);
		surf_Ge.set_diffuse(1.0);
		surf_Ge.set_luminosity(0.0);
		surf_Ge.set_specularity(1.0);
		surf_Ge.set_reflection(0.05);
		lwob.add_surface(surf_Ge);

		Chunk_SURF surf_Ti("Ti");
		surf_Ti.set_color(58, 226, 97);
		surf_Ti.set_diffuse(1.0);
		surf_Ti.set_luminosity(0.0);
		surf_Ti.set_specularity(1.0);
		surf_Ti.set_reflection(0.05);
		lwob.add_surface(surf_Ti);

		Chunk_SURF surf_Si("Si");
		surf_Si.set_color(58, 226, 97);
		surf_Si.set_diffuse(1.0);
		surf_Si.set_luminosity(0.0);
		surf_Si.set_specularity(1.0);
		surf_Si.set_reflection(0.05);
		lwob.add_surface(surf_Si);

		Chunk_SURF surf_Kr("Kr");
		surf_Kr.set_color(58, 226, 97);
		surf_Kr.set_diffuse(1.0);
		surf_Kr.set_luminosity(0.0);
		surf_Kr.set_specularity(1.0);
		surf_Kr.set_reflection(0.05);
		lwob.add_surface(surf_Kr);

		Chunk_SURF surf_Xe("Xe");
		surf_Xe.set_color(58, 226, 97);
		surf_Xe.set_diffuse(1.0);
		surf_Xe.set_luminosity(0.0);
		surf_Xe.set_specularity(1.0);
		surf_Xe.set_reflection(0.05);
		lwob.add_surface(surf_Xe);

		if (in.draw_bonds) {
			Chunk_SURF surf_bond("bond");
			surf_bond.set_color(0, 200, 40);
			surf_bond.set_diffuse(1.0);
			surf_bond.set_luminosity(0.0);
			surf_bond.set_specularity(1.0);
			surf_bond.set_reflection(0.05);
			lwob.add_surface(surf_bond);
		}
	}
*/
	outFile.write(in.outputFile);
	
	return EXIT_SUCCESS;
}





EOL_Mode determineEOLstyle(std::string filename) {
	return EOL_Mode::CRLF;
}