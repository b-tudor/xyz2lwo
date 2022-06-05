#include "Chemical_Data.h"
Chemical_Data::~Chemical_Data() {}
Chemical_Data::Chemical_Data() {}



int Chemical_Data::atomic_number(std::string chemical_symbol) {

	// Special cases for CO2 and C2H2 models commonly used in mpmc
	if (chemical_symbol == "H2G") 
		return 1;
	
	if (chemical_symbol == "C2G")
		return 6;
	
	if (chemical_symbol == "COG")
		return 6;

	if (chemical_symbol == "COE")
		return 8;

	if (chemical_symbol == "HB" )
		return 1;

	if (chemical_symbol == "CB")
		return 6;

	int S = 0, s = 0;

	// First letter & size (> 0) check
	if (chemical_symbol.size() > 0)
		S = (int)(0xdf & (chemical_symbol.c_str()[0]));  // Masked in order to be agnostic to capital/lowercase letters
	else return 0;

	// Second letter
	if (chemical_symbol.size() > 1)
		s = (int)(0xdf & (chemical_symbol.c_str()[1]));  // Masked in order to be agnostic to capital/lowercase letters

	// Size check (cannot be longer than 2 characters
	if (chemical_symbol.size() > 2)
		return 0;


	switch (S) {
	case 67:
		if (!s)	     return 6;    // C
		if (s == 65) return 20;   // Ca
		if (s == 68) return 48;   // Cd
		if (s == 69) return 58;   // Ce
		if (s == 70) return 98;   // Cf
		if (s == 75) return 17;   // Cl
		if (s == 76) return 96;   // Cm
		if (s == 77) return 112;  // Cn
		if (s == 78) return 27;   // Co
		if (s == 81) return 24;   // Cr
		if (s == 82) return 55;   // Cs
		if (s == 85) return 29;   // Cu
		return 0;

	case 72:
		if (!s)      return 1;    // H
		if (s == 69) return 2;    // He
		if (s == 70) return 72;   // Hf
		if (s == 71) return 80;   // Hg
		if (s == 79) return 67;   // Ho
		if (s == 83) return 108;  // Hs
		return 0;

	case 78:
		if (!s) return 7;         // N
		if (s == 65) return 11;   // Na
		if (s == 66) return 41;   // Nb
		if (s == 68) return 60;   // Nd
		if (s == 69) return 10;   // Ne
		if (s == 72) return 113;  // Nh
		if (s == 73) return 28;   // Ni
		if (s == 79) return 102;  // No
		if (s == 80) return 93;   // Np
		return 0;

	case 79:
		if (!s)      return 8;    // O
		if (s == 71) return 118;  // Og
		if (s == 83) return 76;   // Os
		return 0;

	case 83:
		if (!s) return 16;        // S
		if (s == 66) return 51;   // Sb
		if (s == 67) return 21;   // Sc
		if (s == 69) return 34;   // Se
		if (s == 71) return 106;  // Sg
		if (s == 73) return 14;   // Si
		if (s == 77) return 62;   // Sm
		if (s == 78) return 50;   // Sn
		if (s == 82) return 38;   // Sr
		return 0;

	case 80:
		if (!s) return 15;        // P
		if (s == 65) return 91;   // Pa
		if (s == 66) return 82;   // Pb
		if (s == 68) return 46;   // Pd
		if (s == 77) return 61;   // Pm
		if (s == 79) return 84;   // Po
		if (s == 82) return 59;   // Pr
		if (s == 84) return 78;   // Pt
		if (s == 85) return 94;   // Pu
		return 0;

	case 84:
		if (s == 65) return 73;   // Ta
		if (s == 66) return 65;   // Tb
		if (s == 67) return 43;   // Tc
		if (s == 69) return 52;   // Te
		if (s == 72) return 90;   // Th
		if (s == 73) return 22;   // Ti
		if (s == 76) return 81;   // Tl
		if (s == 77) return 69;   // Tm
		if (s == 83) return 117;  // Ts
		return 0;

	case 82:
		if (s == 65) return 88;   // Ra
		if (s == 66) return 37;   // Rb
		if (s == 69) return 75;   // Re
		if (s == 70) return 104;  // Rf
		if (s == 71) return 111;  // Rg
		if (s == 72) return 45;   // Rh
		if (s == 78) return 86;   // Rn
		if (s == 85) return 44;   // Ru
		return 0;

	case 65:
		if (s == 67) return 89;   // Ac
		if (s == 71) return 47;   // Ag
		if (s == 76) return 13;   // Al
		if (s == 77) return 95;   // Am
		if (s == 82) return 18;   // Ar
		if (s == 83) return 33;   // As
		if (s == 84) return 85;   // At
		if (s == 85) return 79;   // Au
		return 0;

	case 66:
		if (!s) return 5;         // B
		if (s == 65) return 56;   // Ba
		if (s == 69) return 4;    // Be
		if (s == 72) return 107;  // Bh
		if (s == 73) return 83;   // Bi
		if (s == 75) return 97;   // Bk
		if (s == 82) return 35;   // Br
		return 0;

	case 77:
		if (s == 67) return 115;  // Mc
		if (s == 68) return 101;  // Md
		if (s == 71) return 12;   // Mg
		if (s == 78) return 25;   // Mn
		if (s == 79) return 42;   // Mo
		if (s == 84) return 109;  // Mt
		return 0;

	case 70:
		if (!s) return 9;         // F
		if (s == 69) return 26;   // Fe
		if (s == 76) return 114;  // Fl
		if (s == 77) return 100;  // Fm
		if (s == 82) return 87;   // Fr
		return 0;

	case 76:
		if (s == 65) return 57;   // La
		if (s == 73) return 3;    // Li
		if (s == 82) return 103;  // Lr
		if (s == 85) return 71;   // Lu
		if (s == 86) return 116;  // Lv
		return 0;

	case 68:
		if (s == 66) return 105;  // Db
		if (s == 83) return 110;  // Ds
		if (s == 89) return 66;   // Dy
		return 0;

	case 69:
		if (s == 82) return 68;   // Er
		if (s == 83) return 99;   // Es
		if (s == 85) return 63;   // Eu
		return 0;

	case 71:
		if (s == 65) return 31;   // Ga
		if (s == 68) return 64;   // Gd
		if (s == 69) return 32;   // Ge
		return 0;

	case 73:
		if (!s) return 53;        // I
		if (s == 78) return 49;   // In
		if (s == 82) return 77;   // Ir
		return 0;

	case 75:
		if (!s) return 19;        // K
		if (s == 82) return 36;   // Kr
		return 0;

	case 89:
		if (!s) return 39;        // Y
		if (s == 66) return 70;   // Yb
		return 0;

	case 90:
		if (s == 78) return 30;   // Zn
		if (s == 82) return 40;   // Zr
		return 0;

	case 85:
		if (!s) return 92;        // U
		return 0;

	case 86:
		if (!s) return 23;        // V
		return 0;

	case 87:
		if (!s) return 74;        // W
		return 0;

	case 88:
		if (s == 69) return 54;   // Xe
		return 0;

	default:
		return 0;
	}
};


