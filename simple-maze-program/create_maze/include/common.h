#ifndef COMMON_H
#define COMMON_H
#include<stdbool.h>
struct maze_tool_main
{
        int deger;
        bool up;
        bool down;
        bool right;
        bool left;
        bool someone_here;
        bool visited;
};

struct maze_info
{
        int start[2];//x:0_y:1
        int alloc[2];
        int algorithm;
        int stop[2];
};
struct maze_koord
{
        int x;
        int y;
	int lane_counter;
};
struct maze
{
        struct maze_tool_main ** unit;
        struct maze_info maze_dimension;
};
typedef struct road_tree
{
        struct maze_koord koord;

        struct road_tree *next;
        struct road_tree *back;
        struct road_tree *current;
}ROAD_TREE;


typedef struct maze_tree
{
	struct maze_koord koord;
	struct maze_tree *next[4];//can be a fail
	struct maze_tree *back;
}MAZE_TREE;

/*decleration of functions, this must be included into main in case to normal compile process*/
/*dfs_start*/
void dfs_maze(struct maze *);
void goback_road_tree_and_control(struct maze *,ROAD_TREE **,ROAD_TREE **);
void add_road_tree(struct maze *,struct maze_koord *,ROAD_TREE **,ROAD_TREE **,ROAD_TREE **);
struct maze_koord choose_rand_and_control(struct maze *,ROAD_TREE *);
void connect_units(struct maze **,ROAD_TREE **);
struct maze_koord choose_rand_and_control(struct maze *,ROAD_TREE *);
void free_memory_dfs(ROAD_TREE **, ROAD_TREE **);
/*dfs_end*/
/*show_map.c_start*/
void screen_init (void);
void set_map_frame(struct maze *);
void show_map(struct maze *);
bool show_map_main(struct maze *);
void recursive_program(struct maze *, struct maze_koord, int);
struct maze_koord connect_map_units(struct maze *, struct maze_koord, struct maze_koord);
void set_unit_visited(struct maze *, struct maze_koord);
struct maze_koord select_new_koord(struct maze *, struct maze_koord);
int check_multiple_lane(struct maze *, struct maze_koord);
bool all_map_kontrol(struct maze *);
/*show_map.c_end*/
#endif
