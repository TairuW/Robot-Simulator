/**
 * @file predator.cc
 *
 * @copyright Tairu Wang, All rights reserved.
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "src/predator.h"
#include "src/params.h"
#include "src/braitenberg_vehicle.h"
#include "src/behaviors.h"
#include "src/behavior_love.h"
#include "src/behavior_explore.h"
#include "src/behavior_aggressive.h"
#include "src/behavior_coward.h"
#include "src/behavior_none.h"

class SensorLightLove;
/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

int Predator::count = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/

Predator::Predator() :
  light_sensors_(), light_wheel_velocity(), food_wheel_velocity(),
  bv_wheel_velocity(), predator_wheel_velocity(), light_behavior_(kCoward),
  food_behavior_(kNone), bv_behavior_(kAggressive), predator_behavior_(kNone),
  closest_light_entity_(NULL), closest_food_entity_(NULL),
  closest_bv_entity_(NULL), closest_predator_entity_(NULL),
   defaultSpeed_(5.0) {
  set_type(kPredator);
  motion_behavior_ = new MotionBehaviorDifferential(this);
  light_sensors_.push_back(Pose());
  light_sensors_.push_back(Pose());
  set_color(PREDATOR_COLOR);
  set_pose(ROBOT_INIT_POS);

  light_wheel_velocity = WheelVelocity(0, 0);
  food_wheel_velocity = WheelVelocity(0, 0);
  bv_wheel_velocity = WheelVelocity(0, 0);
  predator_wheel_velocity = WheelVelocity(0, 0);

  // Set ID
  count++;
  set_id(count);

  // set flag
  pred_ = 1;
}

void Predator::TimestepUpdate(__unused unsigned int dt) {
  if (is_moving()) {
    motion_behavior_->UpdatePose(dt, wheel_velocity_);
  }
  timestep += 1;
  timescollision += 1;
  if (timescollision == 20) {
    set_heading(static_cast<int>((get_pose().theta - 45)) % 360);
  }
  UpdateLightSensors();
}

void Predator::HandleCollision(EntityType ent_type,
                                         ArenaEntity * object) {
  if (ent_type == kBraitenberg) {
    static_cast<BraitenbergVehicle*>(object)->getkill();
    ConsumeFood();
  } else {
    set_heading(static_cast<int>((get_pose().theta + 180)) % 360);
    timescollision = 0;
  }
}

void Predator::SenseEntity(const ArenaEntity& entity) {
  const ArenaEntity** closest_entity_ = NULL;
  if (entity.get_type() == kLight) {
    closest_entity_ = &closest_light_entity_;
  } else if (entity.get_type() == kFood) {
    closest_entity_ = &closest_food_entity_;
  } else if (entity.get_type() == kBraitenberg) {
    closest_entity_ = &closest_bv_entity_;
  } else if (entity.get_type() == kPredator) {
    closest_entity_ = &closest_predator_entity_;
  }

  if (!closest_entity_) {
    return;
  }

  if (!*closest_entity_) {
    *closest_entity_ = &entity;
  }

  double distance = (this->get_pose()-entity.get_pose()).Length();
  double closest_distance =
  (this->get_pose()-(*closest_entity_)->get_pose()).Length();
  if (distance < closest_distance) {
    *closest_entity_ = &entity;
    closest_distance = distance;
  }
  if (closest_distance > 100.0) {
    *closest_entity_ = NULL;
  }
}

void Predator::Update() {
  if (B_light != nullptr) {
    B_light->getwheelvelocity(
      get_sensor_reading_left(closest_light_entity_),
      get_sensor_reading_right(closest_light_entity_),
      defaultSpeed_,
      &light_wheel_velocity);
  }

  if (B_food != nullptr) {
    B_food->getwheelvelocity(
      get_sensor_reading_left(closest_food_entity_),
      get_sensor_reading_right(closest_food_entity_),
      defaultSpeed_,
      &food_wheel_velocity);
  }
  if (B_bv != nullptr) {
    B_bv->getwheelvelocity(
      get_sensor_reading_left(closest_bv_entity_),
      get_sensor_reading_right(closest_bv_entity_),
      defaultSpeed_,
      &bv_wheel_velocity);
  }
  if (B_predator != nullptr) {
    B_predator->getwheelvelocity(
      get_sensor_reading_left(closest_bv_entity_),
      get_sensor_reading_right(closest_bv_entity_),
      defaultSpeed_,
      &predator_wheel_velocity);
  }


  if (numBehaviors) {
    wheel_velocity_ = WheelVelocity(
      (light_wheel_velocity.left + food_wheel_velocity.left +
         bv_wheel_velocity.left + predator_wheel_velocity.left)/numBehaviors,
      (light_wheel_velocity.right + food_wheel_velocity.right +
         bv_wheel_velocity.right + predator_wheel_velocity.right)/numBehaviors,
      defaultSpeed_);
  } else {
    wheel_velocity_ = WheelVelocity(0, 0);
  }
}

std::string Predator::get_name() const {
  return "Predator " + std::to_string(get_id());
}

std::vector<Pose> Predator::get_light_sensors_const() const {
  return light_sensors_;
}

std::vector<Pose> Predator::get_light_sensors() {
  return light_sensors_;
}

double Predator::get_sensor_reading_left(const ArenaEntity* entity) {
  if (entity) {
    return 1800.0/std::pow(
      1.08, (entity->get_pose()-light_sensors_[0]).Length());
  }

  return 0.0001;
}

double Predator::get_sensor_reading_right(const ArenaEntity* entity) {
  if (entity) {
    return 1800.0/std::pow(
      1.08, (entity->get_pose()-light_sensors_[1]).Length());
  }

  return 0.0001;
}

void Predator::UpdateLightSensors() {
  for (unsigned int f = 0; f < light_sensors_.size(); f++) {
    Pose& pos = light_sensors_[f];
    if (f == 0) {
      pos.x = get_pose().x + get_radius() * cos(deg2rad(get_pose().theta - 40));
      pos.y = get_pose().y + get_radius() * sin(deg2rad(get_pose().theta - 40));
    } else {
      pos.x = get_pose().x + get_radius() * cos(deg2rad(get_pose().theta + 40));
      pos.y = get_pose().y + get_radius() * sin(deg2rad(get_pose().theta + 40));
    }
  }
}

void Predator::LoadFromObject(json_object* entity_config) {
  json_object& e_config = *entity_config;
  ArenaEntity::LoadFromObject(entity_config);

  if (e_config.find("light_behavior") != e_config.end()) {
      light_behavior_ = get_behavior_type(
        e_config["light_behavior"].get<std::string>());
  }

  if (e_config.find("food_behavior") != e_config.end()) {
      food_behavior_ = get_behavior_type(
        e_config["food_behavior"].get<std::string>());
  }

  if (e_config.find("bv_behavior") != e_config.end()) {
      bv_behavior_ = get_behavior_type(
        e_config["bv_behavior"].get<std::string>());
  }
  if (e_config.find("predator_behavior") != e_config.end()) {
      predator_behavior_ = get_behavior_type(
        e_config["predator_behavior"].get<std::string>());
  }
  UpdateLightSensors();
}

void Predator::set_bv_behavior(Behavior behavior) {
  bv_behavior_ = behavior;
  switch (behavior) {
    case kExplore:
      B_bv = new Explore();
      break;
    case kLove:
      B_bv = new Love();
      break;
    case kAggressive:
      B_bv = new Aggressive();
      break;
    case kCoward:
      B_bv = new Coward();
      break;
    case kNone:
      B_bv = new None();
      numBehaviors--;
      break;
    default:
      break;
  }
}

void Predator::set_light_behavior(Behavior behavior) {
  light_behavior_ = behavior;
  switch (behavior) {
    case kExplore:
      B_light = new Explore();
      break;
    case kLove:
      B_light = new Love();
      break;
    case kAggressive:
      B_light = new Aggressive();
      break;
    case kCoward:
      B_light = new Coward();
      break;
    case kNone:
      B_light = new None();
      numBehaviors--;
      break;
    default:
      break;
  }
}

void Predator::set_food_behavior(Behavior behavior) {
  food_behavior_ = behavior;
  switch (behavior) {
    case kExplore:
      B_food = new Explore();
      break;
    case kLove:
      B_food = new Love();
      break;
    case kAggressive:
      B_food = new Aggressive();
      break;
    case kCoward:
      B_food = new Coward();
      break;
    case kNone:
      B_food = new None();
      numBehaviors--;
      break;
    default:
      break;
  }
}

void Predator::set_predator_behavior(Behavior behavior) {
  predator_behavior_ = behavior;
  switch (behavior) {
    case kExplore:
      B_predator = new Explore();
      break;
    case kLove:
      B_predator = new Love();
      break;
    case kAggressive:
      B_predator = new Aggressive();
      break;
    case kCoward:
      B_predator = new Coward();
      break;
    case kNone:
      B_predator = new None();
      numBehaviors--;
      break;
    default:
      break;
  }
}

void Predator::ConsumeFood() {
  ts = 0;
  timestep = 0;
  bv_dec = 0;
  light_dec = 0;
  food_dec = 0;
  consumeBV = 1;
}

void Predator::getkill() {
  set_type(kGhost);
  set_color(GHOST_COLOR);
  wheel_velocity_ = WheelVelocity(0, 0);
  set_light_behavior(kNone);
  set_food_behavior(kNone);
  set_bv_behavior(kNone);
  is_dead = 1;
  bv_dec = 3;
  light_dec = 3;
  food_dec = 3;
}

NAMESPACE_END(csci3081);
