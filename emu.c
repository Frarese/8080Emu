#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdint.h>
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

// State dei registri
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
	printf ("Error: Unimplemented istruction!\n");
	printf("Instruction: %i\n",state->pc);
	exit(1);
}

int Parity(int a)
{
	return 0;
}
void Emulatore8080p(State8080* state)
{
	uint8_t *opcode = &state->memory[state->pc];
	uint16_t answer, op, offset;
	uint32_t op1,op2;
	uint8_t b0;

	switch(*opcode)
	{
		case 0x00:
			
				//printf("NOP\n");
			       	break; //NOP
			
		case 0x01:
			
				state->c = opcode[1];
				state->b = opcode[2];
				state->pc+=2;
				break;
		case 0x02: TrovaLavoro(state); break;
		case 0x03: TrovaLavoro(state); break;
		case 0x04: answer = (uint16_t) state->b++;
			   state->cc.z =((answer & 0xff)== 0);
			   state->cc.s = ((answer & 0x80)!= 0);
			  // state->cc.cy =(answer >0xff);
			   state->cc.p = Parity(answer & 0xff);
			   break;
		case 0x05: answer = (uint16_t) state->b--;
		  	   state->cc.z =((answer & 0xff)== 0);
			   state->cc.s = ((answer & 0x80)!= 0);
			   // state->cc.cy =(answer >0xff);
			   state->cc.p = Parity(answer & 0xff);
			   break;
		case 0x06: state->b = opcode[1];
			   state->pc++;
			   break;
		case 0x07: TrovaLavoro(state); break;
		case 0x08: break;
		case 0x09: 
			   op1 = (state->h<<8) | (state->l);
			   op2 = (state->b<<8) | (state->c);
			   op1 = op1 + op2;
			   if(op1>0xffff)
				   state->cc.cy=1;
			   else
				   state->cc.cy=0;
			   state->h = op1 & 0xff;
			   state->l = (op1>>8);
			   break;

		case 0x0a: TrovaLavoro(state); break;
		case 0x0b: TrovaLavoro(state); break;
		case 0x0c:
			   answer = (uint16_t) state->c++;
			   state->cc.z =((answer & 0xff)== 0);
			   state->cc.s = ((answer & 0x80)!= 0);
			   //state->cc.cy =(answer >0xff);
			   state->cc.p = Parity(answer & 0xff);
			   break;
		case 0x0d:
			   answer = (uint16_t) state->c--;
		  	   state->cc.z =((answer & 0xff)== 0);
			   state->cc.s = ((answer & 0x80)!= 0);
			   //state->cc.cy =(answer >0xff);
			   state->cc.p = Parity(answer & 0xff);
			   break;
		case 0x0e: state->c = opcode[1];
			   state->pc++;
			   break;
		case 0x0f: 
			   b0 = (state->a &0x01);
			   if(b0==0x01)
				   state->cc.cy=1;
			   else
				   state->cc.cy=0;
			   b0 = (b0<<7);
			   state->a = (state->a >>1) + b0;
			   break;
			   
		case 0x10: break;
		case 0x11:
				state->e = opcode[1];
				state->d = opcode[2];
				state->pc+=2;
				break;
		case 0x12: TrovaLavoro(state); break;
		case 0x13: TrovaLavoro(state); break;
		case 0x14: 
			   answer = (uint16_t) state->d++;
			   state->cc.z =((answer & 0xff)== 0);
			   state->cc.s = ((answer & 0x80)!= 0);
			   //state->cc.cy =(answer >0xff);
			   state->cc.p = Parity(answer & 0xff);
			   break;
		case 0x15: 
			   answer = (uint16_t) state->d--;
			   state->cc.z =((answer & 0xff)== 0);
			   state->cc.s = ((answer & 0x80)!= 0);
			   //state->cc.cy =(answer >0xff);
			   state->cc.p = Parity(answer & 0xff);
			   break;
		case 0x16: state->d = opcode[1];
			   state->pc++;
			   break;
		case 0x17: TrovaLavoro(state); break;
		case 0x18: break;
		case 0x19: 
			   op1 = (state->h<<8) | (state->l);
			   op2 = (state->d<<8) | (state->e);
			   op1 = op1 + op2;
			   if(op1>0xffff)
				   state->cc.cy=1;
			   else
				   state->cc.cy=0;
			   state->h = op1 & 0xff;
			   state->l = (op1>>8);
			   break;
		case 0x1a:
			   offset = (state->d <<8) | (state->e);
			   state->a = state->memory[offset];
			   break;
		case 0x21:
   			   state->l = opcode[1];
   			   state->h = opcode[2];
   			   state->pc+=2;
   			   break;
		case 0x23: op = (state->h <<8) | (state->l);
			   op++;
			   state->h = op & 0xff;
			   state->l = (op>>8);
			   break;
		case 0x26: state->h = opcode[1];
			   state->pc++;
			   break;
		case 0x29: 
			   op1 = (state->h<<8) | (state->l);
			   op2 = (state->h<<8) | (state->l);
			   op1 = op1 + op2;
			   if(op1>0xffff)
				   state->cc.cy=1;
			   else
				   state->cc.cy=0;
			   state->h = op1 & 0xff;
			   state->l = (op1>>8);
			   break;
		case 0x31:
			   state->sp = opcode[2];
			   state->sp = (state->sp<<8) | (opcode[1]);
			   state->pc = state->pc+2;
			   break;
		case 0x32: offset = opcode[2];
			   offset = (offset<<8) | (opcode[1]);
			   state->memory[offset]= state->a;
			   state->pc = state->pc+2;
			   break;
		case 0x36: 
			   offset = (state->h <<8) | (state->l);
			   state->memory[offset] = opcode[1];
			   state->pc++;
			   break;
		case 0x3a: offset = opcode[2];
			   offset = (offset<<8) | (opcode[1]);
			   state->a = state->memory[offset];
			   state->pc= state->pc +2;
			   break;


		default: TrovaLavoro(state);
	}
	state->pc+=1;
}


int main(int argc, char**argv)
{
	State8080* state = (State8080*)malloc(sizeof(State8080));
	state->pc=0;
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
	int i=0;
	state->memory = buffer;
	while(i<10)
	{
		
		Emulatore8080p(state);
		i++;
	}

	return 0;
}
