/**
 * @file main.cc
 *
 * @copyright Tairu Wang, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>

#include "src/controller.h"
#include "src/graphics_arena_viewer.h"

/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
int main(__unused int argc, __unused char **argv) {
  // The controller creates both the arena and viewer
  if (argc != 4) {
    std::cout << "Incorrect Command Line Arguments" << std::endl;
    return 1;
  }
  auto *controller = new csci3081::Controller(argc, argv);

  // The controller will call Run of the viewer
  controller->Run();
  return 0;
}
