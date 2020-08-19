/**
 * @file factory_ghost.h
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#ifndef SRC_FACTORY_GHOST_H_
#define SRC_FACTORY_GHOST_H_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>

#include "src/common.h"
#include "src/entity_type.h"
#include "src/params.h"
#include "src/pose.h"
#include "src/rgb_color.h"
#include "src/arena_entity.h"
#include "src/ghost.h"
#include "src/factory_entity.h"

NAMESPACE_BEGIN(csci3081);

/**
 * @brief A Factory to create ghost
 *
 */
class FactoryGhost : public FactoryEntity{
 public:
  FactoryGhost() {}
  ~FactoryGhost() {}
  Ghost* create(json_object *config) override;
  FactoryGhost(const FactoryGhost &f) = delete;
  FactoryGhost &operator = (const FactoryGhost *other) = delete;
};


NAMESPACE_END(csci3081);

#endif  // SRC_FACTORY_GHOST_H_
