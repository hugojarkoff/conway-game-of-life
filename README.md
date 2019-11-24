# My 'Conway's Game of Life' implementation in C

Version 0.1

## Prerequisites

This version currently only works on Ubuntu distributions. I tried to make it work on MacOS but it doesn't recognize the <error.h> file, I'll try to make it work in future versions.

## How to run

Download my project, and then simply ``` cd ``` to the repository of my project. Then, compile with command ``` make run-conway ```. The program compiles the frames of the game of life into a animated gif in the 'out' repository.

## Change the initial grid

By default, the program is set to compile the game of life based on the 'ex-complexe.txt' initial setup of cells (which produces the most interesting evolutions, see for yourself...); however, you can change it in the 'app-conway.c' file, line 14 :
```
problem * mon_pb = load_grid ("data/ex-complexe.txt");

```
You simply have to replace the current 'ex-complexe.txt' by the one you want (considering it already exists the data repository).

## Known errors

You may need to exit and then return to the 'out' repository in order to find the animated gif, or rerun the whole 'run-conway'. I don't know why and will try to solve this issue in future versions.
