/**
 * @file factory_entity.h
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#ifndef SRC_FACTORY_ENTITY_H_
#define SRC_FACTORY_ENTITY_H_

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
NAMESPACE_BEGIN(csci3081);

/**
 * @brief A Factory Pattern to create different entities
 *
 */
class FactoryEntity {
 public:
  FactoryEntity() {}
  virtual ~FactoryEntity() {}
  virtual ArenaEntity* create(json_object *config) = 0;
  FactoryEntity(const FactoryEntity &f) = delete;
  FactoryEntity &operator = (const FactoryEntity *other) = delete;

  int getNum_Braitenberg() { return num_Braitenberg_; }
  int getNum_Food() { return num_Food_; }
  int getNum_Light() { return num_Light_; }
  int getNum_Predator() { return num_Predator_; }
  int getNum_Ghost() { return num_Ghost_; }

  int num_Food_ = 0;
  int num_Light_ = 0;
  int num_Braitenberg_ = 0;
  int num_Predator_ = 0;
  int num_Ghost_ = 0;
};


NAMESPACE_END(csci3081);

#endif  // SRC_FACTORY_ENTITY_H_
