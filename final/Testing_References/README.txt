Project: sim04
Class: CS480
instructor: Michael Leverington

Make command: make -f sim04_mf.make
Comments: There are two warnings that appear apon compilation. They are both related to casting variables for POSIX thread operations.

Run: ./sim04.exe "config file name"
Comments: Be sure to supply a valid config file with the file extention ".cnf". Also make sure it is in the same directory.

Code cosmetic issues: There are a few repeted lines of code used for output. These mostly appear in CPU.c.

General program issues: There is an output bug in my program that only runs the first process in the meta-data file. However, it still correctly executes the scheduling algorithm.
	for example if the config file scheduling code is SJF, the processes will execute in the correct order but the output will not be shown for each task.

MMU: The memory allocation requirement has been implemented as seen in MMU.c & MMU.h it is called in the CPU when running memory related tasks.

Master Loop: The general flow of the program is as such: the driver first calls the parsers to allocate data to the correct structures. 
	Then the driver calls the Scheduler which determines which scheduling algorithm to use. The processes are passed to the CPU based on the scheduling algorithm.
	Then the CPU will run each task (meta-data). The CPU is also responsible for creating threads and interrupting for I/O operations. 
	The output data is created mostly in the CPU but some in the Driver. 
	The Driver then calls the Output handler to display all the data to the correct system (FILE MONITOR or BOTH) based on the config file