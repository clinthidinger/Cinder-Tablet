// Copyright (c) 2014 Matt Ebb
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "CinderTablet.h"

#ifdef __APPLE__
    #include "osx/TabletCocoa.h"
#endif

//ofEvent<TabletData> ciTablet::tabletEvent;
//TabletData ciTablet::tabletData;
CinderTablet::CinderTablet()
{
    mTabletData.tabletPointFunc = [this] () { updateTabletPoint(); };
    mTabletData.tabletProximityFunc = [this] () { updateTabletProximity(); };
#ifdef __APPLE__
    // only Mac Cocoa implemented so far
    setupTabletCocoa( mTabletData );
#endif
}

// Tablet data update method implemented here to so it can
// call ofNotifyEvent without including openframeworks in obj-c code
void CinderTablet::updateTabletPoint()
{
    
    //mTabletData.tiltVec[0] = mTabletData.tiltX;
    //mTabletData.tiltVec[1] = mTabletData.tiltY;
    //mTabletData.tiltVec[2] = sqrt( std::max( 0.0, 1.0 - ( mTabletData.tiltX * mTabletData.tiltX ) - ( mTabletData.tiltY * mTabletData.tiltY ) ) );
    
    mIsStylusInProximity = true;
    mTabletPointSignal.emit( mTabletData );
}

void CinderTablet::updateTabletProximity()
{
    mIsStylusInProximity = mTabletData.inProximity;
    mTabletProximitySignal.emit( mTabletData );
}
