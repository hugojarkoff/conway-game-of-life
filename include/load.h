/**
 * 
 * @file load.h
 * 
 * @brief This is the header file used for load
 * 
 * @author Hugo Jarkoff
 * 
 * We must be able to load a problem from a text file in order to change
 * the problem more easily. We therefore define a load_grid function.
 * 
 * The API is then defined as follows:
 * 
 * -a function to print a list of cells
 * 
 */

#ifndef LOAD_H
#define LOAD_H

#include <stdbool.h> 
#include <stdlib.h>
#include <stdio.h> 
#include "cell.h"

/**
 * @brief Loads the problem described to .txt file in the data repertory. 
 * 		 This function returns this problem.
 *
 * @param A pointer to the name of the .txt file
 * 
 * @return the problem corresponding to the .txt file in the data repertory
 */
problem * load_grid (char* name);



#endif
