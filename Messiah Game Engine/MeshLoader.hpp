//
//  MeshLoader.hpp
//  Game Editor
//
//  Created by Attila Varga on 07/07/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#ifndef MeshLoader_hpp
#define MeshLoader_hpp

#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"
#include "Texture.hpp"


namespace DMGS
{
    class MeshLoader
    {
        std::vector<Mesh*> meshes;
        void recursiveProcess(aiNode* node, const aiScene* scene);
        void processMesh(aiMesh* mesh, const aiScene* scene);
        unsigned int LoadTexture(const char* filename);
        
    public:
        MeshLoader(const char* filename);
        ~MeshLoader();
        void draw(unsigned int programID);
        std::vector<Mesh*>& getMeshes();
    private:
    };
}

#endif /* MeshLoader_hpp */
