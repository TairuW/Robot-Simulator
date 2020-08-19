/**
 * @file behavior_none.cc
 *
 * @copyright Tairu Wang, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include "src/common.h"
#include "src/arena_mobile_entity.h"
#include "src/motion_behavior_differential.h"
#include "src/wheel_velocity.h"
#include "src/behavior_enum.h"
#include "src/params.h"
#include "src/braitenberg_vehicle.h"
#include "src/behavior_none.h"
#include "src/predator.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

void None::getwheelvelocity(
  double lsr,
  double rsr,
  double speed,
  WheelVelocity* wv) {
    *wv = WheelVelocity(0.0*lsr, 0.0*rsr, speed);
}

NAMESPACE_END(csci3081);
