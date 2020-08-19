/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "src/arena.h"
#include "src/entity_type.h"
#include "src/params.h"
#include "src/pose.h"
#include "src/behaviors.h"
#include "src/wheel_velocity.h"

 /******************************************************
* TEST FEATURE SetUp
*******************************************************/
class LoveTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    behavior = new csci3081::Love();
    wv = new csci3081::WheelVelocity(0, 0);
    behavior->getwheelvelocity(5.0, 2.0, 5.0, wv);
  }
  virtual void TearDown() {
    delete behavior;
    delete wv;
  }

  csci3081::Behaviors* behavior;
  csci3081::WheelVelocity* wv;
};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(LoveTest, Constructor) {
  EXPECT_EQ(wv->left,0.2);
  EXPECT_EQ(wv->right,0.5);
};
