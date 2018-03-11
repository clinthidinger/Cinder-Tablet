// Copyright (c) 2014 Matt Ebb
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#import <Cocoa/Cocoa.h>
#import "tabletCocoa.h"

// forward declarations, keep NSEvent out of the C++ compatible header
void handlePoint(TabletData &data, NSEvent *event);
void handleProximity(TabletData &data, NSEvent *event);

void setupTabletCocoa(TabletData &tabletData) {
    unsigned long long tabletmask =   NSMouseMovedMask|
                                NSLeftMouseDownMask|
                                NSRightMouseDownMask|
                                NSLeftMouseDraggedMask|
                                NSRightMouseDraggedMask;
    
    id handler = [NSEvent addLocalMonitorForEventsMatchingMask:tabletmask handler:^(NSEvent *event) {
        
        switch ([event subtype]) {
            case NX_SUBTYPE_TABLET_POINT:
                handlePoint(tabletData, event);
                tabletData.tabletPointFunc();
                break;
            case NX_SUBTYPE_TABLET_PROXIMITY:
                handleProximity(tabletData, event);
                tabletData.tabletProximityFunc();
                break;
            default:
                break;
        }
        return event;
    }];
}

void handlePoint(TabletData &data, NSEvent *event) {

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
    // Maybe only do this if we need it???
    data.tiltVec[0] = data.tiltX;
    data.tiltVec[1] = data.tiltY;
    data.tiltVec[2] = sqrt( std::max( 0.0, 1.0 - ( data.tiltX * data.tiltX ) - ( data.tiltY * data.tiltY ) ) );
}

void handleProximity(TabletData &data, NSEvent *event) {
    if ([event isEnteringProximity])
        data.in_proximity = TRUE;
    else
        data.in_proximity = FALSE;
    
    data.pointerType = [event pointingDeviceType];
    data.pointerID = [event pointingDeviceID];
    data.deviceID = [event deviceID];
    
    data.vendorID = [event vendorID];
    data.vendorPointerType = [event vendorPointingDeviceType];
}