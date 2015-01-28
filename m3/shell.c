/*
	Francis Meng, Noah Miller, Tianyu Liu
	Group 1-H
*/

void checkCommand(char *buffer);
short int compareString(char *s1, char *s2);
void handleType(char * command, char *args);
int main(){
  interrupt(0x21, 100, 123, 0, 0);
  while(1){
    char buffer[512];
    interrupt(0x21, 0, "COOL SHELL>\0", 0, 0);
    interrupt(0x21, 1, buffer, 0, 0);
    checkCommand(buffer);
  }
}

void checkCommand(char *buffer){
  char command[20];
  char args[20];
  int counter;
  short int commandLen = 0;
  counter = 0;
  while(1){
    if(buffer[counter] != ' '){
      command[counter] = buffer[counter];
      counter++;
      continue;
    }
    break;
  }

  interrupt(0x21, 0, command, 0, 0);
  if(compareString(command, "type")){
    handleType(command, buffer+counter);
  }else{
    interrupt(0x21, 0, "Command Not Found\n\0", 0, 0);
  }

}

short int compareString(char *s1, char* s2){
  short int i;
  for(i = 0; i < 20; i++){
    if(s1[i] != '\0'){
      if(s1[i] != s2[i]){
        return 0;
      }
    }else{
      return 1;
    }
  }
}

void handleType(char * command, char *args){
  char buffer[13312];
  interrupt(0x21, 3, args, buffer, 0, 0);
  interrupt(0x21, 0, buffer, 0, 0);
}
