/**
 * @file food_decorator.cc
 *
 * @copyright Tairu Wang, All rights reserved.
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>

#include "src/food_decorator.h"
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

FoodDecorator::FoodDecorator() : predator_(nullptr) {
  pred_ = 1;
}

FoodDecorator::FoodDecorator(Predator* pre) : predator_(pre) {
  pred_ = 1;
  predator_->food_dec = 1;
}

void FoodDecorator::HandleCollision(EntityType ent_type,
                                     ArenaEntity* object) {
  Food::HandleCollision(ent_type, object);
  predator_->HandleCollision(ent_type, object);
}

ArenaEntity* FoodDecorator::get_internal_entity() {
  return predator_;
}

std::string FoodDecorator::get_name() const {
  return "Food Predator";
}

void FoodDecorator::TimestepUpdate(unsigned int dt) {
  if (predator_) {
    predator_->set_pose(get_pose());
  }
  Food::TimestepUpdate(dt);
}

NAMESPACE_END(csci3081);
