//  SuperTux
//  Copyright (C) 2006 Matthias Braun <matze@braunis.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef HEADER_SUPERTUX_SCRIPTING_FUNCTIONS_HPP
#define HEADER_SUPERTUX_SCRIPTING_FUNCTIONS_HPP

#ifndef SCRIPTING_API
#include <squirrel.h>
#include <string>
#include "util/sqarrayser.hpp"
#include "squirrel_error.hpp"
#define __suspend
#define __custom(x)
#endif

namespace scripting {

/**
 * Display the value of the argument. This is useful for inspecting tables.
 * @scripting
 */
SQInteger display(HSQUIRRELVM vm) __custom("t.");

/**
 * Displays contents of the current stack
 * @scripting
 */
SQInteger print_stacktrace(HSQUIRRELVM vm);

/**
 * returns the currently running thread
 * @scripting
 */
SQInteger get_current_thread(HSQUIRRELVM vm) __custom("t");

/**
 * Should use christmas mode
 * @scripting
 */
SQInteger is_christmas(HSQUIRRELVM vm) __custom("t");

/**
 * Display a text file and scrolls it over the screen (on next screenswitch)
 * @scripting
 */
void display_text_file(const std::string& filename);

/**
 * Load and display a worldmap (on next screenswitch)
 * @scripting
 */
void load_worldmap(const std::string& filename);

/**
 * Load and display a level (on next screenswitch)
 * @scripting
 */
void load_level(const std::string& filename);

/**
 * Suspend the script execution for the specified number of seconds
 * @scripting
 */
SQInteger wait(HSQUIRRELVM vm) ;

/**
 * Suspend the script execution until the current screen has been changed
 * @scripting
 */
SQInteger wait_for_screenswitch(HSQUIRRELVM vm) __suspend;

/**
 * Exits the currently running screen (force exit from worldmap or scrolling
 * text for example)
 * @scripting
 */
void exit_screen();

/**
 * Does a fadeout for the specified number of seconds before next screenchange
 * @scripting
 */
void fadeout_screen(float seconds);

/**
 * Does a shrinking fade towards the destposition for the specified number of
 * seconds before next screenchange
 * @scripting
 */
void shrink_screen(float dest_x, float dest_y, float seconds);

/**
 * Aborts any kind of previous screen fade; the screenchange will happen
 * anyway.
 * @scripting
 */
void abort_screenfade();

/**
 * Translate a text into the users language (by looking it up in the .po
 * files)
 * @scripting
 */
std::string translate(const std::string& text);
/**
 * @scripting
 */
std::string _(const std::string& text);

/**
 * Load a script file and executes it. This is typically used to import
 * functions from external files.
 * @scripting
 */
 SQInteger import(HSQUIRRELVM vm);
/**
 * Save world state to scripting table
 * @scripting
 */
void save_state();

/**
 * Load world state from scripting table
 * @scripting
 */
void load_state();

/**
 * enable/disable drawing of collision rectangles
 * @scripting
 */
void debug_collrects(bool enable);

/**
 * enable/disable drawing of fps
 * @scripting
 */
void debug_show_fps(bool enable);

/**
 * enable/disable drawing of non-solid layers
 * @scripting
 */
void debug_draw_solids_only(bool enable);

/**
 * enable/disable drawing of editor images
 * @scripting
 */
void debug_draw_editor_images(bool enable);

/**
 * enable/disable worldmap ghost mode
 * @scripting
 */
void debug_worldmap_ghost(bool enable);

/**
 * Changes music to musicfile
 * @scripting
 */
void play_music(const std::string& musicfile);

/**
 * Plays a soundfile
 * @scripting
 */
void play_sound(const std::string& soundfile);

/**
 *  Set the game_speed
 * @scripting
 */
void set_game_speed(float speed);

/**
 * speeds Tux up
 * @scripting
 */
void grease();

/**
 * makes Tux invincible for 10000 units of time
 * @scripting
 */
void invincible();

/**
 * makes Tux a ghost, i.e. lets him float around and through solid objects
 * @scripting
 */
void ghost();

/**
 * recall Tux's invincibility and ghost status
 * @scripting
 */
void mortal();

/**
 * reinitialise and respawn Tux at the beginning of the current level
 * @scripting
 */
void restart();

/**
 * print Tux's current coordinates in a level
 * @scripting
 */
void whereami();

/**
 * move Tux near the end of the level
 * @scripting
 */
void gotoend();

/**
 * move Tux to the X and Y blocks relative to his position
 * @scripting
 */
void warp(float offset_x, float offset_y);

/**
 * show the camera's coordinates
 * @scripting
 */
void camera();

/**
 * adjust gamma
 * @scripting
 */
void set_gamma(float gamma);

/**
 * exit the game
 * @scripting
 */
void quit();

/**
 * Returns a random integer
 * @scripting
 */
int rand();

/**
 * Record a demo to the given file.
 * @scripting
 */
void record_demo(const std::string& filename);

/**
 * Play back a demo from the given file.
 * @scripting
 */
void play_demo(const std::string& filename);

/**
 * Declare function for storing variables
 * @scripting
 */
 SQInteger store(HSQUIRRELVM vm) __custom("t..");
 /**
  * @scripting
  */
 SQInteger load(HSQUIRRELVM vm) __custom("ts");
} // namespace scripting

#endif

/* EOF */
