/*    Brant Tudor (2019)
 *    C++ Class to provide chemical data and constants for various elements.
 */


#pragma once
#ifndef CHEMICAL_DATA_H
#define CHEMICAL_DATA_H

#include <string>


class Chemical_Data
{

public:

	Chemical_Data();
	~Chemical_Data();

	bool is_bonded(int i, int j, double dist2); // Determines if two atoms are bonded, based on their distance
										  // and the covalent radii of each atom.

	// Get an atomic number from a chemical (string) symbol
	static int atomic_number(std::string chemical_symbol);

	// Get van der Waals radius from atomic number
	static double van_der_Waals_radius(int atomic_number);

	// Get empirically measured atomic radius from atomic number
	static double atomic_radius_empirical(int atomic_number);

	// Get covalent radius from atomic number
	static double covalent_radius(int atomic_number);
};

#endif