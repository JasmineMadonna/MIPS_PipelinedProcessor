#include "decodeStage.h"
#include <iostream>

DecodeStage::DecodeStage()
{
	for (int i = 0; i < 31; i++)
		RegisterFile[i] = i;

	RegisterFile[1] = 5;
	RegisterFile[2] = 10;
}

DecodeStage::~DecodeStage()
{
}

void DecodeStage::decode(IFID_reg& decode_in, IDEX_reg& idEx_reg)
{
	int instr = decode_in.instr;

	idEx_reg.next_PC = decode_in.next_PC;

	/*Split instruction*/
	idEx_reg.funct = instr & ((1 << FUNCT_LEN) - 1);
	int shamt = (instr >> FUNCT_LEN)& ((1 << SHAMT_LEN) - 1);
	idEx_reg.rd = (instr >> (FUNCT_LEN + SHAMT_LEN))& ((1 << RD_LEN) - 1);
	int rt = (instr >> (FUNCT_LEN + SHAMT_LEN + RD_LEN))& ((1 << RT_LEN) - 1);
	int rs = (instr >> (FUNCT_LEN + SHAMT_LEN + RD_LEN + RT_LEN))& ((1 << RS_LEN) - 1);
	int opcode = (instr >> (INSTR_LEN - OPCODE_LEN))& ((1 << OPCODE_LEN) - 1);

	idEx_reg.opcode = opcode;

	/*For I format instructions*/
	idEx_reg.imm = instr & ((1 << IMM_LEN) - 1);
	idEx_reg.rt = rt;

	derive_controls(idEx_reg, opcode);

	//std::cout << "ALUOp : " << idEx_reg.ALUOp << "\n";
	/*Access register file*/
	idEx_reg.readData1 = RegisterFile[rs];
	idEx_reg.readData2 = RegisterFile[rt];
}

void DecodeStage::write_back(MEMWB_reg memWb_reg)
{
	if (memWb_reg.memToReg == 1)
		RegisterFile[memWb_reg.write_register] = memWb_reg.load_data;
	else if (memWb_reg.memToReg == 0)
		RegisterFile[memWb_reg.write_register] = memWb_reg.alu_result;
}

void DecodeStage::print_rf_contents()
{
	for (int i = 0; i < 10; i++)
		std::cout << "RF of " << i << "  :  " << RegisterFile[i] << "\n";
}

void DecodeStage::derive_controls(IDEX_reg& idEx_reg, int opcode)
{
	switch (opcode)
	{
	case 0:
	{
		idEx_reg.regDst = 1;
		idEx_reg.ALUSrc = 0;
		idEx_reg.memToReg = 0;
		idEx_reg.regWrite = 1;
		idEx_reg.memRead = 0;
		idEx_reg.memWrite = 0;
		idEx_reg.branch = 0;
		idEx_reg.ALUOp = 2;
		break;
	}
	case 35:
	{
		idEx_reg.regDst = 0;
		idEx_reg.ALUSrc = 1;
		idEx_reg.memToReg = 1;
		idEx_reg.regWrite = 1;
		idEx_reg.memRead = 1;
		idEx_reg.memWrite = 0;
		idEx_reg.branch = 0;
		idEx_reg.ALUOp = 0;
		break;
	}
	case 43:
	{
		idEx_reg.regDst = DONT_CARE;
		idEx_reg.ALUSrc = 1;
		idEx_reg.memToReg = DONT_CARE;
		idEx_reg.regWrite = 0;
		idEx_reg.memRead = 0;
		idEx_reg.memWrite = 1;
		idEx_reg.branch = 0;
		idEx_reg.ALUOp = 0;
		break;
	}
	case 4:
	{
		idEx_reg.regDst = DONT_CARE;
		idEx_reg.ALUSrc = 0;
		idEx_reg.memToReg = DONT_CARE;
		idEx_reg.regWrite = 0;
		idEx_reg.memRead = 0;
		idEx_reg.memWrite = 0;
		idEx_reg.branch = 1;
		idEx_reg.ALUOp = 1;
		break;
	}
	default:
		break;
	}
}