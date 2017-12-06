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
	printf("Instruction's line: %#08x\n",state->pc);
	printf("op: %#02x\n",state->memory[state->pc]);
	exit(1);
}

int Parity(uint8_t a)
{
	if((a & 0x01) == 1)
		return 0;
	else return 1;
}
void Emulatore8080p(State8080* state)
{
	uint8_t *opcode = &state->memory[state->pc];

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
		case 0x04: 
			   {
			   uint16_t answer = (uint16_t) state->b++;
			   state->cc.z =((answer & 0xff)== 0);
			   state->cc.s = ((answer & 0x80)!= 0);
			  // state->cc.cy =(answer >0xff);
			   state->cc.p = Parity(answer & 0xff);
			   }
			   break;
		case 0x05: {
			   uint16_t answer = ((uint16_t) state->b)- 1;
			   state->b = answer;
		  	   state->cc.z =((answer & 0xff)== 0);
			   state->cc.s = ((answer & 0x80)!= 0);
			   // state->cc.cy =(answer >0xff);
			   state->cc.p = Parity(answer & 0xff);}
			   break;
		case 0x06: state->b = opcode[1];
			   state->pc++;
			   break;
		case 0x07: TrovaLavoro(state); break;
		case 0x08: break;
		case 0x09: 
			   {
			   uint32_t op1 = (state->h<<8) | (state->l);
			   uint32_t op2 = (state->b<<8) | (state->c);
			   op1 = op1 + op2;
			   if(op1>0xffff)
				   state->cc.cy=1;
			   else
				   state->cc.cy=0;
			   state->l = op1 & 0xff;
			   state->h = (op1>>8);
			   }
			   break;

		case 0x0a: TrovaLavoro(state); break;
		case 0x0b: TrovaLavoro(state); break;
		case 0x0c:
			   {
			   uint16_t answer = (uint16_t) state->c++;
			   state->cc.z =((answer & 0xff)== 0);
			   state->cc.s = ((answer & 0x80)!= 0);
			   //state->cc.cy =(answer >0xff);
			   state->cc.p = Parity(answer & 0xff);}
			   break;
		case 0x0d:
			   {uint16_t answer = (uint16_t) state->c - 1;
			   state->c=answer;
		  	   state->cc.z =((answer & 0xff)== 0);
			   state->cc.s = ((answer & 0x80)!= 0);
			   //state->cc.cy =(answer >0xff);
			   state->cc.p = Parity(answer & 0xff);}
			   break;
		case 0x0e: state->c = opcode[1];
			   state->pc++;
			   break;
		case 0x0f: 
			   {uint8_t b0 = (state->a &0x01);
			   if(b0==0x01)
				   state->cc.cy=1;
			   else
				   state->cc.cy=0;
			   b0 = (b0<<7);
			   state->a = (state->a >>1) + b0;}
			   break;
			   
		case 0x10: break;
		case 0x11:
				state->e = opcode[1];
				state->d = opcode[2];
				state->pc+=2;
				break;
		case 0x12: TrovaLavoro(state); break;
		case 0x13: 
			   {uint16_t op = (state->d <<8) | (state->e);
			   op++;
			   state->e = op & 0xff;
			   state->d = (op>>8);}
			   break;

		case 0x14: 
			   {uint16_t answer = (uint16_t) state->d++;
			   state->cc.z =((answer & 0xff)== 0);
			   state->cc.s = ((answer & 0x80)!= 0);
			   //state->cc.cy =(answer >0xff);
			   state->cc.p = Parity(answer & 0xff);}
			   break;
		case 0x15: 
			   {uint16_t answer = (uint16_t) state->d--;
			   state->cc.z =((answer & 0xff)== 0);
			   state->cc.s = ((answer & 0x80)!= 0);
			   //state->cc.cy =(answer >0xff);
			   state->cc.p = Parity(answer & 0xff);}
			   break;
		case 0x16: state->d = opcode[1];
			   state->pc++;
			   break;
		case 0x17: TrovaLavoro(state); break;
		case 0x18: break;
		case 0x19: 
			   {uint32_t op1 = (state->h<<8) | (state->l);
			   uint32_t op2 = (state->d<<8) | (state->e);
			   op1 = op1 + op2;
			   if(op1>0xffff)
				   state->cc.cy=1;
			   else
				   state->cc.cy=0;
			   state->l = op1 & 0xff;
			   state->h = (op1>>8);}
			   break;
		case 0x1a:
			   {uint16_t offset = (state->d <<8) | (state->e);
			   state->a = state->memory[offset];}
			   break;
		case 0x21:
   			   state->l = opcode[1];
   			   state->h = opcode[2];
   			   state->pc+=2;
   			   break;
		case 0x23:
			   { uint16_t op = (state->h <<8) | (state->l);
			   op++;
			   state->l = op & 0xff;
			   state->h = (op>>8);}
			   break;
		case 0x26: state->h = opcode[1];
			   state->pc++;
			   break;
		case 0x29: 
			   {uint32_t op1 = (state->h<<8) | (state->l);
			   uint32_t op2 = (state->h<<8) | (state->l);
			   op1 = op1 + op2;
			   if(op1>0xffff)
				   state->cc.cy=1;
			   else
				   state->cc.cy=0;
			   state->l = op1 & 0xff;
			   state->h = (op1>>8);}
			   break;
		case 0x31:
			   state->sp = (opcode[2]<<8) | (opcode[1]);
			   state->pc = state->pc+2;
			   break;
		case 0x32: 
			   {uint16_t offset = (opcode[2]<<8) | (opcode[1]);
			   state->memory[offset]= state->a;
			   state->pc = state->pc+2;}
			   break;
		case 0x36: 
			   {uint16_t offset = (state->h <<8) | (state->l);
			   state->memory[offset] = opcode[1];
			   state->pc++;}
			   break;
		case 0x3a: 
			   {uint16_t offset = (opcode[2]<<8) | (opcode[1]);
			   state->a = state->memory[offset];
			   state->pc= state->pc +2;}
			   break;
		case 0x3e: state->a = opcode[1];
			   state->pc++;
			   break;
		case 0x56:
			   {uint16_t offset = (state->h <<8) | (state->l);
			   state->d = state->memory[offset];}
			   break;
		case 0x5e: 
			   {uint16_t offset = (state->h <<8) | (state->l);
			   state->e = state->memory[offset];}
			   break;
		case 0x66:
			   {uint16_t offset = (state->h <<8) | (state->l);
			   state->h = state->memory[offset];}
			   break;
		case 0x6f: 
			   state->l = state->a;
			   break;
		case 0x77: 
			   {uint16_t offset = (state->h <<8) | (state->l);
			   state->memory[offset]= state->a;}
			   break;
		case 0x7a: 
			   state->a = state->d;
			   break;
		case 0x7b: 
			   state->a = state->e;
			   break;
		case 0x7c: 
			   state->a = state->h;
			   break;
		case 0x7e: 
			   {uint16_t offset = (state->h <<8) | (state->l);
			   state->a = state->memory[offset];}
			   break;
		case 0xa7: 
			   state->a = (state->a) & (state->a);
			   state->cc.z =((state->a & 0xff)== 0);
			   state->cc.s = ((state->a & 0x80)!= 0);
			   state->cc.cy =(state->a >0xff);
			   state->cc.p = Parity(state->a & 0xff);
			   break;
		case 0xaf: 
			   state->a = (state->a) ^ (state->a);
			   state->cc.z =((state->a & 0xff)== 0);
			   state->cc.s = ((state->a & 0x80)!= 0);
			   state->cc.cy =(state->a >0xff);
			   state->cc.p = Parity(state->a & 0xff);
			   break;
		case 0xc1: 
			   state->c = state->memory[state->sp];
			   state->b = state->memory[state->sp+1];
			   state->sp +=2;
			   break;
		case 0xc2: 
			   if(state->cc.z == 0)
				   state->pc = (opcode[2]<<8) | opcode[1] -1;
			   else
				   state->pc +=2;
			   break;
		case 0xc3: 
			   state->pc = ((opcode[2]<<8) | opcode[1]) -1;
			   break;
		case 0xc5:
			   state->memory[state->sp-1] = state->b;
			   state->memory[state->sp-2] = state->c;
			   state->sp = state->sp-2;
			   break;
		case 0xc6: 
			  state->a = state->a + opcode[1];
			  state->pc++;
			  break;
		case 0xc9: 
			  state->pc = (state->memory[state->sp+1]<<8) | state->memory[state->sp]-1;
			  state->sp +=2;
			  break;
		case 0xcd: 
			  state->memory[state->sp-1] = (state->pc>>8);
			  state->memory[state->sp-2] = (state->pc & 0xff);
			  state->sp -=2;
			  state->pc = ((opcode[2]<<8) | opcode[1]) -1;
			  break;
		case 0xd1: 
			   state->e = state->memory[state->sp];
			   state->d = state->memory[state->sp+1];
			   state->sp +=2;
			   break;
		case 0xd3: 
			   state->pc++;
			   break;
		case 0xd5: 
			   state->memory[state->sp-1] = state->d;
			   state->memory[state->sp-2] = state->e;
			   state->sp = state->sp-2;
			   break;
		case 0xe1:
			   state->l = state->memory[state->sp];
			   state->h = state->memory[state->sp+1];
			   state->sp +=2;
			   break;
		case 0xe5:
			   state->memory[state->sp-1] = state->h;
			   state->memory[state->sp-2] = state->l;
			   state->sp = state->sp-2;
			   break;
		case 0xe6: 
			   state->a = (state->a) & opcode[1];
			   state->cc.z =((state->a & 0xff)== 0);
			   state->cc.s = ((state->a & 0x80)!= 0);
			   state->cc.cy =(state->a >0xff);
			   state->cc.p = Parity(state->a & 0xff);
			   state->pc++;
			   break;
		case 0xeb: {
			   uint8_t t1 = state->h;
			   uint8_t t2 = state->l;
			   state->h = state->d;
			   state->l = state->e;
			   state->d = t1;
			   state->e = t2;
			   }
			   break;
		case 0xf1: break;
		case 0xf5: break;
		case 0xfb: break;
		case 0xfe: 
			   state->a = (state->a) - opcode[1];
			   state->cc.z =((state->a & 0xff)== 0);
			   state->cc.s = ((state->a & 0x80)!= 0);
			   state->cc.cy =(state->a >0xff);
			   state->cc.p = Parity(state->a & 0xff);
			   state->pc++;
			   break;



		default: TrovaLavoro(state);}
		//printf("opcode: %#02x",state->memory[state->pc]);
		state->pc+=1;
}

