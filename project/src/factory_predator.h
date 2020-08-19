/**
 * @file factory_predator.h
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#ifndef SRC_FACTORY_PREDATOR_H_
#define SRC_FACTORY_PREDATOR_H_

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
#include "src/predator.h"
#include "src/factory_entity.h"

NAMESPACE_BEGIN(csci3081);

/**
 * @brief A Factory to create BraitenbergVehicle
 *
 */

class FactoryPredator: public FactoryEntity {
 public:
  FactoryPredator() {}
  ~FactoryPredator() {}
  Predator* create(json_object *config) override;
  FactoryPredator(const FactoryPredator &f) = delete;
  FactoryPredator &operator=
   (const FactoryPredator *other) = delete;
};


NAMESPACE_END(csci3081);

#endif  // SRC_FACTORY_PREDATOR_H_
