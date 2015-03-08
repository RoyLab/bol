#pragma once
#include <list>
#include <Fade_2D.h>
#include "MPMesh.h"
#include "BinaryTree.h"
#include <set>

namespace CSG
{
	using OpenMesh::Vec3d;
	struct ISectTriangle;
	struct ISVertexInfo;

	typedef std::list<ISectTriangle>::iterator ISectTriItr;
	typedef std::list<Vec3d>::iterator			VertexItr;
	typedef std::list<Vec3d>::const_iterator	cVertexItr;
	typedef std::list<ISVertexInfo>::iterator	ISectVItr;

	enum VertexPos 
	{
		NONE =   -1, 
		EDGE_0 = 0x01, 
		EDGE_1 = 0x02, 
		EDGE_2 = 0x04, 
		VER_0  = 0x08, 
		VER_1  = 0x10, 
		VER_2  = 0x20, 
		INNER  = 0x00,
	};

	struct ISVertexInfo
	{
		VertexItr pos;
		VertexPos type;

		Relation *relation;

		ISVertexInfo(unsigned i):
			type(NONE)
		{
			relation = new Relation[i];
			memset(relation, 0, i*sizeof(Relation));
		}

		~ISVertexInfo()	{delete [] relation;	}

	};

	struct ISCutSeg
	{
		ISectVItr		start, end;
		ISectTriItr		oppoTriangle;
	};

	struct ISCutSegInfo
	{
		std::list<ISCutSeg> seg;	
		int					meshID;
	};


	struct ISectTriangle
	{
		int					meshID;
		MPMesh::FaceHandle	face;

		int mainIndex;
		std::set<int> relationTestId;

		std::list<ISVertexInfo> vertices;
		std::list<ISCutSegInfo>	segs;
		
		GEOM_FADE2D::Fade_2D		*dtZone;

		ISectTriangle():
			mainIndex(-1), meshID(-1),
			dtZone(nullptr)
		{}

		~ISectTriangle()	 {if (dtZone) delete dtZone;	}
	};
	
	struct ISectZone
	{
		std::list<Vec3d>				vertices; // include original and new vertices 
		std::list<ISectTriangle>		triangles;
	};
} // namespace CSG

