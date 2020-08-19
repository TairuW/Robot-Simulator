/**
 * @file factory_food.cc
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
#include "src/factory_food.h"
/*******************************************************************************
* Namespaces
******************************************************************************/
NAMESPACE_BEGIN(csci3081);


Food* FactoryFood::create(json_object *config) {
  Food* food = new Food();
  food->LoadFromObject(config);
  num_Food_++;
  return food;
}

NAMESPACE_END(csci3081);
