//
//  MeshData.h
//  Game Editor
//
//  Created by Attila Varga on 07/07/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#ifndef MeshData_h
#define MeshData_h

#include "glm/glm.hpp"

namespace DMGS
{
    struct VertexData
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec3 tangent;
        glm::vec3 color;
        float U,V;
    };
    
    struct TextureData
    {
        unsigned int id;
        unsigned int type;
    };
}




#endif /* MeshData_h */
