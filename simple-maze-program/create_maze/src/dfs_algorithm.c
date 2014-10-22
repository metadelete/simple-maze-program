#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

void dfs_maze(struct maze *created_maze)
{
        ROAD_TREE *road_stack_begin=NULL;
        ROAD_TREE *road_stack_end=NULL;
        ROAD_TREE *road_stack_current=NULL;

        struct maze_koord start_koord;
	struct maze_koord chosen_koord;
        start_koord.x=1;//start_koord is defined here manually, this will be changed.
        start_koord.y=1;
	created_maze->maze_dimension.start[0]=1;
	created_maze->maze_dimension.start[1]=1;
        add_road_tree(created_maze, &start_koord, &road_stack_begin, &road_stack_current, &road_stack_end);

	do{
		chosen_koord=choose_rand_and_control(created_maze,road_stack_current);
		if(chosen_koord.x==0){
			goback_road_tree_and_control(created_maze, &road_stack_current, &road_stack_end);
		}
		else
		{
			if(chosen_koord.x==100)
			{
				//free_memory_dfs(&road_stack_current,&road_stack_end);
				return;
			}
			add_road_tree(created_maze, &chosen_koord, &road_stack_begin, &road_stack_current, &road_stack_end);
			connect_units(&created_maze,&road_stack_current);
		}
	}while(1);
}

void add_road_tree(struct maze *created_maze,struct maze_koord *koord,ROAD_TREE **road_stack_begin,ROAD_TREE **road_stack_current,ROAD_TREE **road_stack_end)
{
	ROAD_TREE *new_node;

	created_maze->unit[koord->y][koord->x].visited=true;
	if(!(new_node=(ROAD_TREE*)malloc(sizeof(ROAD_TREE))))
	           		{
	           		 fprintf(stdout,"Program has failed while allocating road_tree, go to dfs_algorithm.c's elseif(road_stack_begin==road...) line\n");
				 return;
				}
	new_node->koord.x=koord->x;
	new_node->koord.y=koord->y;

	*road_stack_current=new_node;
	if((*road_stack_begin)==NULL)
                {
                        (*road_stack_end)=(*road_stack_begin)=new_node;
                        (*road_stack_begin)->back=NULL;
                        (*road_stack_begin)->next=NULL;
                }
        else if((*road_stack_begin) == (*road_stack_end))
        {
                (*road_stack_current)->next=NULL;
                (*road_stack_current)->back=(*road_stack_begin);
                (*road_stack_end)->next=(*road_stack_current);
                (*road_stack_end)=(*road_stack_current);
        }
        else
        {
                (*road_stack_current)->next=NULL;
                (*road_stack_current)->back=(*road_stack_end);
                (*road_stack_end)->next=(*road_stack_current);
                (*road_stack_end)=(*road_stack_current);
        }
}
void goback_road_tree_and_control(struct maze *created_maze,ROAD_TREE **road_stack_current,ROAD_TREE **road_stack_end)
{
	(*road_stack_current)=(*road_stack_current)->back;
	bool goback_kontrol=false;
	if(!created_maze->unit[(*road_stack_current)->koord.y][(*road_stack_current)->koord.x].visited)
                goback_kontrol=true;
        if(!created_maze->unit[(*road_stack_current)->koord.y][(*road_stack_current)->koord.x+1].visited)
                goback_kontrol=true;
        if(!created_maze->unit[(*road_stack_current)->koord.y+1][(*road_stack_current)->koord.x].visited)
                goback_kontrol=true;
        if(!created_maze->unit[(*road_stack_current)->koord.y][(*road_stack_current)->koord.x-1].visited)
                goback_kontrol=true;
        if(!goback_kontrol)
       		goback_road_tree_and_control(created_maze,road_stack_current,road_stack_end);
        else
        {
        	while((*road_stack_current)!=(*road_stack_end))
        	{
        		(*road_stack_end)=(*road_stack_end)->back;
        		free((*road_stack_end)->next);
        		(*road_stack_end)->next=NULL;
        	}
        }
}

