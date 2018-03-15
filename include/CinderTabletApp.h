//
//  CinderTabletApp.h
//  SimpleTabletApp
//
//  Created by clint hidinger on 3/12/18.
//

#ifndef CinderTabletApp_h
#define CinderTabletApp_h

#pragma once

#include "cinder/app/App.h"

class CinderTabletApp : public ci::app::App
{
public:
    CinderTabletApp()
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
    
    virtual ~CinderTabletApp() = default;

    void refresh()
    {
        refresh( 0, 2 );
    }

    void refresh( int target )
    {
        refresh( target, 2 );
    }

    virtual void refresh( int target, int refreshCount )
    {
        if( refreshCount > mHasUpdate )
        {
            mHasUpdate = refreshCount;
        }
    }

    void update() override
    {
        if( mHasUpdate == 0 )
        {
            return;
        }
    }

    void setup() override {}
    void draw() override {}
    void mouseDown( ci::app::MouseEvent event ) override {}
    void mouseUp( ci::app::MouseEvent event ) override {}
    void mouseWheel( ci::app::MouseEvent event ) override {}
    void mouseMove( ci::app::MouseEvent event ) override {}
    void mouseDrag( ci::app::MouseEvent event ) override {}
    void touchesBegan( ci::app::TouchEvent event ) override {}
    void touchesMoved( ci::app::TouchEvent event ) override {}
    void touchesEnded( ci::app::TouchEvent event ) override {}
    void keyDown( ci::app::KeyEvent event ) override {}
    void keyUp( ci::app::KeyEvent event ) override {}
    void resize() override {}
    void fileDrop( ci::app::FileDropEvent event ) override {}
    void cleanup() override {}

private:
    int mHasUpdate{ 0 };
};

#endif // CinderTabletApp_h