void DebugEmu(State8080 * state)
{
	char c;
	printf("Run?\n");
	scanf("%c%*c",&c);
	if(c=='y'|| c== 'Y')
		Emulatore8080p(state);
	else exit(1);

	printf("a: %#02x\n",state->a);
	printf("b: %#02x\n",state->b);
	printf("c: %#02x\n",state->c);
	printf("d: %#02x\n",state->d);
	printf("e: %#02x\n",state->e);
	printf("h: %#02x\n",state->h);
	printf("l: %#02x\n",state->l);
	printf("pc: %#04x\n",state->pc);
	printf("sp: %#04x\n",state->sp);
	printf("flags: %i %i %i %i %i %i\n",state->cc.z,state->cc.s,state->cc.p,state->cc.cy,state->cc.ac,state->cc.pad);
}


int main(int argc, char**argv)
{
	State8080* state = (State8080*)malloc(sizeof(State8080));
	state->pc=0;
	state->sp= 0xf000;
	state->a =0;
	state->b =0;
	state->c =0;
	state->d =0;
	state->e =0;
	state->h =0;
	state->l =0;
	state->cc = (Flags){.z=0,.s=0,.p=0,.cy=0,.ac=0,.pad=0};

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
	while(i< 100003)
	{
	//	Emulatore8080p(state);	
		DebugEmu(state);
		i++;
	}
	printf("opcode: %#02x\n",state->memory[state->pc]);
	return 0;
}
