#include <stdbool.h> 
#include <stdio.h>
#include <stdlib.h>
#include <error.h>
#include "cell.h"
#include "load.h"



int main(void){
	
	problem * mon_pb = load_grid ("data/acorn.txt");
	
	printf("height %d\n", mon_pb->grid_height);
	printf("width %d\n", mon_pb->grid_width);
	printf("iterations %d\n", mon_pb->number_of_step);
	
	print_my_grid(mon_pb);
	
	
	deallocate(&(mon_pb->p_list));
	free(mon_pb);
	
	
	
	return 0;

}
