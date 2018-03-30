//
//  CinderTabletApp.cpp
//  Cinder-Tablet
//
//  Created by clint hidinger on 3/30/18.
//

#include "CinderTabletApp.h"
#include "cinder/app/RendererGl.h"

CinderTabletApp::CinderTabletApp()
{
    auto renderer = std::static_pointer_cast<ci::app::RendererGl>( ci::app::getWindow()->getRenderer() );
    renderer->setFinishDrawFn( [this] ( ci::app::Renderer *renderer ) {
        if( mHasUpdate )
        {
            renderer->swapBuffers();
            --mHasUpdate;
        }
    } );
}

void CinderTabletApp::refresh()
{
    refresh( 0, 2 );
}

void CinderTabletApp::refresh( int target )
{
    refresh( target, 2 );
}

void CinderTabletApp::refresh( int target, int refreshCount )
{
    if( refreshCount > mHasUpdate )
    {
        mHasUpdate = refreshCount;
    }
}

void CinderTabletApp::update() {}
void CinderTabletApp::setup() {}
void CinderTabletApp::draw() {}
void CinderTabletApp::mouseDown( ci::app::MouseEvent event ) {}
void CinderTabletApp::mouseUp( ci::app::MouseEvent event ) {}
void CinderTabletApp::mouseWheel( ci::app::MouseEvent event ) {}
void CinderTabletApp::mouseMove( ci::app::MouseEvent event ) {}
void CinderTabletApp::mouseDrag( ci::app::MouseEvent event ) {}
void CinderTabletApp::touchesBegan( ci::app::TouchEvent event ) {}
void CinderTabletApp::touchesMoved( ci::app::TouchEvent event ) {}
void CinderTabletApp::touchesEnded( ci::app::TouchEvent event ) {}
void CinderTabletApp::keyDown( ci::app::KeyEvent event ) {}
void CinderTabletApp::keyUp( ci::app::KeyEvent event ) {}
void CinderTabletApp::resize() {}
void CinderTabletApp::fileDrop( ci::app::FileDropEvent event ) {}
void CinderTabletApp::cleanup() {}
