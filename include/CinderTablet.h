// Copyright (c) 2014 Matt Ebb
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once
#include "cinder/Signals.h"
#include "cinder/vector.h"
#include "TabletData.h"

class CinderTablet
{
public:
    
    enum class TabletPointerType
	{
        Unknown = 0,       // should never happen
        Pen,               // tip end of a stylus like device
        Cursor,            // any puck like device
        Eraser             // eraser end of a stylus like device
    };
    
    using signal_t = ci::signals::Signal<void ( const TabletData& )>;
    
    CinderTablet();
    void init();
    void updateTabletPoint();
    void updateTabletProximity();
    inline TabletData &getData() { return mTabletData; }
    inline signal_t &getTabletPointSignal() { return mTabletPointSignal; }
    inline signal_t &getTabletProximitySignal() { return mTabletProximitySignal; }

private:
    TabletData mTabletData;
    signal_t mTabletPointSignal; // ??? Do we need these signals when TabletData has callbacks???
    signal_t mTabletProximitySignal;
};
