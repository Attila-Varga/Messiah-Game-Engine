//
//  Program.hpp
//  Game Editor
//
//  Created by Attila Varga on 26/06/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#ifndef Program_hpp
#define Program_hpp

#include "Shader.hpp"
#include <vector>
#include "glm/glm.hpp"

namespace DMGS {
    
    /**
     Represents an OpenGL program made by linking shaders.
     */
    class Program {
    public:
        /**
         Creates a program by linking a list of tdogl::Shader objects
         
         @param shaders  The shaders to link together to make the program
         
         @throws std::exception if an error occurs.
         
         @see tdogl::Shader
         */
        Program(const std::vector<Shader>& shaders);
        ~Program();
        
        
        /**
         @result The program's object ID, as returned from glCreateProgram
         */
        GLuint object() const;
        
        void use() const;
        
        bool isInUse() const;
        
        void stopUsing() const;
        
        /**
         @result The attribute index for the given name, as returned from glGetAttribLocation.
         */
        GLint attrib(const GLchar* attribName) const;
        
        
        /**
         @result The uniform index for the given name, as returned from glGetUniformLocation.
         */
        GLint uniform(const GLchar* uniformName) const;
        
        /**
         Setters for attribute and uniform variables.
         
         These are convenience methods for the glVertexAttrib* and glUniform* functions.
         */
#define _TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(OGL_TYPE) \
void setAttrib(const GLchar* attribName, OGL_TYPE v0); \
void setAttrib(const GLchar* attribName, OGL_TYPE v0, OGL_TYPE v1); \
void setAttrib(const GLchar* attribName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2); \
void setAttrib(const GLchar* attribName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3); \
\
void setAttrib1v(const GLchar* attribName, const OGL_TYPE* v); \
void setAttrib2v(const GLchar* attribName, const OGL_TYPE* v); \
void setAttrib3v(const GLchar* attribName, const OGL_TYPE* v); \
void setAttrib4v(const GLchar* attribName, const OGL_TYPE* v); \
\
void setUniform(const GLchar* uniformName, OGL_TYPE v0); \
void setUniform(const GLchar* uniformName, OGL_TYPE v0, OGL_TYPE v1); \
void setUniform(const GLchar* uniformName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2); \
void setUniform(const GLchar* uniformName, OGL_TYPE v0, OGL_TYPE v1, OGL_TYPE v2, OGL_TYPE v3); \
\
void setUniform1v(const GLchar* uniformName, const OGL_TYPE* v, GLsizei count=1); \
void setUniform2v(const GLchar* uniformName, const OGL_TYPE* v, GLsizei count=1); \
void setUniform3v(const GLchar* uniformName, const OGL_TYPE* v, GLsizei count=1); \
void setUniform4v(const GLchar* uniformName, const OGL_TYPE* v, GLsizei count=1); \

        _TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(GLfloat)
        _TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(GLdouble)
        _TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(GLint)
        _TDOGL_PROGRAM_ATTRIB_N_UNIFORM_SETTERS(GLuint)
        
        void setUniformMatrix2(const GLchar* uniformName, const GLfloat* v, GLsizei count=1, GLboolean transpose=GL_FALSE);
        void setUniformMatrix3(const GLchar* uniformName, const GLfloat* v, GLsizei count=1, GLboolean transpose=GL_FALSE);
        void setUniformMatrix4(const GLchar* uniformName, const GLfloat* v, GLsizei count=1, GLboolean transpose=GL_FALSE);
        void setUniform(const GLchar* uniformName, const glm::mat2& m, GLboolean transpose=GL_FALSE);
        void setUniform(const GLchar* uniformName, const glm::mat3& m, GLboolean transpose=GL_FALSE);
        void setUniform(const GLchar* uniformName, const glm::mat4& m, GLboolean transpose=GL_FALSE);
        void setUniform(const GLchar* uniformName, const glm::vec3& v);
        void setUniform(const GLchar* uniformName, const glm::vec4& v);
        
        
    private:
        GLuint _object;
        
        //copying disabled
        Program(const Program&);
        const Program& operator=(const Program&);
    };
    
}

#endif /* Program_hpp */
