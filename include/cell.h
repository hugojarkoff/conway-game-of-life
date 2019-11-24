/**
 * 
 * @file cell.h
 * 
 * @brief This is the header file used for cell and list definiton
 * 
 * @author Hugo Jarkoff
 * 
 * The chained list containing the cells has to evolve according to the 
 * rules of the Game Of Life. Therefore, we must define functions to 
 * change the list accordingly to the current state of the grid.
 * 
 * The API is then defined as follows:
 * 
 * -a function to print a list of cells
 * -a function to insert a cell in the linked list
 * -a function to delete a cell in the linked list
 * -a function to check if a list is empty
 * -a function to compute the index (ranging from 0 to 7) of a neighbor to a cell
 * -a function to compute the position of a neighbor to a cell given its index ("delta")
 * -a function to compute a new position (from two positions), taking 
 *  into account a "return" (modulo) from the bottom to the top of the grid
 * -a function to give the memory adress of a cell given its position
 * -a function to kill all the dying cells in a list
 * -a function to change, in a list, all the newborn cells into alive cells
 * -a function to compute the numbers of alive (ie ALIVE and DYING) neighbors of a cell
 * -a function to check if an alive cell can die, and if so, change its
 * 	status into "dying"
 * -a function to change all the alive cells in dying cells, if they can
 * -a function to check if a dead cell can revive, and if so, change its
 * 	status into "alive"
 * -a function to check if any neighbor of each alive cell in the list can revive
 * -a function to print the grid according to the list
 * -a function to make the list evolve
 * -a function to deallocate a list
 * 
 */
 
#ifndef CELL_H
#define CELL_H

#include <stdbool.h> 
#include <stdlib.h>
#include <stdio.h> 

/**
 * @brief An alias to the struct representing the position of a cell.
 */
typedef struct position_cell position_cell;

/**
 * @brief An alias to the struct representing the cell.
 */
typedef struct cell cell;

/**
 * @brief An alias to the type representing the linked list of cells.
 */
typedef cell * linked_list; 

/**
 * @brief An alias to the struct representing the problem.
 */
typedef struct problem problem; 

/**
 * @brief An alias to the enum representing the status of the cell.
 */
typedef enum {
	ALIVE,
	NEWBORN,
	DYING
} status;


/**
 * @brief The structure representing the position of the cell.
 */
struct position_cell {
	/** The index associated to the X axis, from left to right */
	int i;
	/** The index associated to the Y axis, from top to bottom */
	int j;
};

/**
 * @brief The structure representing the cell.
 */
struct cell {
	/** The status of the cell */
	status cell_status;
	/** The position of the cell */
	position_cell position;
	/** The list of neighbors of the cell */
	cell *neighbors_list[8];
	/** The pointer to the next cell in the list */
	cell *next_cell;
	/** The pointer to the previous cell in the list */
	cell *previous_cell;
};

/**
 * @brief The structure representing the problem.
 */
struct problem {
	/** The height of the grid */
	int grid_height;
	/** The width of the grid */
	int grid_width;
	/** The number of iterations */
	int number_of_step;
	/** The linked list of cells */
	linked_list p_list;
};



/**
 * @brief Print the linked list of cells.
 *
 * @param  my_problem a pointer to the problem whose list has to printed
 *
 */
void print_list (cell * p_cell);


/**
 * @brief Insert a cell in the linked list.
 *
 * @param p_list a pointer to the linked list in which the cell has to inserted
 * 		  inserted_cell_status the status of the cell to be inserted
 * 		  inserted_cell_position the position of the cell to be inserted
 * 		  insert_neighbors_list[8] an array of 8 pointers to the neighbors
 * 								   of the cell to be inserted
 *
 * @post the cell is inserted a the beggining of the list
 */
void insert_cell (linked_list * p_list, status inserted_cell_status, position_cell inserted_cell_position, cell * insert_neighbors_list[8]);

/**
 * @brief Delete a cell in the list.
 *
 * @param p_list a pointer to the linked list in which the cell is to be deleted
 * 		  p_cell_to_kill a pointer to the cell to be deleted
 * 
 * @post After the call, if the cell pointed was is the list, it is removed from
 * 		 the list.
 */
void delete_cell (linked_list * p_list, cell * p_cell_to_kill);

/**
 * @brief Checks if a list is empty
 *
 * @param p_list a pointer to the list to test
 * 
 * @return 1 if the list is empty, 0 if not
 *
 */
int is_empty(linked_list *p_list);

