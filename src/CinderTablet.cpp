// Copyright (c) 2014 Matt Ebb
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "CinderTablet.h"

#ifdef __APPLE__
    #include "TabletCocoa.h"
#endif

//ofEvent<TabletData> ciTablet::tabletEvent;
//TabletData ciTablet::tabletData;
ciTablet::ciTablet()
{
    init();
}

void ciTablet::init()
{
    mTabletData.tabletPointFunc = std::bind(&ciTablet::updateTabletPoint, this);
    mTabletData.tabletProximityFunc = std::bind(&ciTablet::updateTabletProximity, this);
#ifdef __APPLE__
    // only Mac Cocoa implemented so far
    setupTabletCocoa(mTabletData);
#endif

}

// Tablet data update method implemented here to so it can
// call ofNotifyEvent without including openframeworks in obj-c code
void ciTablet::updateTabletPoint() 
{
    
    //mTabletData.tiltVec[0] = mTabletData.tiltX;
    //mTabletData.tiltVec[1] = mTabletData.tiltY;
    //mTabletData.tiltVec[2] = sqrt( std::max( 0.0, 1.0 - ( mTabletData.tiltX * mTabletData.tiltX ) - ( mTabletData.tiltY * mTabletData.tiltY ) ) );
    
    mTabletPointSignal.emit( mTabletData );
}

void ciTablet::updateTabletProximity()
{
    mTabletProximitySignal.emit( mTabletData );
}
