/**
 * @file behavior_explore.h
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#ifndef SRC_BEHAVIOR_EXPLORE_H_
#define SRC_BEHAVIOR_EXPLORE_H_

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
  * @brief Behavior explore for strategy pattern
  *
  */
class Explore : public Behaviors {
 public:
  Explore() {}
  ~Explore() {}
  void getwheelvelocity(
    double lsr,
    double rsr,
    double speed,
    WheelVelocity* wv) override;
};

NAMESPACE_END(csci3081);

#endif  // SRC_BEHAVIOR_EXPLORE_H_
