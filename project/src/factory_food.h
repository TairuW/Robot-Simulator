/**
 * @file factory_food.h
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#ifndef SRC_FACTORY_FOOD_H_
#define SRC_FACTORY_FOOD_H_

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
#include "src/food.h"
#include "src/factory_entity.h"

NAMESPACE_BEGIN(csci3081);

/**
 * @brief A Factory to create Food
 *
 */
class FactoryFood : public FactoryEntity{
 public:
  FactoryFood() {}
  ~FactoryFood() {}
  Food* create(json_object *config) override;
  FactoryFood(const FactoryFood &f) = delete;
  FactoryFood &operator = (const FactoryFood *other) = delete;
};


NAMESPACE_END(csci3081);

#endif  // SRC_FACTORY_FOOD_H_
