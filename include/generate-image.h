/**
 * 
 * @file generate-image.h
 * 
 * @brief This is the header file used for generate-image
 * 
 * @author Hugo Jarkoff
 * 
 * We must be able to print .ppm frames in order to make a .gif corresponding
 * to the problem.
 * 
 * The API is then defined as follows:
 * 
 * -a function to generate a frame
 * 
 */

#ifndef IMAGE_H
#define IMAGE_H

#include <stdbool.h> 
#include <stdlib.h>
#include <stdio.h> 
#include "cell.h"
#include "load.h"


/**
 * @brief Generates a .ppm frame according to the problem studied.
 *
 * @param A pointer to the problem studied, and a pointer to the frame name
 * 
 * @post After the call, a .ppm frame is created, corresponding to the
 * state of the linked list at that time
 */
void generate(problem * my_prob, char * framename);

#endif
