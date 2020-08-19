/**
 * @file factory_predator.cc
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#include "src/entity_type.h"
#include "src/factory_entity.h"
#include "src/predator.h"
#include "src/common.h"
#include "src/arena_mobile_entity.h"
#include "src/arena_immobile_entity.h"
#include "src/factory_predator.h"
/*******************************************************************************
* Namespaces
******************************************************************************/
NAMESPACE_BEGIN(csci3081);

Predator* FactoryPredator::create(json_object *config) {
  Predator* predator = new Predator();
  predator->LoadFromObject(config);
  num_Predator_++;
  return predator;
}

NAMESPACE_END(csci3081);
