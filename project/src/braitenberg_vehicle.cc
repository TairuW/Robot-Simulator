/**
 * @file braitenberg_vehicle.cc
 *
 * @copyright Tairu Wang, All rights reserved.
 */
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <ctime>
#include "src/braitenberg_vehicle.h"
#include "src/params.h"
#include "src/graphics_arena_viewer.h"

class SensorLightLove;

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

int BraitenbergVehicle::count = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/

BraitenbergVehicle::BraitenbergVehicle() :
  light_sensors_(), wheel_velocity_(),
  light_wheel_velocity(), food_wheel_velocity(), bv_wheel_velocity(),
  light_behavior_(kNone), food_behavior_(kNone), bv_behavior_(kNone),
  closest_light_entity_(NULL), closest_food_entity_(NULL),
  closest_bv_entity_(NULL), defaultSpeed_(5.0), starve(0),
  timestep(0) {
  set_type(kBraitenberg);
  motion_behavior_ = new MotionBehaviorDifferential(this);
  light_sensors_.push_back(Pose());
  light_sensors_.push_back(Pose());
  set_color(BRAITENBERG_COLOR);
  set_pose(ROBOT_INIT_POS);
  set_radius(DEFAULT_RADIUS);

  light_wheel_velocity = WheelVelocity(0, 0);
  food_wheel_velocity = WheelVelocity(0, 0);
  bv_wheel_velocity = WheelVelocity(0, 0);

  wheel_velocity_ = WheelVelocity(0, 0);

  // Set ID
  count++;
  set_id(count);
}

void BraitenbergVehicle::TimestepUpdate(__unused unsigned int dt) {
  if (is_moving()) {
    motion_behavior_->UpdatePose(dt, wheel_velocity_);
  }
  timestep += 1;
  if (timestep == 600) {
    starve = 1;
    getkill();
  }
  timescollision += 1;
  if (timescollision == 20) {
    set_heading(static_cast<int>((get_pose().theta - 45)) % 360);
  }
  UpdateLightSensors();
}

void BraitenbergVehicle::HandleCollision(EntityType ent_type,
                                         ArenaEntity * object) {
  if (ent_type == kFood) {
    if (pred_ != 1) {
      ConsumeFood();
    }
  } else if (ent_type == kLight) {
    if (pred_ == 1) {
      static_cast<Predator*>(object)->getkill();
      consumeBV = 1;
    }
  } else if (ent_type == kBraitenberg) {
    if (pred_ == 1) {
      consumeBV = 1;
    } else {
      set_heading(static_cast<int>((get_pose().theta + 180)) % 360);
      timescollision = 0;
    }
  } else if (ent_type == kPredator) {
    if (pred_ != 1) {
      static_cast<Predator*>(object)->ConsumeFood();
      getkill();
    }
  } else {
    set_heading(static_cast<int>((get_pose().theta + 180)) % 360);
    timescollision = 0;
  }
}

void BraitenbergVehicle::SenseEntity(const ArenaEntity& entity) {
  const ArenaEntity** closest_entity_ = NULL;
  if (entity.get_type() == kLight) {
    closest_entity_ = &closest_light_entity_;
  } else if (entity.get_type() == kFood) {
    closest_entity_ = &closest_food_entity_;
  } else if (entity.get_type() == kBraitenberg) {
    closest_entity_ = &closest_bv_entity_;
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

void BraitenbergVehicle::Update() {
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

  if (numBehaviors) {
    if (timestep >= 500) {
      if (light_wheel_velocity.left != 0 && food_wheel_velocity.left != 0) {
        wheel_velocity_ = WheelVelocity(
          food_wheel_velocity.left, food_wheel_velocity.right, defaultSpeed_);
      }
    } else {
      wheel_velocity_ = WheelVelocity(
        (light_wheel_velocity.left + food_wheel_velocity.left +
           bv_wheel_velocity.left)/numBehaviors,
        (light_wheel_velocity.right + food_wheel_velocity.right +
           bv_wheel_velocity.right)/numBehaviors,
        defaultSpeed_);
    }
  } else {
    wheel_velocity_ = WheelVelocity(0, 0);
  }
  if (light_behavior_ != kNone && food_behavior_ != kNone) {
    set_color(RgbColor(kMaroon));
  } else if (light_behavior_ != kNone && food_behavior_ == kNone) {
    set_color(RgbColor(kGold));
  } else if (light_behavior_ == kNone && food_behavior_ != kNone) {
    set_color(RgbColor(kBlue));
  }
  this->Notify(gav_obs);
}

std::string BraitenbergVehicle::get_name() const {
  if (is_dead == 1) {
    return "Ghost";
  } else {
    return "Braitenberg " + std::to_string(get_id());
  }
}

std::vector<Pose> BraitenbergVehicle::get_light_sensors_const() const {
  return light_sensors_;
}

std::vector<Pose> BraitenbergVehicle::get_light_sensors() {
  return light_sensors_;
}

double BraitenbergVehicle::get_sensor_reading_left(const ArenaEntity* entity) {
  if (entity) {
    return 1800.0/std::pow(
      1.08, (entity->get_pose()-light_sensors_[0]).Length());
  }

  return 0.0001;
}

double BraitenbergVehicle::get_sensor_reading_right(const ArenaEntity* entity) {
  if (entity) {
    return 1800.0/std::pow(
      1.08, (entity->get_pose()-light_sensors_[1]).Length());
  }

  return 0.0001;
}

void BraitenbergVehicle::UpdateLightSensors() {
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

void BraitenbergVehicle::set_bv_behavior(Behavior behavior) {
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

void BraitenbergVehicle::set_light_behavior(Behavior behavior) {
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

void BraitenbergVehicle::set_food_behavior(Behavior behavior) {
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

void BraitenbergVehicle::LoadFromObject(json_object* entity_config) {
  json_object& e_config = *entity_config;
  ArenaEntity::LoadFromObject(entity_config);

  if (e_config.find("light_behavior") != e_config.end()) {
      light_behavior_ = get_behavior_type(
        e_config["light_behavior"].get<std::string>());
      set_light_behavior(light_behavior_);
  }

  if (e_config.find("food_behavior") != e_config.end()) {
      food_behavior_ = get_behavior_type(
        e_config["food_behavior"].get<std::string>());
      set_food_behavior(food_behavior_);
  }

  if (e_config.find("bv_behavior") != e_config.end()) {
      bv_behavior_ = get_behavior_type(
        e_config["bv_behavior"].get<std::string>());
      set_bv_behavior(bv_behavior_);
  }
  if (is_dead != 1) {
    Update();
  }
  UpdateLightSensors();
}

void BraitenbergVehicle::Notify(GraphicsArenaViewer* gav) {
  if (gav != NULL) {
    gav->OnUpdate(light_wheel_velocity, food_wheel_velocity, bv_wheel_velocity);
  }
}

void BraitenbergVehicle::Unsubscribe() {
  gav_obs = NULL;
}

void BraitenbergVehicle::getkill() {
  set_type(kGhost);
  set_color(GHOST_COLOR);
  wheel_velocity_ = WheelVelocity(0, 0);
  set_light_behavior(kNone);
  set_food_behavior(kNone);
  set_bv_behavior(kNone);
  is_dead = 1;
}

void BraitenbergVehicle::ConsumeFood() {
  timestep = 0;
}


NAMESPACE_END(csci3081);
