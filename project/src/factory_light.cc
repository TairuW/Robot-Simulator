/**
 * @file factory_light.cc
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
#include "src/factory_light.h"
/*******************************************************************************
* Namespaces
******************************************************************************/
NAMESPACE_BEGIN(csci3081);

Light* FactoryLight::create(json_object *config) {
  Light* light = new Light();
  light->LoadFromObject(config);
  num_Light_++;
  return light;
}

NAMESPACE_END(csci3081);
