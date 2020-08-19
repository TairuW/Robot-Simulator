/**
 * @file ghost.cc
 *
 * @copyright Tairu Wang, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/ghost.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

// int Ghost::count = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
Ghost::Ghost() : ArenaImmobileEntity() {
  set_type(kGhost);
  set_color(GHOST_COLOR);
  // set_pose(GHOST_INIT_POS);
  set_radius(GHOST_RADIUS);

  // Set ID
  // count++;
  // set_id(count);
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
// void Ghost::Reset() {
//   set_pose(GHOST_INIT_POS);
// } /* Reset */

NAMESPACE_END(csci3081);
