/**
 * @file light_decorator.cc
 *
 * @copyright Tairu Wang, All rights reserved.
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>

#include "src/light_decorator.h"
#include "src/predator.h"
#include "src/arena_mobile_entity.h"
#include "src/motion_behavior_differential.h"
#include "src/common.h"
#include "src/entity_type.h"
#include "src/pose.h"
#include "src/params.h"
#include "src/braitenberg_vehicle.h"


/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

LightDecorator::LightDecorator() : predator_(nullptr) {
  pred_ = 1;
}

LightDecorator::LightDecorator(Predator* pre) : predator_(pre) {
  pred_ = 1;
  predator_->light_dec = 1;
}

void LightDecorator::HandleCollision(EntityType ent_type,
                                     ArenaEntity* object) {
  Light::HandleCollision(ent_type, object);
  predator_->HandleCollision(ent_type, object);
}

ArenaEntity* LightDecorator::get_internal_entity() {
  return predator_;
}

std::string LightDecorator::get_name() const {
  return "Light Predator";
}

void LightDecorator::TimestepUpdate(unsigned int dt) {
  if (predator_) {
    predator_->set_pose(get_pose());
  }
  Light::TimestepUpdate(dt);
}


NAMESPACE_END(csci3081);
