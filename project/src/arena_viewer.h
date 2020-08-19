/**
 * @file arena_viewer.h
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#ifndef SRC_ARENA_VIEWER_H_
#define SRC_ARENA_VIEWER_H_

#include "src/arena.h"

NAMESPACE_BEGIN(csci3081);

/**
 * @brief A viewer of the positions of the Arena
 *
 */

class ArenaViewer {
 public:
  virtual ~ArenaViewer() {}
  virtual bool RunViewer() = 0;
  virtual void SetArena(Arena* arena) = 0;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_VIEWER_H_
