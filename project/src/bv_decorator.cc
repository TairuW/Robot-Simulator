/**
 * @file bv_decorator.cc
 *
 * @copyright Tairu Wang, All rights reserved.
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

#include "src/bv_decorator.h"
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

BVDecorator::BVDecorator() : predator_(nullptr) {
  pred_ = 1;
}

BVDecorator::BVDecorator(Predator* pre) : predator_(pre) {
  pred_ = 1;
  predator_->bv_dec = 1;
  int random = 10;
  srand(time(0));
  random = rand()%5;
  switch (random) {
    case 0:
      set_light_behavior(kExplore);
      break;
    case 1:
      set_light_behavior(kAggressive);
      break;
    case 2:
      set_light_behavior(kCoward);
      break;
    case 3:
      set_light_behavior(kLove);
      break;
    case 4:
      set_light_behavior(kNone);
      break;
    default:
      break;
  }
  srand(time(0));
  random = rand()%5;
  switch (random) {
    case 0:
      set_food_behavior(kExplore);
      break;
    case 1:
      set_food_behavior(kAggressive);
      break;
    case 2:
      set_food_behavior(kCoward);
      break;
    case 3:
      set_food_behavior(kLove);
      break;
    case 4:
      set_light_behavior(kNone);
      break;
    default:
      break;
  }
  set_bv_behavior(kAggressive);
}

void BVDecorator::HandleCollision(EntityType ent_type,
                                     ArenaEntity* object) {
  BraitenbergVehicle::HandleCollision(ent_type, object);
  predator_->HandleCollision(ent_type, object);
}

ArenaEntity* BVDecorator::get_internal_entity() {
  return predator_;
}

std::string BVDecorator::get_name() const {
  return "BV Predator";
}

void BVDecorator::TimestepUpdate(unsigned int dt) {
  if (predator_) {
    predator_->set_pose(get_pose());
  }
  BraitenbergVehicle::TimestepUpdate(dt);
}



NAMESPACE_END(csci3081);
