/**
 * @file behaviors.h
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#ifndef SRC_BEHAVIORS_H_
#define SRC_BEHAVIORS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <ctime>
#include <string>
#include <vector>
#include <iostream>
#include "src/common.h"
#include "src/arena_entity.h"
#include "src/wheel_velocity.h"
#include "src/behavior_enum.h"
#include "src/params.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief Behaviors for strategy pattern
  *
  */
class Behaviors{
 public:
  Behaviors() {}
  virtual ~Behaviors() {}
  virtual void getwheelvelocity(
    double lsr,
    double rsr,
    double speed,
    WheelVelocity *wv) = 0;
};

NAMESPACE_END(csci3081);

#endif  // SRC_BEHAVIORS_H_
