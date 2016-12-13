//
//  Mesh.cpp
//  Game Editor
//
//  Created by Attila Varga on 07/07/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#include "Mesh.hpp"
#include "OpenGL/gl3.h"

DMGS::Mesh::Mesh(std::vector<VertexData> *vd,std::vector<unsigned int> *id, std::vector<TextureData> *td )
{
    data = *vd;
    indices = *id;
    if(td)
        textures = *td;
    
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(VertexData), &data[0], GL_STATIC_DRAW);
    
    glGenBuffers(1,&IND);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IND);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
    
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}

DMGS::Mesh::~Mesh()
{
    glDeleteBuffers(1,&VBO);
    glDeleteBuffers(1,&IND);
}

void DMGS::Mesh::draw(unsigned int programID)
{
    //attribute vec3 vertex
    int vertex=glGetAttribLocation(programID,"vertex"); //0
    int normal=glGetAttribLocation(programID,"normal"); //1
    int tangent=glGetAttribLocation(programID,"tangent"); //2
    int color=glGetAttribLocation(programID,"color"); //3
    int UV=glGetAttribLocation(programID,"UV"); //4
    
    //texture0
    //texture1...
    std::string str="texture";
    for(int i=0;i<textures.size();i++)
    {
        glActiveTexture(GL_TEXTURE0+i);
        glBindTexture(GL_TEXTURE_2D,textures[i].id);
        glUniform1i(glGetUniformLocation(programID,(str+(char)(i+'0')).c_str()),i);
    }
    
    glBindBuffer(GL_ARRAY_BUFFER,VBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,IND);
    
    glEnableVertexAttribArray(vertex);
    glVertexAttribPointer(vertex,3,GL_FLOAT,GL_FALSE,sizeof(VertexData),0);
    
    glEnableVertexAttribArray(normal);
    glVertexAttribPointer(normal,3,GL_FLOAT,GL_FALSE,sizeof(VertexData),(void*)(3*sizeof(float)));
    
    glEnableVertexAttribArray(tangent);
    glVertexAttribPointer(tangent,3,GL_FLOAT,GL_FALSE,sizeof(VertexData),(void*)(6*sizeof(float)));
    
    glEnableVertexAttribArray(color);
    glVertexAttribPointer(color,3,GL_FLOAT,GL_FALSE,sizeof(VertexData),(void*)(9*sizeof(float)));
    
    glEnableVertexAttribArray(UV);
    glVertexAttribPointer(UV,2,GL_FLOAT,GL_FALSE,sizeof(VertexData),(void*)(12*sizeof(float)));
    
    glDrawElements(GL_TRIANGLES,indices.size(),GL_UNSIGNED_INT,0);
    
    glDisableVertexAttribArray(vertex);
    glDisableVertexAttribArray(normal);
    glDisableVertexAttribArray(tangent);
    glDisableVertexAttribArray(color);
    glDisableVertexAttribArray(UV);
    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,0);
}