double Chemical_Data::atomic_radius_empirical(int atomic_number) {
	// Source: https://develop.open.wolframcloud.com/app/ (accessed 3/14/2019)
	// Dataset[EntityValue[Entity["Element", "Radon"], {EntityProperty["Element", "AtomicRadius"], EntityProperty["Element", "CovalentRadius"], EntityProperty["Element", "VanDerWaalsRadius"]}, "PropertyAssociation"]]
	const double atomic_radius[119] = {
		0,     // Padding
		0.25,  // H
		1.20,  // He
		1.45,  // Li
		1.05,  // Be
		0.85,  // B
		0.70,  // C
		0.65,  // N
		0.60,  // O
		0.50,  // F
		1.60,  // Ne
		1.80,  // Na
		1.50,  // Mg
		1.25,  // Al
		1.10,  // Si
		1.00,  // P
		1.00,  // S
		1.00,  // Cl
		0.71,  // Ar
		2.20,  // K
		1.80,  // Ca
		1.60,  // Sc
		1.40,  // Ti
		1.35,  // V
		1.66,  // Cr
		1.40,  // Mn
		1.40,  // Fe
		1.40,  // Co
		1.35,  // Ni
		1.35,  // Cu
		1.35,  // Zn
		1.30,  // Ga
		1.25,  // Ge
		1.15,  // As
		1.15,  // Se
		1.15,  // Br
		0,     // Kr - No data
		2.35,  // Rb
		2.00,  // Sr
		1.80,  // Y
		1.55,  // Zr
		1.45,  // Nb
		1.45,  // Mo
		1.35,  // Tc
		1.30,  // Ru
		1.35,  // Rh
		1.40,  // Pd
		1.60,  // Ag
		1.55,  // Cd
		1.55,  // In
		1.45,  // Sn
		1.45,  // Sb
		1.40,  // Te
		1.40,  // I
		0,     // Xe - No data
		2.60,  // Cs
		2.15,  // Ba
		1.95,  // La
		1.85,  // Ce
		1.85,  // Pr
		1.85,  // Nd
		1.85,  // Pm
		1.85,  // Sm
		1.85,  // Eu
		1.80,  // Gd
		1.75,  // Tb
		1.75,  // Dy
		1.75,  // Ho
		1.75,  // Er
		1.75,  // Tm
		1.75,  // Yb
		1.75,  // Lu
		1.55,  // Hf
		1.45,  // Ta
		1.35,  // W
		1.35,  // Re
		1.30,  // Os
		1.35,  // Ir
		1.35,  // Pt
		1.35,  // Au
		1.50,  // Hg
		1.90,  // Tl
		1.80,  // Pb
		1.60,  // Bi
		1.90,  // Po
		0,     // At - No data
		0,     // Rn - No data
		0,     // Fr - No data
		2.15,  // Ra
		1.95,  // Ac
		1.80,  // Th
		1.80,  // Pa
		1.75,  // U
		1.75,  // Np
		1.75,  // Pu
		1.75,  // Am
		0,     // Cm - No data
		0,     // Bk - No data
		0,     // Cf - No data
		0,     // Es - No data 
		0,     // Fm - No data
		0,     // Md - No data
		0,     // No - No data
		0,     // Lr - No data
		0,     // Rf - No data
		0,     // Db - No data
		0,     // Sg - No data
		0,     // Bh - No data
		0,     // Hs - No data
		0,     // Mt - No data
		0,     // Ds - No data
		0,     // Rg - No data
		0,     // Cn - No data
		0,     // Nh - No data
		0,     // Fl - No data
		0,     // Mc - No data
		0,     // Lv - No data
		0,     // Ts - No data
		0      // Og - No data
	};

	return  (atomic_number >= 1 && atomic_number <= 118) ? atomic_radius[atomic_number] : -1.0;
}


