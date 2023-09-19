void kcls(unsigned int color) {
	char *vmem = (char *) 0xb8000;
	unsigned int i=0;
	while (i < (80*25*2)) {
		vmem[i] = ' ';
		i++;
		vmem[i] = color;
		i++;
	}
}
void kprintf(char *string, unsigned int line, unsigned int color, char *ints) {
	char *vmem = (char *) 0xb8000;
	unsigned int i=0;
	i=(line*80*2);
	while(*string != 0) {
		if (*string == '\n') {
			line++;
			i=(line*80*2);
			*string++;
		}
		else {
			vmem[i]=*string;
			*string++;
			i++;
			vmem[i]=color;
			i++;
		}
	}
}
