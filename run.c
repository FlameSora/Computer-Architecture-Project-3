/***************************************************************/
/*                                                             */
/*   MIPS-32 Instruction Level Simulator                       */
/*                                                             */
/*   CS311 KAIST                                               */
/*   run.c                                                     */
/*                                                             */
/***************************************************************/

#include <stdio.h>

#include "util.h"
#include "run.h"

/***************************************************************/
/*                                                             */
/* Procedure: get_inst_info                                    */
/*                                                             */
/* Purpose: Read insturction information                       */
/*                                                             */
/***************************************************************/
instruction* get_inst_info(uint32_t pc) { 
    return &INST_INFO[(pc - MEM_TEXT_START) >> 2];
}


/***************************************************************/
/*                                                             */
/* Procedure: process_instruction                              */
/*                                                             */
/* Purpose: Process one instrction                             */
/*                                                             */
/***************************************************************/
void process_instruction(){
	/** Your implementation here */
//	instruction* instrp;
//	instrp = get_inst_info(CURRENT_STATE.PC);
//	instruction instr = *instrp;
//	printf(" op code is: %x\n", instr.opcode);
	printf("pc is %x\n",CURRENT_STATE.PC);
//	printf("stare");
	WB_Stage();
	MEM_Stage();
	ID_Stage();
	IF_Stage();
	sleep(1);
}
void IF_Stage(){
//	CURRENT_STATE.PIPE[1] = CURRENT_STATE.PIPE[0];
	CURRENT_STATE.PIPE[0] = CURRENT_STATE.PC;
	CURRENT_STATE.IF_ID_NPC = CURRENT_STATE.PC;
	CURRENT_STATE.PC = CURRENT_STATE.PC +4;
}
void ID_Stage(){
	instruction* instrp; 
	instrp = get_inst_info(CURRENT_STATE.IF_ID_NPC);
	if(CURRENT_STATE.IF_ID_NPC == 0){
		printf ("noop");
	}
	else{ 
//	instruction instr = *instrp;
	CURRENT_STATE.PIPE[1] = CURRENT_STATE.IF_ID_NPC;
	CURRENT_STATE.ID_EX_NPC = CURRENT_STATE.IF_ID_NPC;
	CURRENT_STATE.ID_EX_REG1 = CURRENT_STATE.REGS[RS(instrp)];
//	printf("RS is:%x \n",RS(instrp));
	CURRENT_STATE.ID_EX_REG2 = CURRENT_STATE.REGS[RT(instrp)];
	CURRENT_STATE.ID_EX_IMM = IMM(instrp);
	if (OPCODE(instrp)  == 2){
		CURRENT_STATE.PC = TARGET(instrp)*4;
		CURRENT_STATE.ID_EX_DEST = 1;
	}
	else if(OPCODE(instrp) == 3){
		CURRENT_STATE.REGS[31] = CURRENT_STATE.PC+8;
		CURRENT_STATE.PC = TARGET(instrp)*4;
		CURRENT_STATE.ID_EX_DEST = 1;
	}
	else if(OPCODE(instrp) == 0 &&FUNC(instrp) == 8){
		CURRENT_STATE.PC = CURRENT_STATE.REGS[RS(instrp)];
		CURRENT_STATE.ID_EX_DEST = 1;
	}
	else{
	//	CURRENT_STATE.PC = CURRENT_STATE.PC +4;
		CURRENT_STATE.ID_EX_DEST = 0;
	}
	}
	
	 
}
void EX_Stage(){


}
void MEM_Stage(){
	if(CURRENT_STATE.EX_MEM_NPC != 0){
		instruction* instrp; 
		instrp = get_inst_info(CURRENT_STATE.IF_ID_NPC);
		CURRENT_STATE.PIPE[3] = CURRENT_STATE.EX_MEM_NPC;
		CURRENT_STATE.MEM_WB_NPC = CURRENT_STATE.EX_MEM_NPC;
		CURRENT_STATE.MEM_WB_ALU_OUT = CURRENT_STATE.EX_MEM_ALU_OUT;
		if(OPCODE(instrp) == 43){
		//sw 
			mem_write_32(CURRENT_STATE.EX_MEM_ALU_OUT, CURRENT_STATE.EX_MEM_W_VALUE);
		}
		else if(OPCODE(instrp) == 35){
		//lw 
			CURRENT_STATE.MEM_WB_MEM_OUT = mem_read_32(CURRENT_STATE.EX_MEM_ALU_OUT);
		}
		if(CURRENT_STATE.EX_MEM_BR_TAKE ==1){
			//flush
			CURRENT_STATE.IF_ID_NPC = 0;
			CURRENT_STATE.ID_EX_NPC = 0;
			CURRENT_STATE.EX_MEM_NPC=0; 
			CURRENT_STATE.PC = CURRENT_STATE.EX_MEM_BR_TARGET;
		}
		CURRENT_STATE.MEM_WB_BR_TAKE = CURRENT_STATE.EX_MEM_BR_TAKE;
		CURRENT_STATE.MEM_WB_DEST  = CURRENT_STATE.EX_MEM_DEST; 
	}		
}
void WB_Stage(){
	if(CURRENT_STATE.MEM_WB_NPC!=0){
		instruction* instrp; 
		instrp = get_inst_info(CURRENT_STATE.IF_ID_NPC);
		CURRENT_STATE.PIPE[4] = CURRENT_STATE.MEM_WB_NPC;
		if(OPCODE(instrp) == 35){
			CURRENT_STATE.REGS[CURRENT_STATE.MEM_WB_DEST] = CURRENT_STATE.MEM_WB_MEM_OUT;
		}
		else if(OPCODE(instrp) != 4 && OPCODE(instrp) != 5&& OPCODE(instrp)!=43&&OPCODE(instrp)!= 2&&OPCODE(instrp) != 3 &&~(OPCODE(instrp)==0 && FUNC(instrp) ==8)){
			CURRENT_STATE.REGS[CURRENT_STATE.MEM_WB_DEST] = CURRENT_STATE.MEM_WB_ALU_OUT;
		}

	}	
}  
