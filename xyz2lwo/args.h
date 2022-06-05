#pragma once
#ifndef ARGS_H
#define	ARGS_H

#include <cstring>
#include <iostream>
#include <sstream>


enum class File_Mode    { LWO, OBJ };
enum class Newline_Mode { MSDOS, UNIX, DEFAULT };

typedef struct _parameters{
    std::string          inputFile;
    std::string         outputFile;
    bool                draw_bonds = false;                 // Draw ball-and-stick style bonds between atoms?
    int         tessellation_depth = 3;                     // Depth by which to tesselate spheres representing atoms
    File_Mode          output_mode = File_Mode::LWO;        // Default output file type is LWO
    Newline_Mode      newline_mode = Newline_Mode::DEFAULT; // Line-endings to use in text-files. 

} params;
 


char * stripPath( char * full_path ) {

    // Select either MS Windows or Unix file separator
    #ifndef _WIN32
    const char file_separator = '/';
    #else
    const char file_separator = '\\';
    #endif


    char *simple_name = full_path;
    char *i = full_path;

    // Skip to the last separator in the filename
    while( *i != '\0' ) {
        i++;
        if( (*i) == file_separator )
            simple_name = i+1;
    }

    return simple_name;
}



bool filename_ends_w_obj(std::string fname) {
    
    const char *filename = fname.c_str();
    
    size_t  startIdx = fname.length() - 4;
    if (startIdx <= 0)
        return false;

    const char CAPS_MASK = (char) 32;

    char dot  = filename[startIdx + 0];
    char ext1 = filename[startIdx + 1] | CAPS_MASK;
    char ext2 = filename[startIdx + 2] | CAPS_MASK;
    char ext3 = filename[startIdx + 3] | CAPS_MASK; 

    if(  dot=='.' && ext1=='o' && ext2=='b' && ext3=='j'  ) 
        return true;

    return false;

}
    


void displayUsageAndDie( char* progname, params& p ) {
    
    char *progName_wo_path = stripPath( progname );
    std::cout << "\n";
    std::cout << progName_wo_path << " takes an .XYZ molecular geometry file as input, and outputs a high quality geometry file\n";
    std::cout << "suitable for generating photorealistic images in ray tracing software. LWO files are for use with\n";
    std::cout << "Lightwave 3D, but the .obj file type is suitable for use in a wide variety of renderers (Blender,\n";
    std::cout << "Maya, etc.).\n\n";

    std::cout << "Usage:\n\n";

    std::cout << "  " << progName_wo_path << " <input file> [options]\n\n";

    std::cout << "Options:\n\n";

    std::cout << "  -o FILENAME     Output file name.\n";
    std::cout << "  -O FILENAME        NOTE: If an output file name is not specified, the output file will have the\n";
    std::cout << "                      same name as the input file but the extension will be replaced with \".lwo\".\n";
    std::cout << "                     NOTE: If FILENAME has an.obj extension, the output file produced\n";
    std::cout << "                      will be a Wavefront (.obj) file. IF THE CAPITAL -O OPTION IS USED, the output\n";
    std::cout << "                      file will be a Wavefront file, regardless of the file name. \n";
    std::cout << "  -b              Use this option to draw bonds.\n";
    std::cout << "  -t DEPTH        Levels of tesselation to use in approximating spherical geometry via polygons.\n";
    std::cout << "                     A tesselation level of 0 will result in each atom appearing as a diamond comprised\n"; 
    std::cout << "                     of 6 triangular polygons. Each tesselation level will multiply the number of faces\n";
    std::cout << "                     by 4, such that level 6 will generate 24,576 polygons per atom.\n";
    std::cout << "  -l -w           When writing OBJ files, " << progName_wo_path << " will attempt to preserve the newline\n";
    std::cout << "                     character codes used by the input file. To force Unix/Linux style end-of-line\n"; 
    std::cout << "                     control codes (LF), use the -l option. To force MS-DOS/Windows style EOL encoding\n";
    std::cout << "                     (CR/LF), use the -w option. These options only matter when the output format is a\n";
    std::cout << "                     Wavefront (.obj) file.\n\n";
    
    std::cout << "Sample commands:\n\n";

    std::cout << "  " << progName_wo_path << " H2O.xyz\n";
    std::cout << "  " << progName_wo_path << " H2O.xyz -t 3 -o water.lwo\n";
    std::cout << "  " << progName_wo_path << " benzene.xyz -O C6H6_OBJ_file -b -l\n\n";
    exit(0);
}



