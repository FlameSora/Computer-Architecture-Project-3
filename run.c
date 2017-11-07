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
	EX_Stage();
	IF_Stage();
	sleep(1);
}

void IF_Stage(){

	CURRENT_STATE.PIPE[0] = CURRENT_STATE.PC;
	CURRENT_STATE.IF_ID_NPC = CURRENT_STATE.PC;
	CURRENT_STATE.PC = CURRENT_STATE.PC +4;
}
void ID_Stage(){

}
void EX_Stage(){

	if (CURRENT_STATE.ID_EX_NPC != 0) {

		instruction* inst;
		inst = get_inst_info(CURRENT_STATE.ID_EX_NPC);
		//instruction instr = *inst;
		CURRENT_STATE.PIPE[2] = CURRENT_STATE.ID_EX_NPC;
		CURRENT_STATE.EX_MEM_NPC = CURRENT_STATE.ID_EX_NPC;
		
		short op = OPCODE(inst);
		short func = FUNC(inst);
		uint32_t reg1 = CURRENT_STATE.ID_EX_REG1; // rs
		uint32_t reg2 = CURRENT_STATE.ID_EX_REG2; // rt
		short imm = CURRENT_STATE.ID_EX_IMM;
		unsigned char sh = SHAMT(inst);
		
		// Addiu
		if (op == 9) {
			CURRENT_STATE.EX_MEM_ALU_OUT = reg1 + imm;
			CURRENT_STATE.EX_MEM_DEST = RT(inst);
		}
		// Andi
		if (op == 12) {
			CURRENT_STATE.EX_MEM_ALU_OUT = reg1 & imm;
			CURRENT_STATE.EX_MEM_DEST = RT(inst);
		}
		// Beq
		if (op == 4) {
			if (reg1 == reg2) {
				CURRENT_STATE.EX_MEM_BR_TARGET = CURRENT_STATE.ID_EX_NPC + 4 + imm*4;
				CURRENT_STATE.EX_MEM_BR_TAKE = TRUE;
			}
		}
		// Bne
		if (op == 5) {
			if (reg1 != reg2) {
				CURRENT_STATE.EX_MEM_BR_TARGET = CURRENT_STATE.ID_EX_NPC + 4 + imm*4;
				CURRENT_STATE.EX_MEM_BR_TAKE = TRUE;
			}
		}
		// Lui
		if (op == 15) {
			uint32_t data = (uint32_t) imm;
			CURRENT_STATE.EX_MEM_ALU_OUT = data << 16;
			CURRENT_STATE.EX_MEM_DEST = RT(inst);
		}
		// Lw
		if (op == 35) {
			CURRENT_STATE.EX_MEM_ALU_OUT = reg1 + imm;
			CURRENT_STATE.EX_MEM_DEST = RT(inst);
		}
		// Ori
		if (op == 13) {
			CURRENT_STATE.EX_MEM_ALU_OUT = reg1 | imm;
			CURRENT_STATE.EX_MEM_DEST = RT(inst);
		}
		// Sltiu
		if (op == 11) {
			uint32_t data = (uint32_t) imm;
			if (reg1 < data) {
				CURRENT_STATE.EX_MEM_ALU_OUT = 1;
				CURRENT_STATE.EX_MEM_DEST = RT(inst);
			} else {
				CURRENT_STATE.EX_MEM_ALU_OUT = 0;
				CURRENT_STATE.EX_MEM_DEST = RT(inst);
			}
		}
		// Sw
		if (op == 43) {
			CURRENT_STATE.EX_MEM_ALU_OUT = reg1 + imm;
			CURRENT_STATE.EX_MEM_W_VALUE = reg2;
		}
		// R types
		if (op == 0) {
			// Addu
			if (func == 33) {
				CURRENT_STATE.EX_MEM_ALU_OUT = reg1 + reg2;
				CURRENT_STATE.EX_MEM_DEST = RD(inst);
			}
			// And
			if (func == 36) {
				CURRENT_STATE.EX_MEM_ALU_OUT = reg1 & reg2;
				CURRENT_STATE.EX_MEM_DEST = RD(inst);
			}
			// Nor
			if (func == 39) {
				CURRENT_STATE.EX_MEM_ALU_OUT = ~(reg1 | reg2);
				CURRENT_STATE.EX_MEM_DEST = RD(inst);
			}
			// Or
			if (func == 37) {
				CURRENT_STATE.EX_MEM_ALU_OUT = reg1 | reg2;
				CURRENT_STATE.EX_MEM_DEST = RD(inst);
			}
			// Sltu
			if (func == 43) {
				if (reg1 < reg2) {
					CURRENT_STATE.EX_MEM_ALU_OUT = 1;
					CURRENT_STATE.EX_MEM_DEST = RD(inst);
				} else {
					CURRENT_STATE.EX_MEM_ALU_OUT = 0;
					CURRENT_STATE.EX_MEM_DEST = RD(inst);
				}
			}
			// Sll
			if (func == 0) {
				CURRENT_STATE.EX_MEM_ALU_OUT = reg2 << sh;
				CURRENT_STATE.EX_MEM_DEST = RD(inst);
			}
			// Srl
			if (func == 2) {
				CURRENT_STATE.EX_MEM_ALU_OUT = reg2 >> sh;
				CURRENT_STATE.EX_MEM_DEST = RD(inst);
			}
			// Subu
			if (func == 35) {
				CURRENT_STATE.EX_MEM_ALU_OUT = reg1 - reg2;
				CURRENT_STATE.EX_MEM_DEST = RD(inst);
			}
		}
	}
}

void MEM_Stage(){

}
void WB_Stage(){

}  
