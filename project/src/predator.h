/**
 * @file predator.h
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#ifndef SRC_PREDATOR_H_
#define SRC_PREDATOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/

#include <ctime>
#include <string>
#include <vector>
#include "src/common.h"
#include "src/arena_mobile_entity.h"
#include "src/motion_behavior_differential.h"
#include "src/wheel_velocity.h"
#include "src/behavior_enum.h"
#include "src/behaviors.h"
#include "src/behavior_love.h"
#include "src/behavior_explore.h"
#include "src/behavior_aggressive.h"
#include "src/behavior_coward.h"
#include "src/behavior_none.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

class GraphicsArenaViewer;
class LightDecorator;
class FoodDecorator;
class BVDecorator;

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing a mobile predator within the Arena.
 *
 * Predator can consume a Robot. If a Robot touches the Predator, it becomes
 * a ghost.
 *
 */
class Predator : public ArenaMobileEntity {
 public:
  /**
   * @brief Default constructor.
   */
  Predator();

  /**
   * Deleting the copy assignment and copy constructor. required now with
   *  inclusion of references to sensors and motion_handler/behavior
   */
  Predator(const Predator & rhs) = delete;

  Predator operator=(const Predator & rhs) = delete;

  /**
   * @brief Update the Predator's position and velocity after the
   * specified duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

  void Update() override;

  /**
   * @brief Change the movement state of the Predator.
   */
  void HandleCollision(EntityType ent_type,
                       ArenaEntity * object = NULL) override;

  void SenseEntity(const ArenaEntity& entity);

  std::string get_name() const override;

  std::vector<Pose> get_light_sensors_const() const;

  std::vector<Pose> get_light_sensors();

  void UpdateLightSensors();

  void LoadFromObject(json_object* entity_config) override;

  Behavior get_light_behavior() { return light_behavior_; }

  void set_light_behavior(Behavior behavior);

  Behavior get_food_behavior() { return food_behavior_; }

  void set_food_behavior(Behavior behavior);

  Behavior get_bv_behavior() { return bv_behavior_; }

  void set_bv_behavior(Behavior behavior);

  Behavior get_predator_behavior() { return predator_behavior_; }

  void set_predator_behavior(Behavior behavior);

  double get_sensor_reading_left(const ArenaEntity* entity);

  double get_sensor_reading_right(const ArenaEntity* entity);

  void ConsumeFood();

  void getkill();

  static int count;

  int is_dead = 0;

  int timescollision = 25;

  int timestep = 0;

  int bv_dec = 0;

  int light_dec = 0;

  int food_dec = 0;

  WheelVelocity wheel_velocity_ = WheelVelocity(0, 0);

 private:
  std::vector<Pose> light_sensors_;
  MotionBehaviorDifferential * motion_behavior_{nullptr};

  WheelVelocity light_wheel_velocity;
  WheelVelocity food_wheel_velocity;
  WheelVelocity bv_wheel_velocity;
  WheelVelocity predator_wheel_velocity;

  Behavior light_behavior_;
  Behavior food_behavior_;
  Behavior bv_behavior_;
  Behavior predator_behavior_;

  int numBehaviors = 4;

  Behaviors *B_light = new Coward();
  Behaviors *B_food{nullptr};
  Behaviors *B_bv = new Aggressive();
  Behaviors *B_predator{nullptr};

  const ArenaEntity* closest_light_entity_;
  const ArenaEntity* closest_food_entity_;
  const ArenaEntity* closest_bv_entity_;
  const ArenaEntity* closest_predator_entity_;
  double defaultSpeed_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_PREDATOR_H_
