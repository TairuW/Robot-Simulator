/**
 * @file light.cc
 *
 * @copyright Tairu Wang, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include "src/light.h"
#include "src/params.h"
#include "src/braitenberg_vehicle.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

int Light::count = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Light::Light() :
    motion_behavior_(this) {
  set_color(LIGHT_COLOR);
  set_pose(LIGHT_POSITION);
  if (pred_ == 1) {
    set_radius(DEFAULT_RADIUS);
  } else {
    set_radius(LIGHT_RADIUS);
  }
  set_type(kLight);
  set_speed(3);

  // Set ID
  count++;
  set_id(count);
}

void Light::HandleCollision(EntityType ent_type,
                               ArenaEntity * object) {
  // set_heading(random_num<float>(0, 360));
  if (ent_type == kBraitenberg) {
    if (pred_ == 1) {
      static_cast<BraitenbergVehicle*>(object)->getkill();
      consumeBV = 1;
    }
  } else {
    set_heading(static_cast<int>((get_pose().theta + 180)) % 360);
  }
}

void Light::TimestepUpdate(__unused unsigned int dt) {
  if (is_moving()) {
      Pose pose = get_pose();

      // Movement is always along the heading_angle (i.e. the hypotenuse)
      double new_x =
        pose.x + std::cos(pose.theta * M_PI / 180.0) * get_speed() * dt;
      double new_y =
        pose.y + std::sin(pose.theta * M_PI / 180.0) * get_speed() * dt;

      /* Heading angle remaings the same */
      pose.x = new_x;
      pose.y = new_y;
      set_pose(pose);
  }

  Update();
}

NAMESPACE_END(csci3081);
