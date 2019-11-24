#include <stdbool.h> 
#include <stdlib.h>
#include <error.h>
#include <stdio.h> 
#include <string.h>
#include "cell.h"
#include "load.h"
#include "generate-image.h"

#define MAX_LENGTH 50

int main(void){
	
	problem * mon_pb = load_grid ("data/ex-complexe.txt");

	int ite = mon_pb -> number_of_step;
	
	for (int x = 0; x<ite; x++){
		
		char * frame_n = calloc(1,sizeof(char)*MAX_LENGTH);

		sprintf(frame_n, "out/frame%03d.ppm",x);

		generate(mon_pb, frame_n);
		
		next_generation(mon_pb);
	}
	

	deallocate(&(mon_pb->p_list));
	free(mon_pb);
	
	return 0;
}	
