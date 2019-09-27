#pragma once
#ifndef ARGS_H
#define	ARGS_H

#include <cstring>
#include <iostream>
#include <sstream>
using namespace std;


typedef struct _parameters{
        double	temperature;             
        double  k;
        int	    totalSteps;
        int     equilibrationSteps;
        int     P;
        
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
    
    

void displayUsageAndDie( char* progname, params *p ) {
    
    char *progName_wo_path = stripPath( progname );
    cout << "Usage:" << endl;
    cout << "\t" << progName_wo_path << " <Kelvin_Temperature> [options]" << endl;
    cout << "Options:" << endl;
    cout << "\t-e  EQUIL_STEPS  Number of MC steps to take before system is considered equilibrated." << endl;
    cout << "\t                 (Default is " << p->equilibrationSteps << ")" << endl;
    cout << "\t-k  SPRING_CONST Spring constant value for external (Harmonic) potential. (Default" << endl;
    cout << "\t                 is " << p->k << ")" << endl;
    cout << "\t-p  BEADS        Number of beads used to simulate each atom with quantum effects." << endl;
    cout << "\t                 (Default is " << p->P << ")" << endl;
    cout << "\t-t  TOTALSTEPS   Total number of simulation steps to perform. (Default is " << p->totalSteps << ")" << endl;


	exit(0);
}



void processArgs( int argc, char * argv[], params *p)
{
    using namespace std;
    
	
	if( argc >= 2 ) {
        // TEMPERATURE
        istringstream issArg1( argv[1] );
        issArg1 >> p->temperature;
        if(!issArg1) displayUsageAndDie(argv[0], p );
                
        int n=2;
        while( n<argc ) {
            
            // NATOM 
            istringstream issOptionToken( argv[n] );
            
            // Number of beads in ring polymer quantum particle approximation 
            if( !strncmp( issOptionToken.str().c_str(), "-e", 5 )) {
                
                n++;
                if( n>=argc ) displayUsageAndDie( argv[0], p );
                istringstream issValueToken( argv[n] );
				issValueToken >> p->equilibrationSteps;
                if(!issValueToken) displayUsageAndDie(argv[0], p);
				if( p->equilibrationSteps < 0 ) {
                    cout << "Number of equilibration steps must be non-negative." << endl;
                    cout << "Exiting..." << endl;
                    exit(0);
                }
                n++;
            }

            
            // SIGMA VALUE
            else if( !strncmp( issOptionToken.str().c_str(), "-k", 5 )) {
                
                n++;
                if( n>=argc ) displayUsageAndDie( argv[0], p );
                istringstream issValueToken( argv[n] );
                issValueToken >> p->k;
                if(!issValueToken) displayUsageAndDie(argv[0], p);
                n++;
            }
            
            // Number of beads in ring polymer quantum particle approximation 
            else if( !strncmp( issOptionToken.str().c_str(), "-p", 5 )) {
                
                n++;
                if( n>=argc ) displayUsageAndDie( argv[0], p );
                istringstream issValueToken( argv[n] );
				issValueToken >> p->P;
                if(!issValueToken) displayUsageAndDie(argv[0], p);
				if( p->P <= 0 ) {
                    cout << "There must be at least 1 bead for each quantum-effect particle." << endl;
                    cout << "Exiting..." << endl;
                    exit(0);
                }
                n++;
            }
                        
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

            else 
            {
                cout << "Skipping unrecognized option: " << argv[n] << endl;
                n++;
            }
            
        } // end while
        
        
	} // end if
	else displayUsageAndDie( argv[0], p );
}

#endif	/* ARGS_H */

