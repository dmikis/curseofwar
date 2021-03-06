/******************************************************************************

  Curse of War -- Real Time Strategy Game for Linux.
  Copyright (C) 2013 Alexey Nikolaev.

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 
******************************************************************************/
#ifndef _STATE_H
#define _STATE_H

#include "common.h"
#include "grid.h"
#include "king.h"

/* 
  faster(s)
    returns a faster speed */
enum config_speed faster(enum config_speed);

/* 
  slower(s)
    returns a slower speed */
enum config_speed slower(enum config_speed);

struct ui {
  struct loc cursor;
  int xskip;
};

/*
  struct state
    
    Game state

    Members:
      grid in sthe map grid
      flag_grid[] is the array of flag grids (different for each player)
      country[] is the array of countries
      
      king is the array of AI opponents 
      kings_num is the number of AI opponents

      controlled is the player id of the human controlled player

      condiitions is the initial conditions quality (0==random, 1==best, 4==worst)

      inequality (from 0 to 4) is the level of countries' inequality 

      speed and dif are the game speed and the difficulty level
 */
struct state {
  struct grid grid;
  /* struct loc cursor; */
  struct flag_grid fg [MAX_PLAYER];
  struct king king [MAX_PLAYER];
  int kings_num;

  struct country country [MAX_PLAYER];

  unsigned long time;

  int map_seed;

  int controlled;

  int conditions;
  int inequality;

  enum config_speed speed;
  enum config_speed prev_speed;
  enum config_dif dif;
};

/*
  state_init(&s, w, h, keep_random, speed, dif)

    initializes state s.

    w and h are the map dimensions
    
    if keep_random == 1, the map is kept random,
    otherwise city and player placement is not arbitrary, 
      but players have their initial locations in the corners of the map.
      function conflict() is used to generate this game mode
 */
void state_init(struct state *s, int w, int h, enum stencil shape,
    unsigned int map_seed, int keep_random, int locations_num, int clients_num,
    int conditions, int inequality, enum config_speed speed, enum config_dif dif);

/* compute the cursor location, and xskip */
void ui_init(struct state *s, struct ui *ui);

/* 
  kings_move(&s)
    Kings build cities and place flags */

void kings_move(struct state *s);

/*
  simulate(&s)
    Performs one step of the game simulation
 */
void simulate(struct state *s);

#endif
