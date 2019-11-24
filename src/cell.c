#include "cell.h"
#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>


	
////////////////////////////////////////////////////////////////////////
//                    Fonctions initiales                             //
////////////////////////////////////////////////////////////////////////	


void print_list (cell * p_cell){
	if (p_cell != NULL){
		printf("i: %d , j:%d\n", p_cell->position.i, p_cell->position.j);
		return print_list (p_cell->next_cell);
	}

}

void insert_cell (linked_list * p_list, status inserted_cell_status, position_cell inserted_cell_position, cell * insert_neighbors_list[8]) {
	
	cell * cell_inserted = calloc(1,sizeof(cell));
	//free lors de delete_cell.
	
	cell_inserted -> next_cell     = *p_list;
	cell_inserted -> cell_status   = inserted_cell_status;
	(cell_inserted -> position).i  = inserted_cell_position.i;
	(cell_inserted -> position).j  = inserted_cell_position.j;
	cell_inserted -> previous_cell = NULL;
	
	for (int i = 0; i<8; i++){
		cell_inserted->neighbors_list[i] = insert_neighbors_list[i];
	}
	
	if ((*p_list)!=NULL){
		(*p_list) -> previous_cell = cell_inserted;
		*p_list = cell_inserted;
	} else {
		*p_list = cell_inserted;
	}
}

void delete_cell ( linked_list * p_list, cell * p_cell_to_kill ) {
	
	if (p_cell_to_kill != NULL){
	
		cell * ante_cell = p_cell_to_kill->previous_cell;
		cell * post_cell = p_cell_to_kill->next_cell;
		
		if ((ante_cell != NULL) && (post_cell != NULL)){
			ante_cell->next_cell     = post_cell;
			post_cell->previous_cell = ante_cell;
		}
		if ((ante_cell != NULL) && (post_cell == NULL)){
			ante_cell->next_cell     = post_cell;
		}
		if ((ante_cell == NULL) && (post_cell != NULL)){
			*p_list = post_cell;
			post_cell->previous_cell = ante_cell;
		}
		if ((ante_cell == NULL) && (post_cell == NULL)){
			*p_list = NULL;
		}
		
		free(p_cell_to_kill);

	}
}

int is_empty(linked_list *p_list) {

	if (*p_list == NULL){
		return 1;
	} else {
		return 0;
	}
}

position_cell delta (int i){
	position_cell result;
	result.i=0;
	result.j=0;
	if ( i == 0 ) {
		result.i=1;
		result.j=0;
		return result;
	}
	if ( i == 1 ) {
		result.i=1;
		result.j=1;
		return result;
	}
	if ( i == 2 ) {
		result.i=0;
		result.j=1;
		return result;
	}
	if ( i == 3 ) {
		result.i=-1;
		result.j=1;
		return result;
	}
	if ( i == 4 ) {
		result.i=-1;
		result.j=0;
		return result;
	}
	if ( i == 5 ) {
		result.i=-1;
		result.j=-1;
		return result;
	}
	if ( i == 6 ) {
		result.i=0;
		result.j=-1;
		return result;
	}
	if ( i == 7 ) {
		result.i=1;
		result.j=-1;
		return result;
	}
	return result;
}
	
position_cell new_position_modulo (position_cell position_initiale, position_cell position_delta, problem * my_problem){
	
	int height = my_problem->grid_height;
	int width  = my_problem->grid_width;
	
	position_cell new_position;
	
	new_position.i = (position_initiale.i + position_delta.i) < 0 ? height -1 : (position_initiale.i + position_delta.i) % height;
	new_position.j = (position_initiale.j + position_delta.j) < 0 ? width  -1 : (position_initiale.j + position_delta.j) % width;
	
	return new_position;
}


	
////////////////////////////////////////////////////////////////////////
//                    Fonctions de modification de liste              //
////////////////////////////////////////////////////////////////////////	


cell * get_cell (linked_list * p_list, position_cell positionnus) {
	

	cell * p_get = *p_list;
	
	if (p_get == NULL){
		return NULL;
	} else {
		if ((p_get->position).i == positionnus.i && (p_get->position).j == positionnus.j) {
			return p_get;
		} else {
			return get_cell (&(p_get->next_cell), positionnus);
		}
	}
}
	
void delete_dying (linked_list * p_list){
	
	if (*p_list != NULL){
		if ((*p_list)->cell_status == DYING){
			
			delete_cell (p_list, *p_list);
			delete_dying (p_list);
			
		} else {
			delete_dying (&((*p_list)->next_cell));
		}
	}
}
	
		
void change_newborn_to_alive (linked_list * p_list){
	cell * p_check = *p_list;
	
	if (p_check != NULL){
		cell * cell_next = p_check->next_cell;
		if (p_check->cell_status == NEWBORN){
			p_check->cell_status = ALIVE;
		}
		return change_newborn_to_alive(&cell_next);
	}
}


