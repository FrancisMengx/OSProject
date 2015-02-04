/*
	Francis Meng, Noah Miller, Tianyu Liu
	Group 1-H
*/


void printString(char *chars);
void printInt(int n);
void handleInterrupt21(int ax, int bx, int cx, int dx);
int readFile (char *fileName, char buffer[]);
void writeFile (char* fileName, char* buffer, int secNum);
void deleteFile (char *filename);
void copyFile(char *fileName, char *secondFile);
void listFiles();
void readSector(char *buffer, int sector);
void writeSector(char *buffer, int sector);
void readString(char *chars);
void terminate();
void setCursor(int pos);
int mod(int a, int b);
int div(int a, int b);
void executeProgram(char* name, int segment);
char dirSec[512];
char shell[6];
char num[10];

int main() {
    char buffer[13312];
    makeInterrupt21();
    shell[0] = 's';
    shell[1] = 'h';
    shell[2] = 'e';
    shell[3] = 'l';
    shell[4] = 'l';
    shell[5] = '\0';
    interrupt(0x21, 4, shell, 0x2000, 0);

    while(1){asm "hlt";}
}

void executeProgram(char* name, int segment) {
    int addr;
    int i;
    char buffer[13312];
    readFile(name, buffer);
    addr = 0;
    while(addr<=10000) {
        putInMemory(segment, addr, *(buffer+addr));
        addr++;
    }
    launchProgram(segment);
    interrupt(0x21, 5, 0, 0, 0);
}

void terminate(){
    shell[0] = 's';
    shell[1] = 'h';
    shell[2] = 'e';
    shell[3] = 'l';
    shell[4] = 'l';
    shell[5] = '\0';
    interrupt(0x21, 4, shell, 0x2000, 0);
}

int readFile (char *fileName, char *buffer){
    int i;
    int j;
    int tmp;
    int sec;
    int addr;
    readSector(dirSec, 2);
    for(i=0; i<16; i++) {
        tmp = 0;
        for(j=0; j<7; j++) {
            if(j<6) {
                if(j==0 && dirSec[i*32]==0) break;
                if((fileName[j]==0 || fileName[j] == '\n') && dirSec[32*i+j]==0) tmp = 1;
                if(tmp == 0 && fileName[j]!=dirSec[32*i+j]) break;
            } else {
                sec = 0;
                addr = 32*i+j+sec;
                while(dirSec[addr]!=0) {
                    readSector(buffer+(sec*512), dirSec[addr]);
                    sec++;
                    addr = 32*i+j+sec;
                }
                *(buffer+((sec)*512)) = 0x00;
                return sec;
            }
        }
    }
    buffer[0] = 0x00;
    return 0;
}

void deleteFile (char *fileName){
    int i;
    int j;
    int tmp;
    int sec;
    int addr;
    char mapSec[512];
    readSector(dirSec, 2);
    readSector(mapSec, 1);
    for(i=0; i<16; i++) {
        tmp = 0;
        for(j=0; j<7; j++) {
            if(j<6) {
                if(j==0 && dirSec[i*32]==0) break;
                if(fileName[j]==0 && dirSec[32*i+j]==0){
                  tmp = 1;
                }
                if(tmp == 0 && fileName[j]!=dirSec[32*i+j]) break;
            } else {
                dirSec[32*i] = 0x00;
                sec = 0;
                addr = 32*i+j+sec;
                while(dirSec[addr]!=0) {
                    mapSec[(int) dirSec[addr]] = 0x00;
                    dirSec[addr] = 0x00;
                    sec++;
                    addr = 32*i+j+sec;
                }
                writeSector(dirSec, 2);
                writeSector(mapSec, 1);
                return;
            }
        }
    }
}

void copyFile (char *fileName, char *secondFile){
  char buffer[13312];
  int secCount;
  secCount = readFile(fileName, buffer);
  writeFile(secondFile, buffer, secCount);
}

void listFiles(){
  int i, j, k, secCount;
  char singleName[20];
  char buffer[13312];
  char name[6];
  char digit[1];
  num[0] = '0';
  num[1] = '1';
  num[2] = '2';
  num[3] = '3';
  num[4] = '4';
  num[5] = '5';
  num[6] = '6';
  num[7] = '7';
  num[8] = '8';
  num[9] = '9';
  readSector(dirSec, 2);
  for(i = 0; i < 16; i++){
    if(dirSec[i*32] != 0){
      for(j = 0; j < 6; j++){
        if(dirSec[i*32+j] != 0){
          singleName[j] = dirSec[i*32+j];
          name[j] = dirSec[i*32+j];
        }else{
          name[j] = 0x00;
          singleName[j] = ' ';
        }
      }
        singleName[j] = ' ';

      secCount = readFile(name, buffer);
      if(div(secCount, 1000) == 0){
        singleName[j+1] = ' ';
      }else{
        singleName[j+1]= num[div(secCount,1000)];
      }
      if(div(secCount, 100) == 0){
        singleName[j+2] = ' ';
      }else{
        singleName[j+2] = num[div(secCount,100)];
      }
      if(div(secCount, 10) == 0){
        singleName[j+3] = ' ';
      }else{
        singleName[j+3] = num[div(secCount,10)];
      }
      singleName[j+4] = num[mod(secCount, 10)];
      singleName[j+5] = ' ';
      singleName[j+6] = 's';
      singleName[j+7] = 'e';
      singleName[j+8] = 'c';
      singleName[j+9] = 't';
      singleName[j+10] = 'o';
      singleName[j+11] = 'r';
      singleName[j+12] = '\n';
      singleName[j+13] = '\0';
      printString(singleName);
    }
  }
}

