/**
 * @file behavior_aggressive.h
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#ifndef SRC_BEHAVIOR_AGGRESSIVE_H_
#define SRC_BEHAVIOR_AGGRESSIVE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include "src/common.h"
#include "src/wheel_velocity.h"
#include "src/behavior_enum.h"
#include "src/params.h"
#include "src/braitenberg_vehicle.h"
#include "src/predator.h"
#include "src/behaviors.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief Behavior Aggressive for strategy pattern
  *
  */
class Aggressive : public Behaviors{
 public:
  Aggressive() {}
  ~Aggressive() {}
  void getwheelvelocity(
    double lsr,
    double rsr,
    double speed,
    WheelVelocity* wv) override;
};

NAMESPACE_END(csci3081);

#endif  // SRC_BEHAVIOR_AGGRESSIVE_H_
