#pragma once
#ifndef FILE_GENERATOR_3D_H
#define FILE_GENERATOR_3D_H

#include "LWOB_Builder.h"
#include "WavefrontOBJ.h"

#include "Object3D.h"

enum class File_Mode { LWO,  OBJ }; // Lightwave3D; Wavefront	
enum class EOL_Mode  {  LF, CRLF, DEFAULT }; // Line Feed; Carriage Return + Line Feed; 

class FileGenerator3D {

	public:

		
	

	private:

		File_Mode outMode;
		EOL_Mode  eolMode;
		
		LWOB_Builder lwo;
		WavefrontOBJ  obj;


	public:
		
		~FileGenerator3D();
		 FileGenerator3D();
		 FileGenerator3D( File_Mode fM, EOL_Mode eolM );
		
		void setOutputMode_MSDOS() { eolMode = EOL_Mode::CRLF;}
		void setOutputMode_Unix()  { eolMode = EOL_Mode::LF;  }

		// Add a 3D object to the output file
		void add_object( Object3D o, std::string id );

		// Write the output file
		void write( std::string filename );

};

#endif // FILE_GENERATOR_3D_H