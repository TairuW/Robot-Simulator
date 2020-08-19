/**
 * @file braitenberg_vehicle.h
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#ifndef SRC_BRAITENBERG_VEHICLE_H_
#define SRC_BRAITENBERG_VEHICLE_H_

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

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Entity class to represent a Braitenberg Vehicle
 *
 * A braitenberg vehicle is a simple machine that is used to show how simple
 * concepts (in this case wiring) can give way to complex looking behavior. In
 * this simulation, Braitenberg vehicles contain sensors, which can be hooked
 * up in four different ways, and thus they can exhibit four different behaviors
 *
 */
class BraitenbergVehicle : public ArenaMobileEntity {
 public:
  /**
   * @brief Default constructor.
   */
  BraitenbergVehicle();

  /**
   * Deleting the copy assignment and copy constructor. required now with
   *  inclusion of references to sensors and motion_handler/behavior
   */
  BraitenbergVehicle(const BraitenbergVehicle & rhs) = delete;

  BraitenbergVehicle operator=(const BraitenbergVehicle & rhs) = delete;

  /**
   * @brief Update the BraitenbergVehicle's position and velocity after the
   * specified duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

  void Update() override;

  /**
   * @brief Change the movement state of the BraitenbergVehicle.
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

  double get_sensor_reading_left(const ArenaEntity* entity);

  double get_sensor_reading_right(const ArenaEntity* entity);

  void Notify(GraphicsArenaViewer* gav);

  void Subscribe(GraphicsArenaViewer* observer) {gav_obs = observer; }

  void Unsubscribe();

  void getkill();

  void ConsumeFood();

  static int count;

  int is_dead = 0;

  int timescollision = 25;

 private:
  std::vector<Pose> light_sensors_;
  MotionBehaviorDifferential * motion_behavior_{nullptr};
  WheelVelocity wheel_velocity_;
  WheelVelocity light_wheel_velocity;
  WheelVelocity food_wheel_velocity;
  WheelVelocity bv_wheel_velocity;
  Behavior light_behavior_;
  Behavior food_behavior_;
  Behavior bv_behavior_;

  int numBehaviors = 3;

  Behaviors *B_light{nullptr};
  Behaviors *B_food{nullptr};
  Behaviors *B_bv{nullptr};
  const ArenaEntity* closest_light_entity_;
  const ArenaEntity* closest_food_entity_;
  const ArenaEntity* closest_bv_entity_;
  double defaultSpeed_;
  int starve;
  int timestep;
  GraphicsArenaViewer* gav_obs{nullptr};
};

NAMESPACE_END(csci3081);

#endif  // SRC_BRAITENBERG_VEHICLE_H_
