/*
	Francis Meng, Noah Miller, Tianyu Liu
	Group 1-H
*/

void checkCommand(char *buffer);
short int compareString(char *s1, char *s2);
void handleType(char *args);
void handleExecute(char *args);
void handleDeleteFile(char *args);
void handleCopyFile(char *args);
void handleDir();
void handleCreateFile(char *fileName);
int div(int a, int b);
int main(){
  enableInterrupts();
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
    if((buffer[counter] != ' ' && buffer[counter] != '\n') && counter < 20){
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
  }else if(compareString(command, "delete")){
    handleDeleteFile(buffer+counter+1);
  }else if(compareString(command, "copy")){
    handleCopyFile(buffer+counter+1);
  }else if(compareString(command, "dir")){
    handleDir();
  }else if(compareString(command, "create")){
    handleCreateFile(buffer+counter+1);
  }else{
    interrupt(0x21, 0, "Command Not Found\n\0", 0, 0);
  }
}

void handleCreateFile(char *fileName){
  char oneLine[512];
  char buffer[13312];
  int numChar;
  int i;
  numChar = 0;
  while(1){
    interrupt(0x21, 1, oneLine, 0, 0);
    if(oneLine[0] == '\n'){
      break;
    }
    for(i = 0; i < 512; i ++){
      buffer[numChar] = oneLine[i];
      numChar++;
      if(oneLine[i] == '\n'){
        break;
      }
    }
  }
  interrupt(0x21, 8, fileName, buffer, div(numChar, 512)+1);

}

void handleDir(){
  interrupt(0x21, 30, 0,0,0);
}

void handleDeleteFile(char *args){
  interrupt(0x21, 7, args, 0, 0);
}

void handleExecute(char *args) {
  interrupt(0x21, 4, args, 0x2000, 0);
}

void handleCopyFile(char *args){
  char buffer[13312];
  char argOne[20];
  int counter;
  char secNum[1];
  int i;
  int j;
  counter = 0;
  while(1){
    if(args[counter] != ' ' && counter < 20){
      argOne[counter] = args[counter];
      counter++;
      continue;
    }
    argOne[counter] = '\0';
    break;
  }
  i = 0;
  interrupt(0x21, 20, argOne, args+counter+1, 0);
}

void handleType(char *args){
  char buffer[13312];
  interrupt(0x21, 3, args, buffer, 0);
  interrupt(0x21, 0, buffer, 0, 0);
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


int div(int a, int b){
  int quo = 0;
  while((quo + 1)*b <=a){
    quo++;
  }
  return quo;
}
