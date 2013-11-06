//
//  Created by Ray Wenderlich on 10/24/12.
//  Copyright (c) 2012 Razeware LLC. All rights reserved.
//
#pragma once
#include <stdlib.h>
#import <QuartzCore/CABase.h>
#define COST_QUIRK  10
#define COST_ZAP    25
#define COST_MUNCH  50

#define CCRANDOM_X_Y(__X__, __Y__) (((__Y__) - (__X__)) * (rand() / (float)RAND_MAX) + (__X__))

#define OPPOSITE_TEAM(__TEAM__)  (__TEAM__==1?2:1   )
typedef unsigned int UINT;

#define GetTickCount()  CACurrentMediaTime() * 1000