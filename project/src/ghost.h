/**
 * @file ghost.h
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#ifndef SRC_GHOST_H_
#define SRC_GHOST_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>

#include "src/arena_immobile_entity.h"
#include "src/common.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing a immobile ghost within the Arena.
 *
 */
class Ghost : public ArenaImmobileEntity {
 public:
  /**
   * @brief Constructor.
   *
   * @param params A ghost_params passed down from main.cc for the
   * initialization of the Ghost.
   */
  Ghost();

  // void Reset() override;

  /**
   * @brief Only thing necessary is to update any subscribered sensors
   */
  void TimestepUpdate(__unused unsigned int dt) override {
    Update();
  }

  /**
   * @brief Get the name of the ghost for visualization purposes, and to
   * aid in debugging.
   *
   * @return Name of the ghost.
   */
  std::string get_name() const override { return "Ghost"; }

  // static int count;

 private:
};

NAMESPACE_END(csci3081);

#endif  // SRC_GHOST_H_
