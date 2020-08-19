/**
 * @file factory_ghost.cc
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#include "src/entity_type.h"
#include "src/factory_entity.h"
#include "src/braitenberg_vehicle.h"
#include "src/ghost.h"
#include "src/light.h"
#include "src/common.h"
#include "src/arena_mobile_entity.h"
#include "src/arena_immobile_entity.h"
#include "src/factory_ghost.h"
/*******************************************************************************
* Namespaces
******************************************************************************/
NAMESPACE_BEGIN(csci3081);


Ghost* FactoryGhost::create(json_object *config) {
  Ghost* ghost = new Ghost();
  ghost->LoadFromObject(config);
  num_Ghost_++;
  return ghost;
}

NAMESPACE_END(csci3081);
