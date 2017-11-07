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
	instruction* instrp;
	instrp = get_inst_info(CURRENT_STATE.PC);
	instruction instr = *instrp;
	printf(" op code is: %x\n", instr.opcode);
	printf("pc is %x\n",CURRENT_STATE.PC);
	IF_Stage();
	sleep(1);
}
void IF_Stage(){
	CURRENT_STATE.PIPE[1] = CURRENT_STATE.PIPE[0];
	CURRENT_STATE.PIPE[0] = CURRENT_STATE.PC;
	CURRENT_STATE.IF_ID_NPC = CURRENT_STATE.PC;
	CURRENT_STATE.PC = CURRENT_STATE.PC +4;
}
void ID_Stage(){

}
void EX_Stage(){

}
void MEM_Stage(){

}
void WB_Stage(){

}  
