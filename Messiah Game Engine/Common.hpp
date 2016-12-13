//
//  Common.hpp
//  Game Editor
//
//  Created by Attila Varga on 26/06/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#ifndef Common_hpp
#define Common_hpp

// standard C++ libraries
#include <cassert>
#include <iostream>
#include <stdexcept>
#include <cmath>
#include <stdio.h>
#include <string>

#include "Texture.hpp"

std::string ResourcePath(std::string fileName);


DMGS::Texture* loadTexture(const char* textureFileName);


#endif /* Common_hpp */
