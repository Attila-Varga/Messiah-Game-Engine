//
//  Mesh.hpp
//  Game Editor
//
//  Created by Attila Varga on 07/07/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include <iostream>
#include <vector>
#include <string>

#include "MeshData.h"

namespace  DMGS
{
    //Mesh class holds all information about geometry
    
    class Mesh
    {
        std::vector<VertexData> data;
        std::vector<TextureData> textures;
        std::vector<unsigned int> indices;
        unsigned int VBO;
        unsigned int IND;
    public:
        
        Mesh(std::vector<VertexData> *vd,std::vector<unsigned int> *id, std::vector<TextureData> *td );
        ~Mesh();
        void draw(unsigned int programID);
        
    private:
    };
}

#endif /* Mesh_hpp */
