#pragma once
#ifndef ARGS_H
#define	ARGS_H

#include <cstring>
#include <iostream>
#include <sstream>

const char LWO_FILE = (char) 0;
const char OBJ_FILE = (char) 1;

typedef struct _parameters{
    std::string inputFile;
    std::string outputFile;
    bool draw_bonds = false;           // Draw ball-and-stick type bonds between atoms?
    int tessellation_depth = 3;        // Depth by which to tesselate spheres representing atoms
    char output_file_type  = LWO_FILE; // Default output file type is LWO
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



bool filename_ends_w_OBJ(std::string fname) {
    
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

    std::cout << "Usage:\n";
    std::cout << "\t" << progName_wo_path << " <input file> [options]\n";
    std::cout << "Options:\n";
    std::cout << "\t-b               Use this option to draw bonds.\n";
    std::cout << "\t-t  DEPTH        Levels of tesselation to use in approximating spherical geometry\n";
    std::cout << "\t                 via polygons. A higher number will result in smoother spheres, but\n";
    std::cout << "\t                 accordingly, each sphere will be comprised of an exponentially\n";
    std::cout << "\t                 increasing number of triangles.\n";
    std::cout << "\t-o  FILENAME     Output file name.\n";
    std::cout << "\t                 NOTE: If FILENAME has an.obj extension, the output file produced will\n";
    std::cout << "\t                 be a Wavefront OBJ file." << std::endl;
    
    exit(0);
}



void processArgs( int argc, char * argv[], params& p )
{

    bool  input_name_already_set = false;
    bool output_name_already_set = false;
    
	if( argc >= 2 ) {

        int n=1;
        while( n<argc ) {
            
            std::istringstream issArg( argv[n] );
            
            // Is user requesting that bonds be drawn? 
            if( !strncmp( issArg.str().c_str(), "-b", 3 )) {
                n++;
                p.draw_bonds = true;
            }

            // USER SPECIFIED OUTPUT FILE?
            else if( !strncmp( issArg.str().c_str(), "-o", 3 )) {
                if (output_name_already_set) {
                    std::cout << "ERROR: Output file name already set.\n";
                    displayUsageAndDie(argv[0], p);
                } else {
                    output_name_already_set = true;
                    n++;
                    if (n >= argc) {
                        std::cout << "ERROR: Output file option indicated, but filename not provided.\n";
                        displayUsageAndDie(argv[0], p);
                    }
                    std::istringstream issOptionValue(argv[n]);
                    issOptionValue >> p.outputFile;
                    if (!issOptionValue) {
                        std::cout << "ERROR: Unable to parse output filename.\n";
                        displayUsageAndDie(argv[0], p);
                    }
                    if (filename_ends_w_OBJ(p.outputFile))
                        p.output_file_type = OBJ_FILE;
                    n++;
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
				if( p.tessellation_depth <= 0  || p.tessellation_depth >6 ) {
                    std::cout << "ERROR: Tesselation depth must be between 1 and 6, inclusive.\n";
                    std::cout << "Exiting..." << std::endl;
                    exit(0);
                }
                n++;
            }
            

            /*
            // TOTAL STEPS
            else if( !strncmp( issOptionToken.str().c_str(), "-t", 5 )) {
                
                n++;
                if( n>=argc ) displayUsageAndDie( argv[0], p );
                istringstream issValueToken( argv[n] );
                issValueToken >> p->totalSteps;
                if(!issValueToken) displayUsageAndDie(argv[0], p);
                if( p->totalSteps <= 0 ) {
                    cout << "Total number of steps must be positive." << endl;
                    cout << "Exiting..." << endl;
                    exit(0);
                }
                n++;
            }
            */
            else {
                
                if( input_name_already_set) 
                    std::cout << "ERROR: Unrecognized option: " << argv[n] << std::endl;
                else {
                    issArg >> p.inputFile;
                    if (!issArg) displayUsageAndDie(argv[0], p);
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

