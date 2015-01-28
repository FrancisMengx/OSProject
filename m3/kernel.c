/*
	Francis Meng, Noah Miller, Tianyu Liu
	Group 1-H
*/


void printString(char *chars);
void printInt(int n);
void handleInterrupt21(int ax, int bx, int cx, int dx);
void readFile (char *fileName, char buffer[]);
void readSector(char *buffer, int sector);
void readString(char *chars);
void terminate();
void setCursor(int pos);
int mod(int a, int b);
int div(int a, int b);
void executeProgram(char* name, int segment);
char dirSec[512];
int dirSecEmpty;

int main() {
    char buffer[13312];
    dirSecEmpty = 0;
    makeInterrupt21();
    interrupt(0x21, 4, "shell\0", 0x2000, 0);

    while(1){asm "hlt";}
}

void executeProgram(char* name, int segment) {
    int addr;
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
    //interrupt(0x21, 0, "Hello World\0", 0, 0);
    interrupt(0x21, 4, "shell\0", 0x2000, 0);
}

void readFile (char *fileName, char buffer[]){
    int i;
    int j;
    int tmp;
    int sec;
    int addr;
    if(dirSecEmpty==0) {
        readSector(dirSec, 2);
        dirSecEmpty = 1;
    }
    for(i=0; i<16; i++) {
        tmp = 0;
        for(j=0; j<7; j++) {
            if(j<6) {
                if(j==0 && dirSec[i*32]==0) break;
                if(fileName[j]==0 && dirSec[32*i+j]==0) tmp = 1;
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
                return;
            }
        }
    }
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