int alive_neighbors_nb_bis (position_cell position_centrale, problem * my_problem){
	linked_list * p_list = &(my_problem->p_list);
	
	int S = 0;
	
	for (int x = 0; x<8; x++){
		
		position_cell position_neighbor = new_position_modulo (position_centrale, delta(x), my_problem);
		
		cell * cell_neighbor = get_cell (p_list, position_neighbor);
		
		if (cell_neighbor != NULL){
			
			if ((cell_neighbor->cell_status == ALIVE) || (cell_neighbor->cell_status == DYING)){
				
				S=S+1;
			}
		}
	}
	return S;
}
		
		
void change_alive_to_dying (position_cell position_centrale, problem * my_problem ){
	
	linked_list * p_list = &(my_problem->p_list);
	
	cell * cell_cible = get_cell ( p_list, position_centrale );
	
	int number_neighbor = alive_neighbors_nb_bis (position_centrale, my_problem);
	
	if ((cell_cible->cell_status == ALIVE) && (number_neighbor !=2 && number_neighbor !=3)){
		cell_cible->cell_status = DYING;
	}
}


void change_all_alive_to_dying (cell * p_check, problem * my_problem){
	
	if (p_check != NULL){
		
		change_alive_to_dying(p_check->position, my_problem);
		
		return change_all_alive_to_dying(p_check->next_cell, my_problem);
	}
}		
	

void change_dead_to_newborn (position_cell position_etudiee, problem * my_problem){
	
	linked_list * p_list = &(my_problem->p_list);
	
	cell * cell_cible = get_cell ( p_list, position_etudiee );
	
	if (cell_cible == NULL){
		
		cell * tab[8];
	
		int number_neighbor = alive_neighbors_nb_bis (position_etudiee, my_problem);

		if ( number_neighbor == 3 ){
			insert_cell(p_list, NEWBORN, position_etudiee, tab);
		}
	}
}
	
		
void verify_neighbor_of_each_non_newborn_in_L (cell* p_check, problem * my_problem){
		
	if (p_check != NULL){
		
		if ((p_check->cell_status == ALIVE) || (p_check->cell_status == DYING)){
			
			for (int x=0 ; x<8; x++){
				position_cell position_voisin_x = new_position_modulo (p_check->position, delta(x), my_problem);
				change_dead_to_newborn (position_voisin_x, my_problem); //on vérifie chaque voisin
			}
		}	
		verify_neighbor_of_each_non_newborn_in_L(p_check->next_cell,my_problem);
	}
	
}

	
////////////////////////////////////////////////////////////////////////
//                          Print ma grille 	                      //
////////////////////////////////////////////////////////////////////////
	
void print_my_grid(problem * my_problem) {
	
	printf("+");
	for (int i = 0; i < my_problem->grid_width; i++)
		printf("-");
	
	printf("+\n");
	
	
	for (int i = 0; i < my_problem->grid_height; i++) {
        printf("|");
        for (int j = 0; j < my_problem->grid_width; j++) {
			
			position_cell my_position;
			my_position.i=i;
			my_position.j=j;
			
			cell * cell_cible = get_cell (&(my_problem->p_list), my_position);
			
			if (cell_cible != NULL){
				printf ("*");
			} else {
				printf (" ");
			}
		}
        printf("|\n");
    }
    
	printf("+");
    for (int i = 0; i < my_problem->grid_width; i++)
        printf("-");

    printf("+\n");
    
}	
	
////////////////////////////////////////////////////////////////////////	
//                  Fonction next_generation                          //
////////////////////////////////////////////////////////////////////////	
	
void next_generation ( problem * my_problem) {
	
	linked_list * p_liste = &(my_problem->p_list);
	
	delete_dying (p_liste);
	change_newborn_to_alive (p_liste);
	
	//print_list (*p_liste);
	//print_my_grid (my_problem);
	// 
	//Si on veut afficher les étapes intermédiaires.
	
	change_all_alive_to_dying (*p_liste,my_problem);
	verify_neighbor_of_each_non_newborn_in_L (*p_liste,my_problem);
		
}

	
////////////////////////////////////////////////////////////////////////	
//                  Fonction deallocate                               //
////////////////////////////////////////////////////////////////////////	
	
void deallocate  (linked_list * p_list) {
	while (*p_list != NULL){
		delete_cell (p_list, *p_list);
	}
}
