#include <stdbool.h> 
#include <stdlib.h>
#include <error.h>
#include <stdio.h> 
#include "cell.h"
#include "load.h"
#include "generate-image.h"

void generate(problem * my_prob, char * framename){
	
	FILE *p_file = NULL;
    
    p_file = fopen(framename, "w");

    if (p_file == NULL) {
        error(1, 0, "Cannot write to file fact.txt!\n");
    }
    
    int height = my_prob->grid_height;
    int width  = my_prob->grid_width;

    linked_list * p_liste = &(my_prob->p_list);
    
    fprintf(p_file, "P3\n");
    fprintf(p_file, "%d %d\n", width, height);
    fprintf(p_file, "255");
    
    
    for (int i = 0; i < height; i++){
		for (int j = 0; j < width; j++){
			
			position_cell position_etudiee;
			position_etudiee.i=i;
			position_etudiee.j=j;
			
			cell * p_cell = get_cell(p_liste, position_etudiee);
			
			if (p_cell == NULL){
				fprintf(p_file, " 160 160 160 ");
			} else {
				if (p_cell->cell_status == ALIVE){
					fprintf(p_file, " 0 255 0 ");
				}
				if (p_cell->cell_status == NEWBORN){
					fprintf(p_file, " 255 0 0 ");
				}
				if (p_cell->cell_status == DYING){
					fprintf(p_file, " 0 0 255 ");
				}
			}
		}
		fprintf(p_file, "\n");
	}
	
	fclose(p_file);	
	
	free(framename);
    
}
