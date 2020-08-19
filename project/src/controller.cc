/**
 * @file controller.cc
 *
 * @copyright Tairu Wang, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include <string>
#include <fstream>
#include <streambuf>
#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>

#include "src/common.h"
#include "src/controller.h"
#include "src/graphics_arena_viewer.h"
#include "src/light.h"
#include "src/food.h"
#include "src/braitenberg_vehicle.h"
#include "src/predator.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

Controller::Controller(int argc, char **argv) :
  last_dt(0), viewers_(), config_(NULL) {
  if (argc > 1) {
    std::ifstream t(std::string(argv[3]).c_str());
    std::string str((std::istreambuf_iterator<char>(t)),
                   std::istreambuf_iterator<char>());
    std::string json = str;
    config_ = new json_value();
    if (strstr(argv[3], "csv")) {
      json = parse_csv(argc, argv);
    }
    std::string err = parse_json(config_, json);
    if (json == "1") {
      std::cerr << "Parse error: " << err << std::endl;
      delete config_;
      config_ = NULL;
    }

    if (!err.empty()) {
      std::cerr << "Parse error: " << err << std::endl;
      delete config_;
      config_ = NULL;
    } else {
      x_dim_ = atoi(argv[1]);
      y_dim_ = atoi(argv[2]);
      arena_ = new Arena(&config_->get<json_object>(), x_dim_, y_dim_);
    }
  }
  if (!config_) {
    arena_ = new Arena();
  }
}

Controller::~Controller() {
  if (config_) {
    delete config_;
  }
  for (unsigned int f = 0; f < viewers_.size(); f++) {
    delete viewers_[f];
  }
}

ArenaViewer* Controller::CreateViewer(int width, int height) {
  return new GraphicsArenaViewer(width, height, this);
}

void Controller::Run() {
  viewers_.push_back(CreateViewer(arena_->get_x_dim(), arena_->get_y_dim()));
  for (unsigned int f = 0; f < viewers_.size(); f++) {
    viewers_[f]->SetArena(arena_);
  }

  for (unsigned int f = 0; f < viewers_.size(); f++) {
    viewer_ = viewers_[f];
    if (viewer_->RunViewer()) {
      break;
    }
  }
}

void Controller::AdvanceTime(double dt) {
  if ((last_dt + dt) <= .05) {
    last_dt += dt;
    return;
  }
  last_dt = 0;
  arena_->AdvanceTime(dt);
}


void Controller::Reset() {
  Light::count = 0;
  Food::count = 0;
  BraitenbergVehicle::count = 0;
  Predator::count = 0;

  if (arena_) {
    delete (arena_);
  }
  if (config_) {
    arena_ = new Arena(&config_->get<json_object>(), x_dim_, y_dim_);
  } else {
    arena_ = new Arena();
  }
  viewer_->SetArena(arena_);
}


std::string Controller::parse_csv(int argc, char **argv) {
  // Expecting argv[4] arguments:
  // [1] and [2]: x,y dimensions of graphics window
  // [3]: config filename
  if (argc != 4) {
    std::cout << "Incorrect Command Line Arguments" << std::endl;
    // return 1;
  }
  try {
    // a word parsed from csv row
    std::string token;

    // all column labels of csv -- correspond to json keys (e.g. "type")
    std::vector<std::string> keys;

    // read the file that was passed in as argument
    std::ifstream fin(argv[3]);

    // pull first row of column headings
    std::string labels;
    fin >> labels;

    // Save these as the keys that are put into the json string.
    // These include "type" "x" "robot_behavior" etc.
    std::istringstream ss(labels);
    while (std::getline(ss, token, ',')) {
      keys.push_back(token);
    }

    // Start the json configuration string with { "entities": ["
    std::string entities = "{ \"entities\": [\n";

    // read and parse csv file line-by-line
    // convert each line to json entity row and add to entities ...
    /*  for example, using keys from first row, convert
    Braitenberg,220,400,15,270.0,Love,Aggressive,Coward
        to
    {"type": "Braitenberg", "x":220, "y":400, "r":15, "theta": 270.0,
    "light_behavior": "Love", "food_behavior": "Aggressive",
    "bv_behavior": "Coward" }
    */

    std::string entity_json;  // populate below by converting csv row to json
    std::string row;          // temp holder of csv row
    std::vector<std::string> words;   // all words parsed from csv row

    // while more rows to parse and convert ...
    while (fin >> row) {
      // parse into separate words (separated by commas)
      ss = std::istringstream(row);
      words.clear();
      while (std::getline(ss, token, ',')) {
        words.push_back(token);
      }
      // combine each key with associated word into json row
      // for example: "type" : "Braitenberg" or "x":220
      int keys_index = 0;
      entity_json = "     {";
      for (auto word : words) {
        if (keys_index != 0) { entity_json += ","; }
        entity_json += add_quotes(keys[keys_index]) + ":";
        if (in_number_set(keys[keys_index])) {
          entity_json += word;
        } else {
          entity_json += add_quotes(word);
        }
        ++keys_index;
      }
      entity_json += "}";
      entities += entity_json + ",\n";
    }

    // Erase last comma added to entities
    entities = entities.substr(0, entities.length()-2);

    // Close out the entities array and json string
    entities += "\n  ]\n}";

    // Let's see what we made ...
    std::cout << entities << std::endl;
    //
    // // Here it is in a file if you want to save it ...
    // std::ofstream out("output.json");
    // out << entities;
    // out.close();
    return entities;
  }
  catch(const std::exception& e) {
    std::cout << "Incorrect Format of CSV file" << std::endl;
  }
  return "1";
}
// Add quotes around the string
std::string Controller::add_quotes(std::string word) {
  std::string quoted_string("\"");
  quoted_string += (word + "\"");
  return quoted_string;
}

// To determine if quotes should be put around the parsed word
inline bool Controller::in_number_set(std::string word) {
  // compare returns 0 when it matches the word
  return !(
    word.compare("x") && word.compare("y")
    && word.compare("r") && word.compare("theta") );
}

NAMESPACE_END(csci3081);
