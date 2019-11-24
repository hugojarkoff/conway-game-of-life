#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include "cell.h"

int main(void){
	
	problem * my_problem = calloc (1,sizeof(problem));
	
	linked_list * my_liste = &(my_problem->p_list);
	
	*my_liste = NULL;
	
	my_problem->grid_height    = 20;
	my_problem->grid_width     = 20;
	my_problem->number_of_step = 100;
	my_problem->p_list         = *my_liste;

	cell * neighbors[8];
	
	
	position_cell my_position;
	my_position.i = 0;
	my_position.j = 1;
	
	insert_cell (my_liste, ALIVE, my_position, neighbors);
	

	
	position_cell my_position_deux;
	my_position_deux.i = 1;
	my_position_deux.j = 2;
	
	insert_cell(my_liste, ALIVE, my_position_deux, neighbors);
    
    
    
	position_cell my_position_trois;
	my_position_trois.i = 2;
	my_position_trois.j = 0;
	
	insert_cell(my_liste, ALIVE, my_position_trois, neighbors);
    
    
	position_cell position_anterieure;
	position_anterieure.i = 2;
	position_anterieure.j = 1;
	
	insert_cell (my_liste, ALIVE, position_anterieure, neighbors);

	position_cell position_finale;
	position_finale.i = 2;
	position_finale.j = 2;
	
	insert_cell (my_liste, ALIVE, position_finale, neighbors);

	my_problem->p_list = *my_liste;

	print_list(*my_liste);
	print_my_grid(my_problem);
	
	
	next_generation (my_problem);
	
	print_my_grid(my_problem);
	
	deallocate(my_liste);
	free(my_problem);
	
	return 0;
}


