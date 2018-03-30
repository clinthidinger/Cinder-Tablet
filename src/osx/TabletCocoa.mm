// Copyright (c) 2014 Matt Ebb
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
// Referenced from https://github.com/mattebb/ofxTablet


#import "osx/TabletCocoa.h"
#include <algorithm>
#include <cmath>
#import <Cocoa/Cocoa.h>


void handlePoint( TabletData &data, NSEvent *event );
void handleProximity( TabletData &data, NSEvent *event );

void setupTabletCocoa( TabletData &tabletData )
{
    unsigned long long tabletMask = NSEventMaskMouseMoved |
                                    NSEventMaskLeftMouseDown |
                                    NSEventMaskRightMouseDown |
                                    NSEventMaskLeftMouseDragged |
                                    NSEventMaskRightMouseDragged |
                                    NSEventMaskTabletPoint |
                                    NSEventMaskTabletProximity
                                    ;
    
    [NSEvent addLocalMonitorForEventsMatchingMask:tabletMask handler:^( NSEvent *event ) {
        
        switch ([event subtype])
        {
            case NX_SUBTYPE_TABLET_POINT:
                handlePoint( tabletData, event );
                tabletData.tabletPointFunc();
                break;
            case NX_SUBTYPE_TABLET_PROXIMITY:
                handleProximity( tabletData, event );
                tabletData.tabletProximityFunc();
                break;
            default:
                break;
        }
        
        return event;
    }];
}

void handlePoint( TabletData &data, NSEvent *event )
{
    NSRect frame = [[NSScreen mainScreen] frame];
    data.absScreen[0] = [NSEvent mouseLocation].x / (frame.size.width);
    data.absScreen[1] = [NSEvent mouseLocation].y / (frame.size.height);
    data.absX = [NSEvent mouseLocation].x;
    data.absY = [NSEvent mouseLocation].y;
    data.x = [event locationInWindow].x;
    data.y = [event locationInWindow].y;
    data.pressure = [event pressure];
    data.tiltX = [event tilt].x;
    data.tiltY = [event tilt].y;
    data.rotation = [event rotation];
    data.tangentialPressure = [event tangentialPressure];
    data.tiltVec[0] = data.tiltX;
    data.tiltVec[1] = data.tiltY;
}

void handleProximity( TabletData &data, NSEvent *event )
{
    data.inProximity = [event isEnteringProximity];
    data.pointerType = (TabletPointerType)[event pointingDeviceType];
    data.pointerID = [event pointingDeviceID];
    data.deviceID = [event deviceID];
    data.vendorID = [event vendorID];
    data.vendorPointerType = [event vendorPointingDeviceType];
}