struct maze_koord choose_rand_and_control(struct maze *created_maze,ROAD_TREE *road_stack_current)
{
	int rand_kontrol=0,end_kontrol=0;
	int x,y;struct maze_koord susame;

	susame=road_stack_current->koord;
	if(!created_maze->unit[susame.y-1][susame.x].visited)
		rand_kontrol=1;
	if(!created_maze->unit[susame.y][susame.x+1].visited)
	        rand_kontrol=1;
	if(!created_maze->unit[susame.y+1][susame.x].visited)
	        rand_kontrol=1;
	if(!created_maze->unit[susame.y][susame.x-1].visited)
	        rand_kontrol=1;

	if(!rand_kontrol)
		{
			for(y=1 ;y < created_maze->maze_dimension.alloc[0]-1; y++){
				for(x=1; x< created_maze->maze_dimension.alloc[1]-1;x++)
				{
					if(!created_maze->unit[y][x].visited)
						{
							susame.x=0;susame.y=0;
							return susame;
						}
				}
			}
		}
	if((!rand_kontrol) && (!end_kontrol))
	{susame.x=100;susame.y=100;return susame;}
	if(!rand_kontrol)
	{susame.x=-1;susame.y=-1; return susame;}

	do{
		x=rand()%4;
		switch(x)
		{
			case 0:
				{if(!created_maze->unit[susame.y-1][susame.x].visited)
					{susame.y--;return susame;}break;}
			case 1:
				{if(!created_maze->unit[susame.y][susame.x+1].visited)
					{susame.x++;return susame;}break;}
			case 2:
				{if(!created_maze->unit[susame.y+1][susame.x].visited)
					{susame.y++;return susame;}break;}
			case 3:
				{if(!created_maze->unit[susame.y][susame.x-1].visited)
					{susame.x--;return susame;}}
				break;
			default: printf("An error was occured in dfs_algorithm\n");
				exit(-1);
		}
	}while(1);
}
void connect_units(struct maze **created_maze,ROAD_TREE **road_tree_current)//
{
	struct maze_koord fark;


	if((*road_tree_current)->back==NULL)
		return;
	else
	{
		fark.x=(*road_tree_current)->koord.x-(*road_tree_current)->back->koord.x;
		fark.y=(*road_tree_current)->koord.y-(*road_tree_current)->back->koord.y;
	}
	switch(fark.x)
	{
		case -1:
		{
		(*created_maze)->unit[(*road_tree_current)->koord.y][(*road_tree_current)->koord.x+1].left=false;
		(*created_maze)->unit[(*road_tree_current)->koord.y][(*road_tree_current)->koord.x].right=false;
		}
		break;
		case 1:
		{
		(*created_maze)->unit[(*road_tree_current)->koord.y][(*road_tree_current)->koord.x-1].right=false;
		(*created_maze)->unit[(*road_tree_current)->koord.y][(*road_tree_current)->koord.x].left=false;
		}
		break;
		default:
		switch(fark.y)
		{
			case -1:
			(*created_maze)->unit[(*road_tree_current)->koord.y+1][(*road_tree_current)->koord.x].up=false;
			(*created_maze)->unit[(*road_tree_current)->koord.y][(*road_tree_current)->koord.x].down=false;
			break;
			case 1:
			(*created_maze)->unit[(*road_tree_current)->koord.y-1][(*road_tree_current)->koord.x].down=false;
			(*created_maze)->unit[(*road_tree_current)->koord.y][(*road_tree_current)->koord.x].up=false;
			break;
			default:printf("An error has occured please contact with your service provider lol\nşaka maka eğer burda hata yaşarsan dfs_algoritm->connect_units'e uğra");
		}
	}
}

void free_memory_dfs(ROAD_TREE **road_stack_begin,ROAD_TREE **road_stack_end)
{

	do
	{
		if((*road_stack_begin)->next==NULL)
		{
			free((*road_stack_end));
			break;
		}
		(*road_stack_begin)=(*road_stack_begin)->next;
		free((*road_stack_begin)->back);
	}while(1);
}
