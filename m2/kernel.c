/*
	Francis Meng, Noah Miller, Tianyu Liu
	Group 1-H
*/


void printString(char *chars);
void readString(char *chars);

int main() {
	//interrupt(0x10, 0xe * 256 + 'L', 0, 0, 0);
	//interrupt(0x10, 0xe * 256 + 'T', 0, 0, 0);
	//interrupt(0x10, 0xe * 256 + 'Y', 0, 0, 0);
	char line[80];
	printString("Enter a line: \0");
	readString(line);
	printString(line);
}

void readString(char *chars)	{
	int i;
	char tmp;
	i = 0;
	while(1) {
		tmp = interrupt(0x16, 0, 0, 0, 0);
		if(tmp == 0xd) {
			chars[i] = 0xa;
			chars[i+1] = 0x0;
			break;
		}
		chars[i] = tmp;
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
	}

}

