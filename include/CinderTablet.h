
#pragma once

#include "cinder/Signals.h"
#include "cinder/Vector.h"
#include "TabletData.h"

class CinderTablet
{
public:
    using signal_t = ci::signals::Signal<void ( const TabletData& )>;
    
    CinderTablet();
    void updateTabletPoint();
    void updateTabletProximity();
    inline TabletData &getData() { return mTabletData; }
    inline const TabletData &getData() const { return mTabletData; }
    inline signal_t &getTabletPointSignal() { return mTabletPointSignal; }
    inline signal_t &getTabletProximitySignal() { return mTabletProximitySignal; }
    inline bool isStylusInProximity() const { return mIsStylusInProximity; }
    
private:
    TabletData mTabletData;
    signal_t mTabletPointSignal;
    signal_t mTabletProximitySignal;
    bool mIsStylusInProximity{ false };
    bool mDoComputeTiltZ{ false };
};
