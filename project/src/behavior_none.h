/**
 * @file behavior_None.h
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#ifndef SRC_BEHAVIOR_NONE_H_
#define SRC_BEHAVIOR_NONE_H_

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
#include "src/behaviors.h"
#include "src/predator.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief Behavior none for strategy pattern
  *
  */
class None:public Behaviors{
 public:
  None() {}
  ~None() {}
  void getwheelvelocity(
    double lsr,
    double rsr,
    double speed,
    WheelVelocity* wv) override;
};

NAMESPACE_END(csci3081);

#endif  // SRC_BEHAVIOR_NONE_H_