/**
 * @brief Returns the index of the neighbor (from 0 to 7) given its "delta" to the central cell.
 *
 * @param int i, int j : the "delta" position of the neighbor.
 * 
 * @return the index of the neighbor as defined in the paper
 *
 */
int index_neighbor_delta (int i, int j);

/**
 * @brief Returns the "delta" of the neighbor given its index (0-7).
 * Useful in filling the neighbor.
 *
 * @param int i : the index of the neighbor.
 *
 */
position_cell delta (int i);
	
/**
 * @brief Returns a new position taking into account the "return" aspect of the problem in the grid
 *
 * @param position_initiale : the initiate position
 * 		  position_delta: the delta position, ranging from -1<x<1 and -1<y<1 (cf index_neighbor_delta)
 * 
 * @return the new position computed according to the dimensions of the grid
 *
 */	
position_cell new_position_modulo (position_cell position_initiale, position_cell position_delta, problem * my_problem);

/**
 * @brief Returns a cell given its position in the grid.
 *
 * @param the linked list in which the cell may or may not be,
 * 			and positionnus its position in the grid
 *
 * @return a pointer to the cell if the cell is in the list, and to NULL if the cell
 * 			is not in the list
 */
cell * get_cell (linked_list * p_list, position_cell positionnus);

/**
 * @brief Removes all the dying cells in a list.
 *
 * @param the linked list that has to be examined
 *
 * @post all the 'dying' cells are removed from the list
 */
void delete_dying (linked_list * p_list);

/**
 * @brief Changes all the status 'newborn' in a linked list to 'alive'.
 *
 * @param the linked list that has to be examined
 *
 * @post the status of all 'newborn' cells in the list is now 'alive'
 */
void change_newborn_to_alive (linked_list * p_list);

/**
 * @brief Changes the status 'alive' of a cell into 'dying' if the cell
 * 	is effectively dying
 *
 * @param the position of the cell that has to be examined, and a pointer to the problem
 *
 * @post the status of the cell is now 'dying' if the cell was effectively
 * 	dying; if not, its status remains unchanged.
 */
void change_alive_to_dying (position_cell position_centrale, problem * my_problem);

/**
 * @brief Computes the number of alive/dying neighbors of a cell a list.
 *
 * @param  the position of the cell to be examined and a pointer to the problem
 * 	(containing the linked list of cells).
 *
 * @return the number of alive/dying neighbors of a cell a list.
 */
int alive_neighbors_nb_bis (position_cell position_centrale, problem * my_problem);

/**
 * @brief Change the status of actually dying cells in a list, from 'alive' to 'dying'.
 *
 * @param a pointer to a cell (necessary given the way I built this function: recursively)
 * 	and a pointer to the problem containing the linked list
 *
 * @post All the 'alive' cells in the linked list of the problem that were dying
 * 	now have a 'dying' status
 */
void change_all_alive_to_dying (cell * p_check, problem * my_problem);

/**
 * @brief If a cell is dead and can revive (according to the rules of GoL),
 * 		it is inserted in the list, and its status is changed to 'newborn'.
 *
 * @param the position of the cell to be examined and a pointer to the problem 
 * 	containing the linked list of cells.
 *
 * @post If the dead cell could be revived, it is inserted in the linked list and 
 * 		its status is changed to 'newborn'
 */
void change_dead_to_newborn (position_cell position_etudiee, problem * my_problem);

/**
 * @brief Checks if each neighbor of a alive/dying cell in the list can be revived
 *
 * @param a pointer to the cell (I built the function recursively) 
 * and a pointer to the problem containing the linked list of cells 
 * 
 * @post Each neighbor of each non newborn cell in the list is now examined: if
 * it could be revived, it has been (ie change its status to 'newborn' and inserted in the list);
 * if not, left unchanged.
 */
void verify_neighbor_of_each_non_newborn_in_L (cell* p_check,problem * my_problem);

/**
 * @brief Print the linked list of cells
 *
 * @param a pointer to the problem containing the linked list of cells
 * 
 */
void print_my_grid(problem * my_problem);

/**
 * @brief Make the list of cells evolve according to the rules of Game Of Life.
 *
 * @param A pointer to the problem containing the list of cells 
 * 
 * @post After the call, the list is modified according to the rules of GoL.
 */
void next_generation (problem * my_problem);

/**
 * @brief Deallocates entirely the list of cells
 *
 * @param A pointer to the list of cells 
 * 
 * @post After the call, the list now points to NULL
 */
void deallocate  (linked_list * p_list);

#endif
