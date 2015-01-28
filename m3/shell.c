/*
	Francis Meng, Noah Miller, Tianyu Liu
	Group 1-H
*/

void checkCommand(char *buffer);
short int compareString(char *s1, char *s2);
void handleType(char *args);
void handleExecute(char *args);
int main(){
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
    if(buffer[counter] != ' ' && counter < 20){
      command[counter] = buffer[counter];
      counter++;
      continue;
    }
    command[counter] = '\0';
    break;
  }
  if(compareString(command, "type")){
    handleType(buffer+counter+1);
  }else if(compareString(command, "execute")) {
    handleExecute(buffer+counter+1);
  }else{
    interrupt(0x21, 0, "Command Not Found\n\0", 0, 0);
  }
}

void handleExecute(char *args) {
  interrupt(0x21, 4, args, 0x2000, 0);
}

short int compareString(char *s1, char* s2){
  short int i;
  for(i = 0; i < 20; i++){
    if(s1[i] != '\0' && s2[i] != '\0'){
      if(s1[i] != s2[i]){
        return 0;
      }
    }else{
      if(s1[i]!=s2[i]) return 0;
      return 1;
    }
  }
}

void handleType(char *args){
  char buffer[13312];
  interrupt(0x21, 3, args, buffer, 0);
  interrupt(0x21, 0, buffer, 0, 0);
}
