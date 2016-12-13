//
//  MeshLoader.cpp
//  Game Editor
//
//  Created by Attila Varga on 07/07/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#include "MeshLoader.hpp"
#include "Common.hpp"

#include <fstream>
#include <unistd.h>

void DMGS::MeshLoader::recursiveProcess(aiNode* node,const aiScene* scene)
{
    //process
    for(int i=0;i<node->mNumMeshes;i++)
    {
        aiMesh* mesh=scene->mMeshes[node->mMeshes[i]];
        processMesh(mesh,scene);
    }
    
    
    
    //recursion
    for(int i=0;i<node->mNumChildren;i++)
    {
        recursiveProcess(node->mChildren[i],scene);
    }
}

void DMGS::MeshLoader::processMesh(aiMesh* mesh,const aiScene* scene)
{
    std::vector<VertexData> data;
    std::vector<unsigned int> indices;
    std::vector<TextureData> textures;
    aiColor4D col;
    aiMaterial* mat=scene->mMaterials[mesh->mMaterialIndex];
    aiGetMaterialColor(mat,AI_MATKEY_COLOR_DIFFUSE,&col);
    glm::vec3 defaultColor(col.r,col.g,col.b);
    
    
    for(int i=0;i<mesh->mNumVertices;i++)
    {
        VertexData tmp;
        glm::vec3 tmpVec;
        
        //position
        tmpVec.x=mesh->mVertices[i].x;
        tmpVec.y=mesh->mVertices[i].y;
        tmpVec.z=mesh->mVertices[i].z;
        tmp.position=tmpVec;
        
        //normals
        tmpVec.x=mesh->mNormals[i].x;
        tmpVec.y=mesh->mNormals[i].y;
        tmpVec.z=mesh->mNormals[i].z;
        tmp.normal=tmpVec;
        
        
        //tangent
        if(mesh->mTangents)
        {
            tmpVec.x=mesh->mTangents[i].x;
            tmpVec.y=mesh->mTangents[i].y;
            tmpVec.z=mesh->mTangents[i].z;
        }else{
            tmpVec.x=1.0;
            tmpVec.y=tmpVec.z=0;
        }
        tmp.tangent=tmpVec;
        
        
        //colors
        if(mesh->mColors[0])
        {
            //!= material color
            tmpVec.x=mesh->mColors[0][i].r;
            tmpVec.y=mesh->mColors[0][i].g;
            tmpVec.z=mesh->mColors[0][i].b;
        }else{
            tmpVec=defaultColor;
        }
        tmp.color=tmpVec;
        
        //color
        if(mesh->mTextureCoords[0])
        {
            tmpVec.x=mesh->mTextureCoords[0][i].x;
            tmpVec.y=mesh->mTextureCoords[0][i].y;
        }else{
            tmpVec.x=tmpVec.y=tmpVec.z=0.0;
        }
        tmp.U=tmpVec.x;
        tmp.V=tmpVec.y;
        data.push_back(tmp);
    }
    
    for(int i=0;i<mesh->mNumFaces;i++)
    {
        aiFace face=mesh->mFaces[i];
        for(int j=0;j<face.mNumIndices;j++) //0..2
        {
            indices.push_back(face.mIndices[j]);
        }
    }
    
    
    for(int i=0;i<mat->GetTextureCount(aiTextureType_DIFFUSE);i++)
    {
        aiString str;
        mat->GetTexture(aiTextureType_DIFFUSE,i,&str);
        TextureData tmp;
        tmp.id=LoadTexture(str.C_Str());
        tmp.type=0;
        textures.push_back(tmp);
    }
    meshes.push_back(new Mesh::Mesh(&data,&indices,&textures));
}

unsigned int DMGS::MeshLoader::LoadTexture(const char* filename)
{
    unsigned int num;
   /* glGenTextures(1,&num);
    
    //TODO REMOVE IMG
    DMGS::Texture* img = loadTexture(filename);
    if(img==NULL)
    {
        //std::cout << "img was not loaded" << std::endl;
        return -1;
    }
    
    glBindTexture(GL_TEXTURE_2D,num);
    
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
    //glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,img->w,img->h,0,GL_RGBA,GL_UNSIGNED_INT_8_8_8_8,img->pixels);
        return num;*/
    
    return num;
}


DMGS::MeshLoader::MeshLoader(const char* filename)
{
    Assimp::Importer importer;
    
    std::ifstream infile(filename);
    
    char wd[1024];
    std::cout << getcwd(wd, sizeof(wd)) << std::endl;
    
    if (!infile)
    {
        std::cout<<filename<<" doesn't exist.";
    }
    
    
    
    const aiScene* scene=importer.ReadFile(filename, aiProcess_GenSmoothNormals | aiProcess_Triangulate | aiProcess_CalcTangentSpace | aiProcess_FlipUVs);
    if(!scene->mRootNode)
    {
        std::cout << "The file wasn't successfuly opened (mRootNode)" << filename << std::endl;
        return;
    }
    
    if(scene->mFlags==AI_SCENE_FLAGS_INCOMPLETE)
    {
        std::cout << "The file wasn't successfuly opened (mFlags)" << filename << std::endl;
        return; 
    }
   
    
    recursiveProcess(scene->mRootNode,scene);
}

DMGS::MeshLoader::~MeshLoader()
{
    for(int i=0;i<meshes.size();i++)
        delete meshes[i];
}

void DMGS::MeshLoader::draw(unsigned int programId)
{
    for(int i=0;i<meshes.size();i++)
        meshes[i]->draw(programId);	
}

std::vector<DMGS::Mesh*>& DMGS::MeshLoader::getMeshes()
{
    return meshes;
}
