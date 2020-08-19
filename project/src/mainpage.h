/**
 * @file mainpage.h
 *
 * @copyright Tairu Wang, All rights reserved.
 */

#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_

/*! \mainpage CSCI3081 Braitenberg Vehicle Simulator Project
 *
 * \section intro_sec Introduction
 *
 * Project Iteration 2 Base Code: Feature enhancements include the additions of
 * a Predator class that can consume Braitenberg Vehicles, Braitenberg Vehicle
 * sensors with a corresponding behavior so that robots react to robots, output
 * of wheel velocity information to better understand behavior, factories for
 * entity creation that do not use JSON, robots that can starve, and a weighted
 * function for determining wheel velocity. As I develop and refactor my code,
 * I employed the Factory Pattern to initialize entities, the Strategy Pattern
 * to implement the 4 behaviors (and write unit tests), and the Observer pattern
 * to view wheel velocities.
*
*
*
* \section design_doc Design Document
*
*
* \subsection factory_pattern Factory pattern
*
Instead of creating entities instantially, use Factory Patterns that grabs
entites from factory classes to make the project more dimensional.
- Factories
    - FactoryEntity – A Factory to create different entity
    - FactoryBraitenbergVehicle – A Factory to create BraitenbergVehicle
    - FactoryPredator – A Factory to create Predator
    - FactoryFood – A Factory to create Food
    - FactoryLight – A Factory to create Light
*
*
* \subsection strategy_pattern Strategy pattern

For the strategy pattern, instead of using switch statements, I created the
Behaviors class in order to get the wheel velocity. The update function is
called every time step for every arena mobile entity, so that the switch
statement is called every time, which is duplicate code and useless work that
slows the program. Using strategy pattern instead, the switch statement is only
called when the behavior is changed, which saves time and process.

- Behaviors - behaviors for ArenaMobileEntity
    - Aggressive Class
    - Coward Class
    - Love Class
    - None Class
*
* \subsection observer_pattern Observer pattern
Add Notify, Subscribe, Unsubscribe functions in the braitenberg_vehicle file.

Add Onupdate function in the braitenberg_vehicle file.

These functions corresponding to show the WheelVelocity of BraitenbergVehicle in
the control pannel.
*
*
*
* \subsection decorator_pattern Decorator pattern
*
For Decorator pattern, I used aggregation. I created 3 decorator classes,
FoodDecorator inherit from Food, LightDecorator inherit from Light, BVDecorator
inherit from BraitenbergVehicle. I override TimesUpdate(), HandleCollision()
functions inside each Decorator class.

Pros: the default setting of decorator do not need to be implement, less coding.

Cons: more complex when redecorate entities than using inherit class from
predator.
*
*
*
*
*
* \section structure_doc System Structure
*
*
Braitenberg Vehicle Simulator’s system structure consist of many different
classes, they are listed below with small summary stating what they are.
All the different type of entities in the arena are:
- Entities
    - ArenaEntity – An abstract class that provides a basic interface for all
      the different types of entities that can be present in the arena.
    - ArenaImmobileEntity – An abstract class that provides a basic interface
      for all the immobile entities that can be present in the arena. Food and
      Ghost classes inherit from this class.
    - ArenaMobileEntity – An abstract class that provides a basic interface for
      all the mobile entities that can be present in the arena. Light, Predator,
      BraitenbergVehicle classes inherit from this class.
    - BraitenbergVehicle – A mobile entity that has various behaviors.
    - Light – A mobile entity.
    - Predator – A mobile entity that consume BraitenbergVehicle.
    - Food – A immobile entity that can be consumed by BraitenbergVehicle.
*
*
*
*/
#endif  // SRC_MAINPAGE_H_
