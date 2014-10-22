#include <ncurses.h>
#include "show_map.h"
#include "common.h"
#include <stdbool.h>

void screen_init (void)
{
        initscr ();
        noecho ();
        cbreak ();
        keypad (stdscr, TRUE);
        refresh ();
}

void set_map_frame(struct maze *created_maze)
{
	int x=0,y=0;
	for(y=0;y < created_maze->maze_dimension.alloc[0]*2+1;y++)
	{
		for(x=0;x < created_maze->maze_dimension.alloc[1]*2+1;x++)
		{
			mvaddch(y,x,' ' | A_REVERSE);
			refresh();
		}
	}
	for(y=1;y < created_maze->maze_dimension.alloc[0]*2+1;y++)
	{
		for(x=0;x < created_maze->maze_dimension.alloc[1]*2;x++)
			if((x%2) && (y%2))
				{mvaddch(y,x,' ');refresh();}
	}
	refresh();
}

bool show_map_main(struct maze *created_maze)
{
	set_map_frame(created_maze);
	struct maze_koord current_pos;

	current_pos.x=created_maze->maze_dimension.start[1];
	current_pos.y=created_maze->maze_dimension.start[0];
	int lane_counter=current_pos.lane_counter=check_multiple_lane(created_maze,current_pos);
	set_unit_visited(created_maze, current_pos);
	recursive_program(created_maze, current_pos, lane_counter);
}
void recursive_program(struct maze *created_maze, struct maze_koord beginning_pos, int counter)
{
	struct maze_koord next_pos,current_pos=beginning_pos;int temp_counter;
	bool kontrol=true;
	while(kontrol)
	{
		kontrol=all_map_kontrol(created_maze);
		while(1)//exploitation
		{
			next_pos=select_new_koord(created_maze, current_pos);
			if(next_pos.x==-1)
				return;
			if(temp_counter==0)
				return;
			connect_map_units(created_maze, current_pos, next_pos);
			set_unit_visited(created_maze,next_pos);
			temp_counter=check_multiple_lane(created_maze,next_pos);
			if(temp_counter>1)
			{
				temp_counter--;
				current_pos=next_pos;
				recursive_program(created_maze, current_pos, temp_counter);
			}
			else if (temp_counter == 1)
			{
				current_pos=next_pos;
				continue;
			}
		}
	}
}
bool all_map_kontrol(struct maze *created_maze)
{
	int x=1,y=1;bool kontrol=false;
	for(y=1;y < created_maze->maze_dimension.alloc[0]-1; y++)
	{
		for(x =1; x < created_maze->maze_dimension.alloc[1]-1 ; x++)
		{
			if(!created_maze->unit[y][x].visited)
				kontrol=true;
		}
	}
	return kontrol;
}
struct maze_koord connect_map_units(struct maze *created_maze, struct maze_koord current_pos, struct maze_koord next_pos)
{
	switch(next_pos.x-current_pos.x)
	{
		case -1:
		{
			mvaddch(current_pos.y*2+1,current_pos.x*2,' ');refresh();
		}break;
		case 1:
		{
			mvaddch(current_pos.y*2+1,current_pos.x*2+2,' ');refresh();
		}break;
		case 0:
		{
			switch(next_pos.y-current_pos.y)
			{
				case -1:
				{
					mvaddch(current_pos.y*2,current_pos.x*2+1,' ');refresh();
				}break;
				case 1:
				{
					mvaddch(current_pos.y*2+2,current_pos.x*2+1,' ');refresh();
				}break;
			}
		}
	}
	refresh();
}

void set_unit_visited(struct maze *created_maze, struct maze_koord current_pos)
{
	created_maze->unit[current_pos.y][current_pos.x].visited=true;
}
struct maze_koord select_new_koord(struct maze *created_maze, struct maze_koord current_pos)
{
	struct maze_koord next_koord;
	if(current_pos.x-1 > 0)
                if(!created_maze->unit[current_pos.y][current_pos.x-1].visited)
                {
                        if(!created_maze->unit[current_pos.y][current_pos.x-1].right)
                                if(!created_maze->unit[current_pos.y][current_pos.x].left)
                                        {
						next_koord=current_pos;
						next_koord.x=current_pos.x-1;
						return next_koord;
					}
                }
	if(current_pos.x+1 < created_maze->maze_dimension.alloc[1]-1)
                if(!created_maze->unit[current_pos.y][current_pos.x+1].visited)
                {
                        if(!created_maze->unit[current_pos.y][current_pos.x+1].left)
                                if(!created_maze->unit[current_pos.y][current_pos.x].right)
                                        {
                                                next_koord=current_pos;
                                                next_koord.x=current_pos.x+1;
						return next_koord;
                                        }
                }
	if(current_pos.y-1 > 0)
                if(!created_maze->unit[current_pos.y-1][current_pos.x].visited)
                {
                        if(!created_maze->unit[current_pos.y-1][current_pos.x].down)
                                if(!created_maze->unit[current_pos.y][current_pos.x].up)
                                        {
                                                next_koord=current_pos;
                                                next_koord.y=current_pos.y-1;
						return next_koord;
                                        }
                }
	if(current_pos.y+1 < created_maze->maze_dimension.alloc[0]-1)
                if(!created_maze->unit[current_pos.y+1][current_pos.x].visited)
                {
                        if(!created_maze->unit[current_pos.y+1][current_pos.x].up)
                                if(!created_maze->unit[current_pos.y][current_pos.x].down)
                                        {
                                                next_koord=current_pos;
                                                next_koord.y=current_pos.y+1;
						return next_koord;
                                        }
                }

	next_koord=current_pos;
	next_koord.x=-1;
	return next_koord;
}

int check_multiple_lane(struct maze *created_maze, struct maze_koord current_pos)
{
	int counter=0;

	if(!created_maze->unit[current_pos.y][current_pos.x].right)
		if(!created_maze->unit[current_pos.y][current_pos.x+1].visited)
		counter++;
	if(!created_maze->unit[current_pos.y][current_pos.x].up)
		if(!created_maze->unit[current_pos.y-1][current_pos.x].visited)
		counter++;
	if(!created_maze->unit[current_pos.y][current_pos.x].left)
		if(!created_maze->unit[current_pos.y][current_pos.x-1].visited)
		counter++;
	if(!created_maze->unit[current_pos.y][current_pos.x].down)
		if(!created_maze->unit[current_pos.y+1][current_pos.x].visited)
		counter++;
	return counter;
}





