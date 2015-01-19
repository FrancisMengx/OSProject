/*
	Francis Meng, Noah Miller, Tianyu Liu
	Group 1-H
*/


void printString(char *chars);
void readString(char *chars);
void handleInterrupt21(int ax, int bx, int cx, int dx);
void readSector(char *buffer, int sector);
void setCursor(int pos);
int mod(int a, int b);
int div(int a, int b);

int main() {
	char line[512];
	int tmp;
	char buffer[512];
	printString("Enter a line: \0");
	readString(line);
	printString(line);
  readSector(buffer, 30);
  printString(buffer);
  makeInterrupt21();
  interrupt(0x21, 2, line, 30, 0);
  interrupt(0x21, 0, line, 0, 0);
  //while(1){}
  asm {
  	"hlt";
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
      interrupt(0x10, 0xe*256+'\n', 0, 0, 0);
			chars[i] = 0xa;
			chars[i+1] = 0x0;
      setCursor(i);
			break;
		}
    if(tmp == 0x8){
      if(i > 0){
        interrupt(0x10, 0xe*256+8, 0, 0, 0);
        chars[i-1] = 0x0;
        i--;
        interrupt(0x10, 0xe*256, 0, 0, 0);
        interrupt(0x10, 0xe*256, 0, 0, 0);
        continue;
      }
      continue;
    }
		chars[i] = tmp;
    interrupt(0x10, 0xe*256+tmp, 0, 0, 0);
		i++;
	}
}

void setCursor(int pos){
  int i;
  for(i = 0; i < pos; i++){
        interrupt(0x10, 0xe*256+8, 0, 0, 0);
  }
}

void printString(char *chars) {
	int i;
  int curPos;
	char ah;
	int ax;
	i = 0;
  curPos=0;
	ah = 0xe;
	while (chars[i] != '\0') {
		ax = ah * 256 + chars[i];
		interrupt(0x10, ax, 0, 0, 0);
		i++;
    curPos++;
    if(chars[i] == '\n'){
      setCursor(curPos);
      curPos = 0;
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
		default: 
			printString("Error ax");
			break;
	}
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
