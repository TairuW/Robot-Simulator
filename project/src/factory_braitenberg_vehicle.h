/**
 * @file factory_braitenberg_vehicle.h
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#ifndef SRC_FACTORY_BRAITENBERG_VEHICLE_H_
#define SRC_FACTORY_BRAITENBERG_VEHICLE_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "src/common.h"
#include "src/entity_type.h"
#include "src/params.h"
#include "src/pose.h"
#include "src/rgb_color.h"
#include "src/arena_entity.h"
#include "src/braitenberg_vehicle.h"
#include "src/factory_entity.h"

NAMESPACE_BEGIN(csci3081);

/**
 * @brief A Factory to create BraitenbergVehicle
 *
 */

class FactoryBraitenbergVehicle: public FactoryEntity {
 public:
  FactoryBraitenbergVehicle() {}
  ~FactoryBraitenbergVehicle() {}
  BraitenbergVehicle* create(json_object *config) override;
  FactoryBraitenbergVehicle(const FactoryBraitenbergVehicle &f) = delete;
  FactoryBraitenbergVehicle &operator=
   (const FactoryBraitenbergVehicle *other) = delete;
};


NAMESPACE_END(csci3081);

#endif  // SRC_FACTORY_BRAITENBERG_VEHICLE_H_