double Chemical_Data::covalent_radius(int atomic_number) {
	// Source: https://develop.open.wolframcloud.com/app/ (accessed 3/14/2019)
	// Dataset[EntityValue[Entity["Element", "Radon"], {EntityProperty["Element", "AtomicRadius"], EntityProperty["Element", "CovalentRadius"], EntityProperty["Element", "VanDerWaalsRadius"]}, "PropertyAssociation"]]

	const double covalent_radius[119] = {
		0,     // Padding
		0.31,  // H
		0.28,  // He
		1.28,  // Li
		0.96,  // Be
		0.84,  // B
		0.76,  // C
		0.71,  // N
		0.66,  // O
		0.57,  // F
		0.58,  // Ne
		1.66,  // Na
		1.41,  // Mg
		1.21,  // Al
		1.11,  // Si
		1.07,  // P
		1.05,  // S
		1.02,  // Cl
		1.06,  // Ar
		2.03,  // K
		1.76,  // Ca
		1.70,  // Sc
		1.60,  // Ti
		1.53,  // V
		1.39,  // Cr
		1.39,  // Mn
		1.32,  // Fe
		1.26,  // Co
		1.24,  // Ni
		1.32,  // Cu
		1.22,  // Zn
		1.22,  // Ga
		1.20,  // Ge
		1.19,  // As
		1.20,  // Se
		1.20,  // Br
		1.16,  // Kr
		2.20,  // Rb
		1.95,  // Sr
		1.90,  // Y
		1.75,  // Zr
		1.64,  // Nb
		1.54,  // Mo
		1.47,  // Tc
		1.46,  // Ru
		1.42,  // Rh
		1.39,  // Pd
		1.45,  // Ag
		1.44,  // Cd
		1.42,  // In
		1.39,  // Sn
		1.39,  // Sb
		1.38,  // Te
		1.39,  // I
		1.40,  // Xe
		2.44,  // Cs
		2.15,  // Ba
		2.07,  // La
		2.04,  // Ce
		2.03,  // Pr
		2.01,  // Nd
		1.99,  // Pm
		1.98,  // Sm
		1.98,  // Eu
		1.96,  // Gd
		1.94,  // Tb
		1.92,  // Dy
		1.92,  // Ho
		1.89,  // Er
		1.90,  // Tm
		1.87,  // Yb
		1.87,  // Lu
		1.75,  // Hf
		1.70,  // Ta
		1.62,  // W
		1.51,  // Re
		1.44,  // Os
		1.41,  // Ir
		1.36,  // Pt
		1.36,  // Au
		1.32,  // Hg
		1.45,  // Tl
		1.46,  // Pb
		1.48,  // Bi
		1.40,  // Po
		1.50,  // At
		1.50,  // Rn
		2.60,  // Fr
		2.21,  // Ra
		2.15,  // Ac
		2.06,  // Th
		2.00,  // Pa
		1.96,  // U
		1.90,  // Np
		1.87,  // Pu
		1.80,  // Am
		1.69,  // Cm
		0,     // Bk
		0,     // Cf
		0,     // Es
		0,     // Fm
		0,     // Md
		0,     // No
		0,     // Lr
		0,     // Rf
		0,     // Db
		0,     // Sg
		0,     // Bh
		0,     // Hs
		0,     // Mt
		0,     // Ds
		0,     // Rg
		0,     // Cn
		0,     // Nh
		0,     // Fl
		0,     // Mc
		0,     // Lv
		0,     // Ts
		0      // Og
	};

	return  (atomic_number >= 1 && atomic_number <= 118) ? covalent_radius[atomic_number] : -1.0;
}


