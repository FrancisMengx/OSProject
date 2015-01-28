Francis Meng, Noah Miller, Tianyu Liu
Group 1-H

Current Iteration: Milestone 2;

Instructions:
  Build:     there is a Makefile in the milestone repository. Type in command make will compile the project
             the compilation is controled by the shell script: compileOS.sh. So in the future if we want to
             change the way we are compiling our program, we can change the compile.sh file;

  Execution: After compiling the OS, running command bochs -f opsys.bxrc will fire up bochs and execute the
             operating system.

  Cleanup:   make clean will clean up the .o files and the executable.


Feature Descriptions:

	Print to Console: A user is prompted to enter a message in the console. After pressing ENTER, The 				  message will be displayed on the next line.

	Reading Sectors: The contents can read from a given sector on the floppy disk and print the 				 results on the screen.

	Backspace: The user can press the BACKSPACE key to delete characters from an input before pressing 			   ENTER to submit the input.

	Interrupt Handler: The operating system has an interrupt handler that will execute when an interrupt 				   0x21 occurs. 

	Shell: A user is prompted by the shell when running the operating system. After executing a command 		       from the shell, the shell will be reloaded to use again.
	
	Execute Command: A user can type "execute program" in the shell and then press "ENTER" to run a program 			 from the shell.

	Type Command: A user can type "type filename" in the shell and then press "ENTER" to print a file from 			      the shell.
