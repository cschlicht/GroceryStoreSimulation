# GroceryStoreSimulation
This is a simulation that given the amount of customers (m) that have their own arrival time and duration, will simulate the average wait, max wait, and total wait time of situations with 1 to m-1 registers. Also provides a trace file to show the movement of the customers throughout the simulation.

To run: gcc Simulation.c Job.c  IntegerQueue.c -o simulate
Then: .\simulate.exe inputFile.txt

The trace file (.trc) and the report file (.rpt) will be created in the folder.
