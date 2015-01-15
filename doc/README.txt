Francis Meng, Noah Miller, Tianyu Liu
Group 1-H

Current Iteration: Milestone 1;

Instructions:
  Build:     there is a Makefile in the milestone repository. Type in command make will compile the project
             the compilation is controled by the shell script: compileOS.sh. So in the future if we want to
             change the way we are compiling our program, we can change the compile.sh file;

  Execution: After compiling the OS, running command bochs -f opsys.bxrc will fire up bochs and execute the
             operating system.

  Cleanup:   make clean will clean up the .o files and the executable.


Feature Description:
  The only feature that the project has is that when user fire up the operating system as described above
the system will print out "Hello World" on the top of the screen.
