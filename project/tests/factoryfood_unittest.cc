/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "src/arena.h"
#include "src/entity_type.h"
#include "src/params.h"
#include "src/food.h"
#include "src/pose.h"
#include "src/factory_food.h"

 /******************************************************
* TEST FEATURE SetUp
*******************************************************/
class FactoryFoodTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
    factory = new csci3081::FactoryFood();
    std::string json = "{\"type\":\"Food\",\"x\":270,\"y\":270}";
    json_value* config = new json_value();
    std::string err = parse_json(config,json);
    food = factory->create(&config->get<json_object>());
  }
  virtual void TearDown() {
    delete factory;
  }

  csci3081::FactoryFood *factory;
  csci3081::Food *food;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(FactoryFoodTest, Constructor) {
  EXPECT_EQ(food->get_id(),1);
  //EXPECT_EQ(food->get_name(),"Food");
  EXPECT_EQ(food->get_pose().x,270);
  EXPECT_EQ(food->get_pose().y,270);
  EXPECT_EQ(food->get_color().r,0);
  EXPECT_EQ(food->get_color().g,255);
  EXPECT_EQ(food->get_color().b,0);
};
