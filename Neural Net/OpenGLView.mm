//
//  OpenGLView.m
//  Game Editor
//
//  Created by Attila Varga on 26/06/2016.
//  Copyright © 2016 Attila Varga. All rights reserved.
//

#import "OpenGLView.h"

#include <OpenGL/gl.h>

@implementation OpenGLView

- (void) awakeFromNib
{
    NSOpenGLPixelFormatAttribute pixelFormatAttributes[] =
    {
        NSOpenGLPFAOpenGLProfile, NSOpenGLProfileVersion3_2Core,
        NSOpenGLPFAColorSize    , 24                           ,
        NSOpenGLPFAAlphaSize    , 8                            ,
        NSOpenGLPFADepthSize    , 16                            ,
        NSOpenGLPFADoubleBuffer ,
        NSOpenGLPFAAccelerated  ,
        NSOpenGLPFANoRecovery   ,
        0
    };
    NSOpenGLPixelFormat *pixelFormat = [[NSOpenGLPixelFormat alloc] initWithAttributes:pixelFormatAttributes];
    
    super.pixelFormat=pixelFormat;
    
    // 2. Make the context current
    [[self openGLContext] makeCurrentContext];
    
    //Make the NSOpenGLView first responder to receive keypress events
    [[self window] makeFirstResponder:self];
    
    //Run 3D engine and load shaders,vertices
    
    engine = new DMGS::DMEngine();
    engine->startEngine();
    //engine->loadTexture();
   // engine->loadShaders();
    engine->createScene();
    
    camera = engine->getCamera();
}

//
//
- (void) setupAnimationTimerWithInterval:(const float)inInterval
{
    SEL the_selector = @selector( timerUpdate );
    NSMethodSignature * a_signature = [OpenGLView instanceMethodSignatureForSelector:the_selector];
    NSInvocation * an_invocation = [NSInvocation invocationWithMethodSignature:a_signature] ;
    [an_invocation setSelector:the_selector];
    [an_invocation setTarget:self];
    
    m_timer = [NSTimer scheduledTimerWithTimeInterval:inInterval
                                           invocation:an_invocation
                                              repeats:YES];
    
    [[NSRunLoop currentRunLoop] addTimer:m_timer forMode:NSDefaultRunLoopMode];
    [[NSRunLoop currentRunLoop] addTimer:m_timer forMode:NSEventTrackingRunLoopMode];
    [[NSRunLoop currentRunLoop] addTimer:m_timer forMode:NSModalPanelRunLoopMode];
}

//
//
- (void) timerUpdate
{
    [self setNeedsDisplay:YES];
}

//
//
- (void) resizeGL
{
    NSRect rectView = [self bounds];
    
    if( m_rectView.size.width != rectView.size.width || m_rectView.size.height != rectView.size.height )
    {
        glViewport( 0, 0, rectView.size.width, rectView.size.height );
        m_rectView = rectView;
    }
}

//
//
- (void) prepareOpenGL
{
    glClearColor(0, 0, 0, 0);
    
    GLint vblSynch = 1;
    [[self openGLContext] setValues:&vblSynch forParameter:NSOpenGLCPSwapInterval];
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    [self setupAnimationTimerWithInterval:(1.0f/60.0f)];
    
    [super prepareOpenGL];
}

//
//
- (void) drawRect:(NSRect)rect
{
    
    [self resizeGL];
    elapsedTime = [m_timer timeInterval];
    
    engine->render(elapsedTime);
    [[self openGLContext] flushBuffer];
}

//
//
- (void) mouseDown:(NSEvent*) event;
{
   
}

- (void) mouseDragged:(NSEvent *)event
{
    engine->cameraLook([event deltaX] , [event deltaY]);
}

- (BOOL)acceptsFirstResponder {
    return YES;
}

- (void) keyDown:(NSEvent *)theEvent
{
    
    
    NSString* str = [theEvent characters];
    
    NSLog(str);
    
    
    switch ([theEvent keyCode]) {
        case 123:    // Left arrow
            camera->Moving(true);
            camera->moveLeft();
            break;
        case 124:    // Right arrow
            camera->Moving(true);
            camera->moveRight();
            break;
        case 125:    // Down arrow
            camera->Moving(true);
            camera->moveBackward();
            break;
        case 126:    // Up arrow
            camera->Moving(true);
            camera->moveForward();
            break;
        default:
            break;
    }
}

- (void) keyUp:(NSEvent *)theEvent
{
    switch ([theEvent keyCode]) {
        case 123:    // Left arrow
            camera->stopCamera();
            break;
        case 124:    // Right arrow
            camera->stopCamera();
            break;
        case 125:    // Down arrow
            camera->stopCamera();
            break;
        case 126:    // Up arrow
            camera->stopCamera();
            break;
        default:
            break;
    }
}


@end
