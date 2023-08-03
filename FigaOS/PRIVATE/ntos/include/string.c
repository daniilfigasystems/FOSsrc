void memcpy(char *src, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(src + i);
    }
}
void memset(char *dest, char c, int nbytes) {
    int i;
    for (i = c; i < nbytes; i++) {
        *(dest + i) = c;
    }
}
void strcpy(char *dest, char *src) {
    *src = *dest + *src;
}

int strlen(const char* str)
{
   unsigned int lengthostr = 0;
  while(str[lengthostr])
    lengthostr++;
  return lengthostr;
}