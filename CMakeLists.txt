# CMakeList.txt : CMake project for xyz2lwo

cmake_minimum_required (VERSION 3.7)
project(xyz2lwo)

set(INCLUDE Chemical_Data Quaternion Vector3D xyz2lwo)
include_directories(${INCLUDE})

set(SRC 

	xyz2lwo/Chemical_Data.cpp
	xyz2lwo/Chunk.cpp
	xyz2lwo/Chunk_BBOX.cpp
	xyz2lwo/Chunk_FORM_LWO2.cpp
	xyz2lwo/Chunk_LAYR.cpp
	xyz2lwo/Chunk_PNTS.cpp
	xyz2lwo/Chunk_POLS.cpp
	xyz2lwo/Chunk_PTAG.cpp
	xyz2lwo/Chunk_SURF.cpp
	xyz2lwo/Chunk_TAGS.cpp
	xyz2lwo/IFF.cpp
	xyz2lwo/LWOB_Builder.cpp
	xyz2lwo/OBJ_group.cpp
	xyz2lwo/Object3D.cpp
	xyz2lwo/Quaternion.cpp
	xyz2lwo/Sphere.cpp
	xyz2lwo/Tube.cpp
	xyz2lwo/Vector3D.cpp

	xyz2lwo/main.cpp
)

# Add source to this project's executable.
add_executable(xyz2lwo ${SRC})
target_link_libraries(xyz2lwo PRIVATE m)
