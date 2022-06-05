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

	// Determines if two atoms are bonded, based on their distance and the covalent radius of each atom.
	// is_bonded_covalent2() receives distance^2 to avoid call to sqrt(). tolerancePct is a percentage (+/-)
	// by which to multiply the computed atom-atom bond length in order to allow for a little leeway in 
	// detecting bonds (a separation distance <= to the computed bond length will return TRUE for bond length
	// queries).
	const double DEFAULT_TOLERANCE = 1.03;
	static inline bool is_bonded_covalent (int i, int j, double dist)                      { return is_bonded_covalent2( i, j, dist*dist, DEFAULT_TOLERANCE); }
	static inline bool is_bonded_covalent (int i, int j, double dist, double tolerancePct) { return is_bonded_covalent2( i, j, dist*dist, tolerancePct);      }
	static inline bool is_bonded_covalent2(int i, int j, double dist2)                     { return is_bonded_covalent2( i, j,     dist2, DEFAULT_TOLERANCE); }
	static        bool is_bonded_covalent2(int i, int j, double dist2, double tolerancePct);
										  
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