Francis Meng, Noah Miller, Tianyu Liu
Group 1-H

Current Iteration: Milestone 5;

Instructions:
  Build:     There is a Makefile in the milestone repository. Type in command make will compile the project
             the compilation is controled by the shell script: compileOS.sh. So in the future if we want to
             change the way we are compiling our program, we can change the compile.sh file;

  Execution: After compiling the OS, running command bochs -f opsys.bxrc will fire up bochs and execute the
             operating system.

  Cleanup:   make clean will clean up the .o files and the executable.


Feature Descriptions:

	Print to Console: A user is prompted to enter a message in the console. After pressing ENTER, The message will be displayed on the next line.

	Reading Sectors: The given contents can read from a given sector on the floppy disk and print the results on the screen.

	Backspace: The user can press the BACKSPACE key to delete characters from an input before pressing ENTER to submit the input.

	Interrupt Handler: The operating system has an interrupt handler that will execute when an interrupt 0x21 occurs. 

	Shell: A user is prompted by the shell when running the operating system. After executing a command from the shell, the shell will be reloaded to use again.
	
	Execute Command: A user can type "execute program" in the shell and then press "ENTER" to run a program from the shell.

	Type Command: A user can type "type filename" in the shell and then press "ENTER" to print a file from the shell.

	Delete Command: A user can type "delete filename" in the shell and press "ENTER" to remove the file from the floppy. 

	Create Command: A user can type "create filename" in the shell and press "ENTER" to create a new file. Then the user will be prompted to enter multiple lines for the file until the user enters an empyty line.

	Write Sector: The given contents can be written to the given sector number. 

	Write File: The given contents can be stored in a sector and mapped to the given filename. The user must provide the number of sectors the contents will occupy. 
	
	Copy Command: A user can type "copy file1 file 2" in the shell and press "ENTER" to copy the contents of file1 to a new file, file2. 

	Dir Command: A user can type "dir" in the shell and press "ENTER" to print all files in the directory.

	Kill Command: A user can kill the given process. Type 'kill processNumber' and press "ENTER". processNumber is an integer from 0 to 7 which is assigned to the process when scheduled.  

	Wait Command: A user can force the shell to wait on the given process to finish executing. Type 'wait processNumber' and press "ENTER". processNumber is an integer from 0 to 7 which is assigned to the process when scheduled.  

	MultiProcessing: The operating system supports multiprocessing. The user can execute a process in the shell and then continue to use the shell while the process is running. 

Addional Features:

	Dir Command: In addition to its standard feature, this command prints the number of sectors that each file occupies.

	Clear Command: A user can clear the terminal from previous commands. Type 'clear' and press "ENTER". 

	changeBgColor Command: A user can change background color. Type 'changeBgColor bg' and press "ENTER".

	ps Command: Displays all processes that are currently scheduled to run. Type 'ps' and press "ENTER".

	

	
