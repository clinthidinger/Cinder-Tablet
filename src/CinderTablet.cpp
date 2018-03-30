
#include "CinderTablet.h"

#ifdef __APPLE__
    #include "osx/TabletCocoa.h"
#endif

CinderTablet::CinderTablet()
{
    mTabletData.tabletPointFunc = [this] () { updateTabletPoint(); };
    mTabletData.tabletProximityFunc = [this] () { updateTabletProximity(); };
#ifdef __APPLE__
    setupTabletCocoa( mTabletData );
#endif
}

void CinderTablet::updateTabletPoint()
{
    mIsStylusInProximity = true;
    if( mDoComputeTiltZ )
    {
        auto xSq = ( mTabletData.tiltX * mTabletData.tiltX );
        auto ySq = ( mTabletData.tiltY * mTabletData.tiltY );
        mTabletData.tiltVec[2] = std::sqrt( std::max<float>( 0.0f, 1.0f - xSq - ySq ) );
    }
    mTabletPointSignal.emit( mTabletData );
}

void CinderTablet::updateTabletProximity()
{
    mIsStylusInProximity = mTabletData.inProximity;
    mTabletProximitySignal.emit( mTabletData );
}
