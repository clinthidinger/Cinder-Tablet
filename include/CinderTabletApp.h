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
#include "cinder/app/MouseEvent.h"
#include "cinder/app/TouchEvent.h"
#include "cinder/app/KeyEvent.h"
#include "CinderTablet.h"

class CinderTabletApp : public ci::app::App
{
public:
    CinderTabletApp();
    virtual ~CinderTabletApp() = default;

    void refresh();
    void refresh( int target );
    virtual void refresh( int target, int refreshCount );

    void update() override;
    void setup() override;
    void draw() override;
    void mouseDown( ci::app::MouseEvent event ) override;
    void mouseUp( ci::app::MouseEvent event ) override;
    void mouseWheel( ci::app::MouseEvent event ) override;
    void mouseMove( ci::app::MouseEvent event ) override;
    void mouseDrag( ci::app::MouseEvent event ) override;
    void touchesBegan( ci::app::TouchEvent event ) override;
    void touchesMoved( ci::app::TouchEvent event ) override;
    void touchesEnded( ci::app::TouchEvent event ) override;
    void keyDown( ci::app::KeyEvent event ) override;
    void keyUp( ci::app::KeyEvent event ) override;
    void resize() override;
    void fileDrop( ci::app::FileDropEvent event ) override;
    void cleanup() override;

protected:
    CinderTablet mTablet;
    int mHasUpdate{ 2 };
};

#endif // CinderTabletApp_h
