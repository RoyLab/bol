#pragma once
#include "AABB.h"
#include <vector>

namespace GS
{
    class BaseMesh;
}


namespace CSG
{
    typedef unsigned uint;

    struct TriangleInfo
    {
        uint VertexIndex[3];
        GS::double3 Normal;
        TriangleInfo(const int* index, const double3& normal)
        {
            VertexIndex[0] = index[0];
            VertexIndex[1] = index[1];
            VertexIndex[2] = index[2];
            Normal = normal;
        }
    };

    struct CSGMesh
    {
        CSGMesh(GS::BaseMesh* pMesh);
        ~CSGMesh(void);

        const std::vector<double3>& Vertex() const {return mVertex;}
        const std::vector<TriangleInfo>& Triangle() const {return mTriangle;}

        std::vector<double3> mVertex;
        std::vector<TriangleInfo> mTriangle;
        AABB mAABB;
        int ID;
    };

    GS::BaseMesh* ConverteToBaseMesh(GS::double3* input, int count);
}


