#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include "cell.h"
#include "load.h"


problem * load_grid (char* name) {
    
    FILE *p_file = NULL;

    p_file = fopen(name, "r");

    if (p_file == NULL) {
        error(1, 0, "Cannot read file %s!\n", name);
    }
    
    
    problem * my_problem = malloc(sizeof(problem));
    my_problem -> p_list = NULL;
    
    
    char charac = 0;
    int fscanf_result = 0;
    
    fscanf_result = fscanf(p_file, "%d %d\n", &(my_problem->grid_width), &(my_problem->grid_height));
    //printf("height value : %d\n", my_problem->grid_height);
    if (fscanf_result != 2) {
		error(1, 0, "Line number 1 is not syntactically correct!\n");
	}
	
	fscanf_result = fscanf(p_file, "%d\n", &(my_problem->number_of_step));
	//printf("width  value : %d\n", my_problem->grid_width);
    if (fscanf_result != 1) {
		error(1, 0, "Line number 2 is not syntactically correct!\n");
	}
	
    
    
    for (int i = 0; i < my_problem->grid_height; i++){
		for (int j = 0; j < my_problem->grid_width; j++){
			
			fscanf_result = fscanf(p_file, "%c", &charac);

			
			if (fscanf_result != 1) { 
				error(1, 0, "Not syntactically correct!\n");
			}
			
			if ( charac == 'o' ){
				position_cell posit;
				posit.i=i;
				posit.j=j;
				cell * neighbors[8];
				insert_cell (&(my_problem->p_list) , ALIVE , posit, neighbors);
			}
		}
		fscanf(p_file,"\n");
	}
    fclose(p_file);
    return my_problem;
    
    

}

