#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define CELL_ALIVE '*'
#define CELL_DEAD ' '

#define GAME_SIZE 50
#define GAME_MAX_GENERATIONS 1000

#define clear() printf("\033[H\033[J")

#define for_x for(int x = 0; x < GAME_SIZE; x++)
#define for_y for(int y = 0; y < GAME_SIZE; y++)
#define for_y_x for_y for_x

char cur_state[GAME_SIZE][GAME_SIZE];
char new_state[GAME_SIZE][GAME_SIZE];

void init();
void display();
void display_new();
void update();

int main(int argc, char **argv)
{
	init();
	struct timespec ts;
	ts.tv_sec = 0;
	ts.tv_nsec = 70 * 1000000;
	for(int i = 0; i < GAME_MAX_GENERATIONS; i++)
	{
		clear();
		printf("Generation: %d\n", i+1);
		display();
		update();
		nanosleep(&ts, NULL);
	}
	return 0;
}

void init() {
	srand(time(NULL));
	int i;
	char c;
	for_y_x
	{
		i = rand() % 2;
		if(i == 0) c = CELL_ALIVE;
		else if(i == 1) c = CELL_DEAD;
		cur_state[x][y] = c;
	}
}

void display()
{
	for_x
	{
		printf("--");
	}
	printf("----\n");
	for_y
	{
		printf("| ");
		for_x
		{
			printf("%c ", cur_state[x][y]);
		}
		printf(" |\n");
	}
	for_x
	{
		printf("--");
	}
	printf("----\n");
}

void update()
{
	int neighbour_count;
	for_y_x
	{
		neighbour_count = 0;

		// middle right cell
		if(x < GAME_SIZE-1 && cur_state[x+1][y] == CELL_ALIVE)
		{
			/* printf("m-r\n"); */
			neighbour_count++;
		}

		// middle left cell
		if(x > 0 && cur_state[x-1][y] == CELL_ALIVE)
		{
			/* printf("m-l\n"); */
			neighbour_count++;
		}

		// middle bottom cell
		if(y < GAME_SIZE-1 && cur_state[x][y+1] == CELL_ALIVE)
		{
			/* printf("m-b\n"); */
			neighbour_count++;
		}

		// middle top cell
		if(y > 0 && cur_state[x][y-1] == CELL_ALIVE)
		{
			/* printf("m-t\n"); */
			neighbour_count++;
		}
			
		// top left cell
		if(x > 0 && y > 0 && cur_state[x-1][y-1] == CELL_ALIVE)
		{
			/* printf("t-l\n"); */
			neighbour_count++;
		}
			
		// bottom left cell
		if(x > 0 && y < GAME_SIZE-1 && cur_state[x-1][y+1] == CELL_ALIVE)
		{
			/* printf("b-t\n"); */
			neighbour_count++;
		}
			
		// top right cell
		if(x < GAME_SIZE-1 && y > 0 && cur_state[x+1][y-1] == CELL_ALIVE)
		{
			/* printf("t-r\n"); */
			neighbour_count++;
		}
			
		// bottom right cell
		if(x < GAME_SIZE-1 && y < GAME_SIZE-1 && cur_state[x+1][y+1] == CELL_ALIVE)
		{
			/* printf("b-r\n"); */
			neighbour_count++;
		}

		/* printf("%d %d -> %d\n", x, y, neighbour_count); */

		if(cur_state[x][y] == CELL_ALIVE) {
			if(neighbour_count == 2 || neighbour_count == 3) new_state[x][y] = CELL_ALIVE;
			else new_state[x][y] = CELL_DEAD;
		} else {
			if(neighbour_count == 3) new_state[x][y] = CELL_ALIVE;
			else new_state[x][y] = CELL_DEAD;
		}
	}

	memcpy(cur_state, new_state, sizeof(char) * (GAME_SIZE * GAME_SIZE));
}
