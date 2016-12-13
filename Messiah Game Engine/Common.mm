//
//  Common.cpp
//  Game Editor
//
//  Created by Attila Varga on 26/06/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#include "Common.hpp"
#include "Foundation/Foundation.h"

// returns the full path to the file `fileName` in the resources directory of the app bundle
std::string ResourcePath(std::string fileName) {
    NSString* fname = [NSString stringWithCString:fileName.c_str() encoding:NSUTF8StringEncoding];
    NSString* path = [[[NSBundle mainBundle] resourcePath] stringByAppendingPathComponent:fname];
    return std::string([path cStringUsingEncoding:NSUTF8StringEncoding]);
}



DMGS::Texture* loadTexture(const char* textureFileName)
{
    DMGS::Bitmap bmp = DMGS::Bitmap::bitmapFromFile(ResourcePath(textureFileName));
   // bmp.flipVertically();
    return new DMGS::Texture(bmp);
}