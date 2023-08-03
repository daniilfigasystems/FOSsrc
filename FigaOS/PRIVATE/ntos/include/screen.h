/*               SCREEN FUNCTION FIGAOS           */
/*               FIGASYSTEMS  2020-2023           */
int x = 0,y = 0;
char * vga  = (char *)0xB8000;
void printChar(char ch,int color){
  if(ch=='\n'||x==160){
      x=0;
      y++;
  }
  if(ch!='\n'){
      vga[(y*160)+x]=ch;
      vga[(y*160)+x+1]=color;
      x+=2;
  }
}
void print(char * str,int color){
    for(int i =0;str[i]!=0;i++)
     printChar(str[i],color);
}