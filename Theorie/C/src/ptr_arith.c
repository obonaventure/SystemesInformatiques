// arithmétique des pointeurs

int main() {

  #define SIZE 3
  int tab[3];
  tab[0]=0x01020304;
  tab[1]=0x05060708;
  tab[1]=0x090A0B0C;

  
  int i;
  for(i=0; i<SIZE;i++) {
    printf("%d est à l'adresse %p\n",tab[i],&(tab[i]));
  }
	
}
