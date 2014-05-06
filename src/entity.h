#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <stdlib.h>

//Boolean type
typedef int bool;
#define true 1
#define false 0

struct _Entity {
	int x;
	int y;
	int e_id;
	bool alive;
	int generation;
};

typedef struct _Entity Entity;

//Allocate memory for an entity
Entity *entity_create(
	int x, 
	int y
);

void entity_printf(
	Entity *entity
);

#endif /*ENTITY*/
/*Rules:
For a space that is 'populated':
    Each cell with one or no neighbors dies, as if by loneliness. 
    Each cell with four or more neighbors dies, as if by overpopulation. 
    Each cell with two or three neighbors survives. 
For a space that is 'empty' or 'unpopulated'
    Each cell with three neighbors becomes populated. 
*/
