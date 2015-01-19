/*
	Francis Meng, Noah Miller, Tianyu Liu
	Group 1-H
*/


void printString(char *chars);

int main() {
		interrupt(0x10, 0xE*256 + 'l', 0, 0, 0);
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