void writeFile (char* fileName, char* buffer, int secNum){
  int i, j, k, sec, tmp;
  char mapSec[512];
  char oneSec[512];
  char sectors[512];
  readSector(dirSec, 2);
  readSector(mapSec, 1);
  i = 0;
  j = 0;
  tmp = 0;
  while(secNum != j){
    if(mapSec[i] == 0){
      sectors[j] = i;
      mapSec[i] = 0xFF;
      j++;
    }
    i++;
  }
  for(i = 0; i < 16; i++){
    if(dirSec[i*32] == 0){
      for(j = 0; j < 6; j++){
        if(fileName[j] == '\0' ||  fileName[j] == '\n'){
          tmp = 1;
        }
        if(tmp == 0){
          dirSec[i*32 + j] = fileName[j];
        }else{
          dirSec[i*32 + j] = 0x00;
        }
      }
      sec = 0;
      for(j = 0; j < secNum; j++){
        dirSec[i*32 + 6 + j] = sectors[j];
        for(k = 0; k < 512; k++){
          oneSec[k] = buffer[sec*512 + k];
        }
        writeSector(oneSec, sectors[j]);
        sec++;
      }
      for(j = 0; j < 26-secNum; j++){
        dirSec[i*32 + 6 + secNum + j] = 0x00;
      }
      writeSector(dirSec, 2);
      writeSector(mapSec, 1);
      return;
    }
  }
}

void writeSector(char *buffer, int sector){
  int rs;
  int head;
  int track;
  int ah;
  int al;
  int ch;
  int cl;
  int dh;
  int dl;

  rs = mod(sector, 18) + 1;
  head = mod(div(sector, 18), 2);
  track = div(sector, 36);
  ah = 3;
  al = 1;
  ch = track;
  cl = rs;
  dh = head;
  dl = 0;
  interrupt(0x13, ah*256+al, buffer, ch*256+cl, dh*256+dl);

}


void readSector(char *buffer, int sector){
  int rs;
  int head;
  int track;
  int ah;
  int al;
  int ch;
  int cl;
  int dh;
  int dl;

  rs = mod(sector, 18) + 1;
  head = mod(div(sector, 18), 2);
  track = div(sector, 36);
  ah = 2;
  al = 1;
  ch = track;
  cl = rs;
  dh = head;
  dl = 0;
  interrupt(0x13, ah*256+al, buffer, ch*256+cl, dh*256+dl);

}

void readString(char *chars)	{
	int i;
	char tmp;
  char tmpArr[2];
	i = 0;
	while(1) {
		tmp = interrupt(0x16, 0, 0, 0, 0);
		if(tmp == 0xd) {
      interrupt(0x10, 0xe*256+0xa, 0, 0, 0);
      interrupt(0x10, 0xe*256+0xd, 0, 0, 0);
			chars[i] = 0xa;
			chars[i+1] = 0x0;
			break;
		}
    if(tmp == 0x8){
      if(i > 0){
        interrupt(0x10, 0xe*256+8, 0, 0, 0);
        chars[i-1] = 0x0;
        i--;
        interrupt(0x10, 0xe*256, 0, 0, 0);
        interrupt(0x10, 0xe*256+8, 0, 0, 0);
        continue;
      }
      continue;
    }
		chars[i] = tmp;
    interrupt(0x10, 0xe*256+tmp, 0, 0, 0);
		i++;
	}
}

void printString(char *chars) {
	int i;
	char ah;
	int ax;
	i = 0;
	ah = 0xe;
        while (chars[i] != '\0') {
		ax = ah * 256 + chars[i];
		interrupt(0x10, ax, 0, 0, 0);
		i++;
    if(chars[i] == '\n'){
      interrupt(0x10, 0xe*256+0xd, 0, 0, 0);
    }
  }
}


void handleInterrupt21(int ax, int bx, int cx, int dx) {
	switch(ax) {
		case 0: 
			printString((char *)bx);
			break;
		case 1:
			readString((char *)bx);
			break;
		case 2:
			readSector((char *)bx, cx);
			break;
    case 3:
      readFile((char *)bx, (char *)cx);
      break;
    case 4:
      executeProgram((char *)bx, cx);
      break;
    case 5:
      terminate();
      break;
    case 6:
			writeSector((char *)bx, cx);
      break;
    case 7:
      deleteFile((char *)bx);
      break;
    case 8:
      writeFile((char *)bx, (char*)cx, dx);
      break;
    case 20:
      copyFile((char *)bx, (char*) cx);
      break;
    case 30:
      listFiles();
      break;

    case 100:
      printInt(bx);
      break;
		default:
			printString("Error ax");
			break;
	}
}

void printInt(int n){
	char ah;
  int *list[20];
	int ax;
	ah = 0xe;
  while(div(n, 10) >= 1){
		ax = ah * 256 + 48 + mod(n, 10);
		interrupt(0x10, ax, 0, 0, 0);
    n = div(n, 10);
  }
  ax = ah * 256 + 48 + mod(n, 10);
	interrupt(0x10, ax, 0, 0, 0);
	interrupt(0x10, ah*256 + 48 + '\n', 0, 0, 0);
}

int mod(int a, int b){
  while(a >= b)
      a = a - b;
  return a;
}

int div(int a, int b){
  int quo = 0;
  while((quo + 1)*b <=a){
    quo++;
  }
  return quo;
}
