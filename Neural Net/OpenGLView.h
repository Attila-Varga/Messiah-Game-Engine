//
//  OpenGLView.h
//  Game Editor
//
//  Created by Attila Varga on 26/06/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#import <Cocoa/Cocoa.h>

#include "DMEngine.hpp"

@interface OpenGLView : NSOpenGLView
{
    NSTimer * m_timer;
    NSRect m_rectView;
    
    float elapsedTime;
    
    DMGS::DMEngine *engine;
    DMGS::Camera* camera;
}
- (BOOL)acceptsFirstResponder ;
//
//
- (void) setupAnimationTimerWithInterval:(const float)inInterval;

//
//
- (void) timerUpdate;

//
//
- (void) resizeGL;

//
//
- (void) prepareOpenGL;

//
//
- (void) drawRect:(NSRect)rect;

- (void) mouseDragged: (NSEvent*) event; // Mouse click-and-drag
- (void) mouseUp: (NSEvent*) event; // Mouse button released
- (void) mouseDown: (NSEvent*) event; // Mouse button pressed
- (void) keyDown: (NSEvent*) theEvent; // Keyboard key pressed
- (void) keyUp: (NSEvent*) theEvent; //Keyboard key released


@end