void processArgs( int argc, char * argv[], params& p ) {

    bool    input_name_already_set = false; // Check if user fails to set the input name (or attempts to set it more than once)
    bool   output_name_already_set = false; // Check if user attempts to set multiple output file names
    
	if( argc >= 2 ) {

        int n=1; // argument in argument vector (argv) that we are currently examining.

        while( n<argc ) {
            
            std::istringstream issArg( argv[n] ); // for convenient type conversion from strings
            
            // Is user requesting that bonds be drawn? 
            if( !strncmp( issArg.str().c_str(), "-b", 3 )) {
                n++;
                p.draw_bonds = true;
            }

            // USER SPECIFIED OUTPUT FILE?
            else if(!strncmp(issArg.str().c_str(), "-o", 3) || !strncmp(issArg.str().c_str(), "-O", 3)) {
                if (output_name_already_set) {
                    std::cout << "ERROR: Attempted to set multiple output names\n";
                    displayUsageAndDie(argv[0], p);
                } else {
                    output_name_already_set = true;

                    char oO_option_used = issArg.str().c_str()[1]; // Store the option used (o vs O) for later reference

                    n++; // Advance to the next command line argument

                    if (n >= argc) {
                        // If there are no more arguments...
                        std::cout << "ERROR: Output file option indicated, but filename not provided.\n";
                        displayUsageAndDie(argv[0], p);
                    }
                    std::istringstream issOptionValue(argv[n]);
                    issOptionValue >> p.outputFile;
                    if (!issOptionValue) {
                        std::cout << "ERROR: Unable to parse output filename.\n";
                        displayUsageAndDie(argv[0], p);
                    }

                    // Determine the output format 
                    if (oO_option_used == 'O')                    // If user used the -O option (vs -o) then the output mode is .obj
                        p.output_mode = File_Mode::OBJ;
                    else if (filename_ends_w_obj(p.outputFile))   // Or... if user specified a file name ending in .obj, output mode is .obj
                        p.output_mode = File_Mode::OBJ;
                    else                                          // Otherwise, the output mode is Lightwave3D
                        p.output_mode = File_Mode::LWO;

                    n++; // This argument has been consumed... then next loop iteration should examine the next command line argument
                }
            }
            
            
            // USER SPECIFIED TESSELATION DEPTH?
            else if( !strncmp( issArg.str().c_str(), "-t", 3 )) {
                
                n++;
                if (n >= argc) {
                    std::cout << "ERROR: Tesselation option indicated, but value not provided.\n";
                    displayUsageAndDie(argv[0], p);
                }
                std::istringstream issValueToken( argv[n] );
				issValueToken >> p.tessellation_depth;
                if (!issValueToken) {
                    std::cout << "ERROR: Unable to parse tesselation depth value.\n";
                    displayUsageAndDie(argv[0], p);
                }
				if( p.tessellation_depth < 0  || p.tessellation_depth >6 ) {
                    std::cout << "ERROR: Tesselation depth must be between 0 and 6, inclusive.\n";
                    std::cout << "Exiting..." << std::endl;
                    exit(0);
                }

                n++;
            }

            // Is user requesting MS-DOS/Windows style output on text files (.obj files)?
            else if( !strncmp( issArg.str().c_str(), "-w", 3 )) {
                n++;
                if( p.newline_mode == Newline_Mode::UNIX ) {
                    std::cerr << "ERROR: Conflicting newline modes requested (-l/-w)\n";
                    std::cout << "Exiting..." << std::endl;
                    exit(0);
                }
                p.newline_mode = Newline_Mode::MSDOS;
            }

            // Is user requesting Unix/Linux/MacOS style output on text files (.obj files)?
            else if (!strncmp(issArg.str().c_str(), "-l", 3)) {
                n++;
                if( p.newline_mode == Newline_Mode::MSDOS ) {
                    std::cerr << "ERROR: Conflicting newline modes requested (-l/-w)\n";
                    std::cout << "Exiting..." << std::endl;
                    exit(0);
                }
                p.newline_mode = Newline_Mode::UNIX;
            }

            else {
                
                if( input_name_already_set) 
                    std::cout << "ERROR: Unrecognized option: " << argv[n] << std::endl;
                else {
                    issArg >> p.inputFile;
                    if (!issArg) displayUsageAndDie(argv[0], p); // Couldn't read input file name?
                    input_name_already_set = true;
                }

                n++;
            }
            
        } // end while
        
	} // end if
	else displayUsageAndDie( argv[0], p );

    


    if (!input_name_already_set) {
        std::cout << "ERROR: Input file was not specified.\n";
        displayUsageAndDie(argv[0], p);
    }

    if ( !output_name_already_set ) {
        char outFile[1000];
        strcpy( outFile, p.inputFile.c_str() );
        size_t len = strlen(outFile);
        if( len >= 5 ) {
            size_t extension_idx = len - 4;
            if( ! strncmp(&outFile[extension_idx], ".xyz", 4)) {
                strcpy(&outFile[extension_idx], ".lwo");
                output_name_already_set = true;
            }
        }

        if (!output_name_already_set)
            strcpy(outFile, "xyz.lwo");

        p.outputFile = outFile;
    }
}

#endif	/* ARGS_H */

