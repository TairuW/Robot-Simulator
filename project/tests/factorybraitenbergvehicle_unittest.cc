/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "src/arena.h"
#include "src/entity_type.h"
#include "src/params.h"
#include "src/pose.h"
#include "src/factory_braitenberg_vehicle.h"

 /******************************************************
* TEST FEATURE SetUp
*******************************************************/
class FactoryBraitenbergVehicleTest : public::testing::Test {

 protected:
  virtual void SetUp() {
    factory = new csci3081::FactoryBraitenbergVehicle();
    std::string json = "{\"type\":\"BraitenbergVehicle\",\"x\":270,\"y\":270,\"r\":15,\"theta\":215,\"light_behavior\":\"None\",\"food_behavior\":\"Explore\",\"bv_behavior\":\"Explore\"}";
    json_value *config = new json_value();
    std::string err = parse_json(config,json);
    bv = factory->create(&config->get<json_object>());
  }
  virtual void TearDown() {
    delete factory;
  }

  csci3081::FactoryBraitenbergVehicle *factory;
  csci3081::BraitenbergVehicle *bv;

};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(FactoryBraitenbergVehicleTest, Constructor) {
  EXPECT_EQ(bv->get_id(),1);
  //EXPECT_EQ(bv->get_name(),"BraitenbergVehicle 1");
  EXPECT_EQ(bv->get_pose().x,270);
  EXPECT_EQ(bv->get_pose().y,270);
  EXPECT_EQ(bv->get_pose().theta,215);
  EXPECT_EQ(bv->get_radius(),15);
  EXPECT_EQ(bv->get_color().r,122);
  EXPECT_EQ(bv->get_color().g,0);
  EXPECT_EQ(bv->get_color().b,25);
  EXPECT_EQ(bv->get_light_behavior(),csci3081::kNone);
  EXPECT_EQ(bv->get_food_behavior(),csci3081::kExplore);
  EXPECT_EQ(bv->get_bv_behavior(),csci3081::kExplore);
};
