/*
	bu program haritayı ana bilgisayar üzerinde oluşturacaktır
	created by meta
*/

#include <stdio.h>
#include <stdlib.h>
#include"common.h" 
#include"show_map.h"
//#include "show_map.h"
//void *__gxx_personality_v0;//linux terminalinde derlenirken ihtiyaç duyulan bir CPP değişkendir.

/*
	dfs_algorithm.c PROTOTYPES
	section starts**
*/
//struct maze created_maze;

//void dfs_maze(struct maze *created_maze);
/*
	dfs_algorithm.c PROTOTYPES
	section ends**
*/

/*
	element1 begin
*/

struct maze_tool_main** allocate_labyrinth(struct maze_info info,struct maze_tool_main **unit)
{
        int vertical_temp=info.alloc[0], horizontal_temp=info.alloc[1];
        if(!(unit=(struct maze_tool_main**)malloc(sizeof(struct maze_tool_main)*vertical_temp)))
                return NULL;

        vertical_temp=0;
        for(vertical_temp=0;vertical_temp<info.alloc[0];vertical_temp++)
        {
                if(!(unit[vertical_temp]=(struct maze_tool_main *)malloc(sizeof(struct maze_tool_main)*horizontal_temp)))
                        return NULL;
        }
        return unit;
}
bool set_maze_layout(struct maze *created_maze)
{
        int i=0,j=0,k=0;
        for(i=0;i< created_maze->maze_dimension.alloc[0] ;i++)
                for(j=0;j< created_maze->maze_dimension.alloc[1];j++)
                {
                        created_maze->unit[i][j].up=true;
                        created_maze->unit[i][j].down=true;
                        created_maze->unit[i][j].left=true;
                        created_maze->unit[i][j].right=true;
                        created_maze->unit[i][j].someone_here=false;
                        created_maze->unit[i][j].deger=i;
                        created_maze->unit[i][j].visited=false;
                }
        i=0;j=0;
        for(j=0;j < created_maze->maze_dimension.alloc[1];j++)
                {
                        created_maze->unit[i][j].up=true;
                        created_maze->unit[i][j].visited=true;
                }
        i=0;j=0;
        for(j=0;j < created_maze->maze_dimension.alloc[1];j++)
                {
                        created_maze->unit[i][j].up=true;
                        created_maze->unit[i][j].visited=true;
                }
        i=0;j=0;
        for(i;i< created_maze->maze_dimension.alloc[0];i++)
                {
                        created_maze->unit[i][j].left=true;
                        created_maze->unit[i][j].visited=true;
                }

        i=0;j= created_maze->maze_dimension.alloc[1]-1;
        for(i;i < created_maze->maze_dimension.alloc[0];i++)
                {
                        created_maze->unit[i][j].right=true;
                        created_maze->unit[i][j].visited=true;
                }
        i=created_maze->maze_dimension.alloc[0]-1;j=0;
        for(j;j< created_maze->maze_dimension.alloc[1];j++)
                {
                        created_maze->unit[i][j].down=true;
                        created_maze->unit[i][j].visited=true;
                }
        return true;
}
void set_maze_units_unvisited(struct maze *created_maze)
{
	int x=0,y=0;
	for(y=0; y< created_maze->maze_dimension.alloc[0]; y++)
		for(x=0; x< created_maze->maze_dimension.alloc[1];x++)
		{
			created_maze->unit[y][x].visited=false;
		}
}
/*
	element1 stop
*/


int main(int argc,char **argv)
{
	srand(time(NULL));
	struct maze_info info;
	switch(argc)
	{
	case 0:break;
	case 1:
		printf("Program will be executed by default values\n");
		printf("Maze will be generated randomly with unknown x unknown  matrix and default algorithm will be used.. please wait\n");
		info.alloc[0]=6;//34 big
		info.alloc[1]=6;//120 big
		info.algorithm=0;
		break;
	case 3:
		info.alloc[0]=atoi(argv[1]);
		info.alloc[1]=atoi(argv[2]);
		break;
	default:
		printf("Program failure: wrong argument usage (no argument) ");exit(-2);
		break;
	}

	struct maze created_maze;

	if(!(created_maze.unit=allocate_labyrinth(info,created_maze.unit)))
		{
			printf("Program was failed while operating the allocation function");
			exit(EXIT_FAILURE);
		}
	created_maze.maze_dimension.alloc[0]=info.alloc[0];
	created_maze.maze_dimension.alloc[1]=info.alloc[1];
	/*if there is no failure error then program has succesfully proceeded this very line of the page*/
	/*o halde bu kısımdan itibaren haritayı oluşturmaya başlayabiliriz*/

	screen_init();

	set_maze_layout(&created_maze);//element0.h

	dfs_maze(&created_maze);

	set_maze_units_unvisited(&created_maze);

	show_map_main(&created_maze);
	refresh();
	getch();
	endwin();


	return (EXIT_SUCCESS);
}
