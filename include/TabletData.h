// Copyright (c) 2014 Matt Ebb
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#pragma once

//#include <functional>

enum class TabletPointerType
 {
    UNKNOWN,       // should never happen
    PEN,           // tip end of a stylus like device
    CURSOR,        // any puck like device
    ERASER         // eraser end of a stylus like device
};

// for meanings of fields see here: http://www.wacomeng.com/mac/Developers%20Guide.htm
struct TabletData
 {
    // from driver
    int x{ 0 };
    int y{ 0 };
    int absX{ 0 };
    int absY{ 0 };
    int absZ{ 0 };
    float tiltX{ 0.0 };          // 2d projection of normalized 3d vector on to ground plane, from driver
    float tiltY{ 0.0 };
    float pressure{ 0.0f };
    float rotation{ 0.0f };
    float tangentialPressure{ 0.0f };
    
    // from proximity events
    bool inProximity{ false };
    TabletPointerType pointerType{ TabletPointerType::Unknown };
    int pointerID{ 0 };          // index of the device on this tablet
    int deviceID{ 0 };           // used to match pointer events with proximity events
    
    int vendorID{ 0 };
    int vendorPointerType{ 0 };
    
    // custom for ofxTablet
    float absScreen[2];    // absolute floating point location relative to main screen in (0,1)
    float tiltVec[3];      // reconstructed 3d vector representing pen tilt
    
    // update global tablet data for use in openFrameworks, implemented in ciTablet.cpp
    //!!!std::function<void()> tabletPointFunc;
    //!!!std::function<void()> tabletProximityFunc;
    //void update();
};
