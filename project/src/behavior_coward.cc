/**
 * @file behavior_coward.cc
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
#include "src/behavior_coward.h"
#include "src/predator.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/

void Coward::getwheelvelocity(
  double lsr,
  double rsr,
  double speed,
  WheelVelocity *wv) {
    *wv = WheelVelocity(1.0*lsr, 1.0*rsr, speed);
}

NAMESPACE_END(csci3081);
