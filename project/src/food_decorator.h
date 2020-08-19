/**
 * @file food_decorator.h
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#ifndef SRC_FOOD_DECORATOR_H_
#define SRC_FOOD_DECORATOR_H_
/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <iostream>
#include <string>

#include "src/food.h"
#include "src/arena_mobile_entity.h"
#include "src/motion_behavior_differential.h"
#include "src/common.h"
#include "src/entity_type.h"
#include "src/pose.h"
#include "src/predator.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);
/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class is decorator pattern for Predator
 *
 * If Predator did not consume braitenberg Vehicle for 150 iteration, it will
 * decorate into either FoodDecorator, LightDecorator, BVDecorator.
 *
 */
class FoodDecorator : public Food {
 public:
  FoodDecorator();

  explicit FoodDecorator(Predator* pre);

  FoodDecorator(const FoodDecorator & rhs) = delete;

  FoodDecorator operator=(const FoodDecorator & rhs) = delete;

  void HandleCollision(EntityType ent_type,
     ArenaEntity* object = NULL) override;

  ArenaEntity* get_internal_entity() override;

  std::string get_name() const override;

  void TimestepUpdate(unsigned int dt) override;

 protected:
  Predator* predator_{nullptr};
};

NAMESPACE_END(csci3081);

#endif  // SRC_FOOD_DECORATOR_H_
