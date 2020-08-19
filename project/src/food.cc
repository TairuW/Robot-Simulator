/**
 * @file food.cc
 *
 * @copyright Tairu Wang, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/food.h"
#include "src/params.h"
#include "src/braitenberg_vehicle.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

int Food::count = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Food::Food() : ArenaMobileEntity() {
  set_type(kFood);
  set_color(FOOD_COLOR);
  set_pose(FOOD_INIT_POS);
  if (pred_ == 1) {
    set_radius(DEFAULT_RADIUS);
  } else {
    set_radius(FOOD_RADIUS);
  }

  // Set ID
  count++;
  set_id(count);
}

void Food::HandleCollision(EntityType ent_type,
                               ArenaEntity * object) {
  if (ent_type == kBraitenberg) {
    if (pred_ == 1) {
      static_cast<BraitenbergVehicle*>(object)->getkill();
      consumeBV = 1;
    }
  }
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void Food::Reset() {
  set_pose(FOOD_INIT_POS);
} /* Reset */

NAMESPACE_END(csci3081);
