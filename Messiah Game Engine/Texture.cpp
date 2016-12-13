//
//  Texture.cpp
//  Game Editor
//
//  Created by Attila Varga on 27/06/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#include "Texture.hpp"
#include <stdexcept>

using namespace DMGS;

static GLenum TextureFormatForBitmapFormat(Bitmap::Format format)
{
    switch (format) {
        case Bitmap::Format_Grayscale: return GL_RED;
        case Bitmap::Format_GrayscaleAlpha: return GL_RG;
        case Bitmap::Format_RGB: return GL_RGB;
        case Bitmap::Format_RGBA: return GL_RGBA;
        default: throw std::runtime_error("Unrecognised Bitmap::Format");
    }
}

Texture::Texture(const Bitmap& bitmap, GLint minMagFiler, GLint wrapMode) :
_originalWidth((GLfloat)bitmap.width()),
_originalHeight((GLfloat)bitmap.height())
{
    glGenTextures(1, &_object);
    glBindTexture(GL_TEXTURE_2D, _object);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minMagFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, minMagFiler);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapMode);
    glTexImage2D(GL_TEXTURE_2D,
                 0,
                 TextureFormatForBitmapFormat(bitmap.format()),
                 (GLsizei)bitmap.width(),
                 (GLsizei)bitmap.height(),
                 0,
                 TextureFormatForBitmapFormat(bitmap.format()),
                 GL_UNSIGNED_BYTE,
                 bitmap.pixelBuffer());
    glBindTexture(GL_TEXTURE_2D, 0);
}

Texture::~Texture()
{
    glDeleteTextures(1, &_object);
}

GLuint Texture::object() const
{
    return _object;
}

GLfloat Texture::originalWidth() const
{
    return _originalWidth;
}

GLfloat Texture::originalHeight() const
{
    return _originalHeight;
}
