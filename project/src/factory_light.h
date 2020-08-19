/**
 * @file factory_light.h
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#ifndef SRC_FACTORY_LIGHT_H_
#define SRC_FACTORY_LIGHT_H_

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
#include "src/light.h"
#include "src/factory_entity.h"

NAMESPACE_BEGIN(csci3081);

/**
 * @brief A Factory to create Light
 *
 */

class FactoryLight : public FactoryEntity{
 public:
  FactoryLight() {}
  ~FactoryLight() {}
  Light* create(json_object *config) override;
  FactoryLight(const FactoryLight &f) = delete;
  FactoryLight &operator = (const FactoryLight *other) = delete;
};


NAMESPACE_END(csci3081);

#endif  // SRC_FACTORY_LIGHT_H_