double Chemical_Data::van_der_Waals_radius(int atomic_number) {
	// Source: https://develop.open.wolframcloud.com/app/ (accessed 3/14/2019)
	// Dataset[EntityValue[Entity["Element", "Radon"], {EntityProperty["Element", "AtomicRadius"], EntityProperty["Element", "CovalentRadius"], EntityProperty["Element", "VanDerWaalsRadius"]}, "PropertyAssociation"]]

	const double vdW_radius[119] = {
		0,     // Padding
		1.20,  // H
		1.40,  // He
		1.82,  // Li
		0,     // Be
		0,     // B
		1.70,  // C
		1.55,  // N
		1.52,  // O
		1.47,  // F
		1.54,  // Ne
		2.27,  // Na
		1.73,  // Mg
		0,     // Al
		2.10,  // Si
		1.80,  // P
		1.80,  // S
		1.75,  // Cl
		1.88,  // Ar
		2.75,  // K
		0,     // Ca
		0,     // Sc
		0,     // Ti
		0,     // V
		0,     // Cr
		0,     // Mn
		0,     // Fe
		0,     // Co
		1.63,  // Ni
		1.40,  // Cu
		1.39,  // Zn
		1.87,  // Ga
		0,     // Ge
		1.85,  // As
		1.90,  // Se
		1.85,  // Br
		2.02,  // Kr
		0,     // Rb
		0,     // Sr
		0,     // Y
		0,     // Zr
		0,     // Nb
		0,     // Mo
		0,     // Tc
		0,     // Ru
		0,     // Rh
		1.63,  // Pd
		1.72,  // Ag
		1.58,  // Cd
		1.93,  // In
		2.17,  // Sn
		0,     // Sb
		2.06,  // Te
		1.98,  // I
		2.16,  // Xe
		0,     // Cs
		0,     // Ba
		0,     // La
		0,     // Ce
		0,     // Pr
		0,     // Nd
		0,     // Pm
		0,     // Sm
		0,     // Eu
		0,     // Gd
		0,     // Tb
		0,     // Dy
		0,     // Ho
		0,     // Er
		0,     // Tm
		0,     // Yb
		0,     // Lu
		0,     // Hf
		0,     // Ta
		0,     // W
		0,     // Re
		0,     // Os
		0,     // Ir
		1.75,  // Pt
		1.66,  // Au
		1.55,  // Hg
		1.96,  // Tl
		2.02,  // Pb
		0,     // Bi
		0,     // Po
		0,     // At
		0,     // Rn
		0,     // Fr
		0,     // Ra
		0,     // Ac
		0,     // Th
		0,     // Pa
		1.86,  // U
		0,     // Np
		0,     // Pu
		0,     // Am
		0,     // Cm
		0,     // Bk
		0,     // Cf
		0,     // Es
		0,     // Fm
		0,     // Md
		0,     // No
		0,     // Lr
		0,     // Rf
		0,     // Db
		0,     // Sg
		0,     // Bh
		0,     // Hs
		0,     // Mt
		0,     // Ds
		0,     // Rg
		0,     // Cn
		0,     // Nh
		0,     // Fl
		0,     // Mc
		0,     // Lv
		0,     // Ts
		0      // Og
	};

	return  (atomic_number >= 1 && atomic_number <= 118) ? vdW_radius[atomic_number] : -1.0;
}


bool Chemical_Data::is_bonded_covalent2( int i, int j, double dist2, double tolerance ) {
	
	double len = -1;
	double covalent_radius_i = Chemical_Data::covalent_radius(i);
	double covalent_radius_j = Chemical_Data::covalent_radius(j);
	double bond_length = (covalent_radius_i + covalent_radius_j) * tolerance;
	double bond_len2 = bond_length * bond_length;
	
	return (dist2 < bond_len2);
}
