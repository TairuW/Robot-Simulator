/**
 * @file controller.h
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#ifndef SRC_CONTROLLER_H_
#define SRC_CONTROLLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include <string>
#include <iostream>
#include <cstring>
#include <fstream>
#include <sstream>
#include <vector>

#include "src/arena.h"
#include "src/common.h"
#include "src/arena_viewer.h"
#include "src/params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Controller that mediates Arena and GraphicsArenaViewer communication.
 *
 * The Controller instantiates the Arena and the GraphicsArenaViewer. The
 * viewer contains the main loop that keeps it live, but at each update, the
 * viewer sends a message to the controller to update its time.
 *
 * Other types of communication between Arena and Viewer include:
 * - keypresses intercepted by the Viewer.
 * - Play/Pause/New Game user input via the Viewer.
 * - Game status from arena to the viewer.
 **/
class Controller {
 public:
  /**
   * @brief Controller's constructor that will create Arena and Viewer.
   */
  Controller(int argc, char **argv);

  // Controller(Const &);
  Controller(const Controller &other);
  virtual ~Controller();

  virtual ArenaViewer* CreateViewer(int width, int height);

  /**
   * @brief Run launches the graphics and starts the game.
   */
  void Run();

  /**
   * @brief AdvanceTime is communication from the Viewer to advance the
   * simulation.
   */
  void AdvanceTime(double dt);

  std::string parse_csv(int argc, char **argv);

  /**
   * @brief add_quotes is Add quotes around the string
   */
  std::string add_quotes(std::string word);

  /**
   * @brief in_number_set is To determine if quotes should be put around
   * the parsed word
   */
  inline bool in_number_set(std::string word);

  /**
  * @brief Completely destroy and remake the arena
  */
  void Reset();

  Controller &operator=(const Controller &other) = delete;

 private:
  double last_dt{0};
  Arena* arena_{nullptr};
  ArenaViewer* viewer_{nullptr};
  std::vector<ArenaViewer*> viewers_;
  json_value* config_;
  int x_dim_ = 0;
  int y_dim_ = 0;
};

NAMESPACE_END(csci3081);

#endif  // SRC_CONTROLLER_H_
