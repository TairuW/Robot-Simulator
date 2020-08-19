/**
 * @file factory_braitenberg_vehicle.cc
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#include "src/entity_type.h"
#include "src/factory_entity.h"
#include "src/braitenberg_vehicle.h"
#include "src/food.h"
#include "src/light.h"
#include "src/common.h"
#include "src/arena_mobile_entity.h"
#include "src/arena_immobile_entity.h"
#include "src/factory_braitenberg_vehicle.h"
/*******************************************************************************
* Namespaces
******************************************************************************/
NAMESPACE_BEGIN(csci3081);

BraitenbergVehicle* FactoryBraitenbergVehicle::create(json_object *config) {
  BraitenbergVehicle* bv = new BraitenbergVehicle();
  bv->LoadFromObject(config);
  num_Braitenberg_++;
  return bv;
}

NAMESPACE_END(csci3081);
