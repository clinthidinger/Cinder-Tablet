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

class CinderTabletApp : public ci::App
{
public:
    CinderTabletApp()
    {
        
         auto renderer = std::static_pointer_cast<RendererGl>( app::getWindow()->getRenderer() );
         renderer->setFinishDrawFn( [this] ( Renderer *renderer ) {
             if( mHasUpdate )
             {
                 renderer->swapBuffers();
                 --mHasUpdate;
             }
         } );
    }
    
    virtual ~CinderTabletApp() = default;
    virtual void refresh( int target, int refreshCount = 2 )
    {
        if( refreshCount > mHasUpdate )
        {
            mHasUpdate = refreshCount;
        }
    }
private:
    int mHasUpdate{ 0 };
}


#endif // CinderTabletApp_h
