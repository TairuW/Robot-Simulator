/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <gtest/gtest.h>
#include "src/arena.h"
#include "src/entity_type.h"
#include "src/params.h"

 /******************************************************
* TEST FEATURE SetUp
*******************************************************/
class ArenaTest : public ::testing::Test {

 protected:
  virtual void SetUp() {
    arena = new csci3081::Arena();
  }
  virtual void TearDown() {
    delete arena;
  }

  csci3081::Arena * arena;

};

/*******************************************************************************
 * Test Cases
 ******************************************************************************/

TEST_F(ArenaTest, Constructor) {
  EXPECT_EQ(arena->get_x_dim(), X_DIM);
  EXPECT_EQ(arena->get_y_dim(), Y_DIM);
  EXPECT_GE((int)arena->get_entities().size(), 3) << "FAIL: Arena:Constructor - There should be at least 3 entities";
};
