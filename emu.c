#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

//Flags
typedef struct Flags {
uint8_t z:1;
uint8_t s:1;
uint8_t p:1;
uint8_t cy:1;
uint8_t ac:1;
uint8_t pad:3;
} Flags;

typedef struct State8080 {
uint8_t a;
uint8_t b;
uint8_t c;
uint8_t d;
uint8_t e;
uint8_t h;
uint8_t l;
uint16_t sp;
uint16_t pc;
uint8_t *memory;
struct Flags cc;
uint8_t int_enable;
} State8080;

void TrovaLavoro(State8080* state)
{
	//You fucked up
	printf ("Error: Unimplemented istruction\n;");
	exit(1);
}

void Emulatore8080p(State8080* state)
{
	return;
}


int main(int argc, char**argv)
{
	FILE *f= fopen(argv[1],"rb");
	if(f==NULL)
	{
		printf("error: No such %s\n",argv[1]);
		exit(1);
	}

	//Mette il file nel buffer
	fseek(f, 0L, SEEK_END);
	int fsize = ftell(f);
	fseek(f, 0L, SEEK_SET);
	
	uint8_t *buffer=malloc(fsize);
	fread(buffer,fsize,1,f);
	fclose(f);
	return 0;
}
