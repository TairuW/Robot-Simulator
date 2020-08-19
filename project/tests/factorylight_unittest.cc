/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "src/arena.h"
#include "src/entity_type.h"
#include "src/params.h"
#include "src/light.h"
#include "src/pose.h"
#include "src/factory_light.h"


 /******************************************************
* TEST FEATURE SetUp
*******************************************************/
class FactoryLightTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
    factory = new csci3081::FactoryLight();
    std::string json = "{\"type\":\"Food\",\"x\":270,\"y\":270}";
    json_value* config = new json_value();
    std::string err = parse_json(config,json);
    light = factory->create(&config->get<json_object>());
  }
  virtual void TearDown() {
    delete factory;
  }

  csci3081::FactoryLight *factory;
  csci3081::Light *light;

};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(FactoryLightTest, Constructor) {
  EXPECT_EQ(light->get_id(),1);
  //EXPECT_EQ(light->get_name(), "Light");
  EXPECT_EQ(light->get_pose().x,270);
  EXPECT_EQ(light->get_pose().y,270);
  EXPECT_EQ(light->get_color().r,255);
  EXPECT_EQ(light->get_color().g,255);
  EXPECT_EQ(light->get_color().b,255);

};
