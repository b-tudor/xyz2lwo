#include "FileGenerator3D.h"

FileGenerator3D::~FileGenerator3D(){}
FileGenerator3D:: FileGenerator3D(){
	outMode = File_Mode::LWO;
	eolMode =  EOL_Mode::DEFAULT; // Irrelevant for .lwo files
}
FileGenerator3D:: FileGenerator3D( File_Mode fM, EOL_Mode eM ) {
	outMode = fM;
	eolMode = eM; // Irrelevant if file is of type .lwo
}


void FileGenerator3D::add_object( Object3D o, std::string id ) {

	switch(outMode) {

		case File_Mode::LWO:
			lwo.add_object(o,id);
			return;

		case File_Mode::OBJ:
			obj.add_object(o,id);
			return;
	}
}


void FileGenerator3D::write( std::string filename ) {

	switch(outMode) {

		case File_Mode::LWO:
			lwo.write(filename);
			return;


		case File_Mode::OBJ:
			// First, select desired EOL character sequence: CRLF or LF
			if(      eolMode==EOL_Mode::CRLF ) { obj.setOutputMode_MSDOS(); }
			else if( eolMode==EOL_Mode::LF   ) { obj.setOutputMode_Unix();  }
			// Then write the file
			obj.write(filename);
			return;
	}
}