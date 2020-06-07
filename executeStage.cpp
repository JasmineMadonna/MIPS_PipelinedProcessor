#include "executeStage.h"

ExecuteStage::ExecuteStage()
{
}

ExecuteStage::~ExecuteStage()
{
}

void ExecuteStage::execute(IDEX_reg& idEx_reg, EXMEM_reg& exMem_reg)
{
	int alu_cntrl = derive_ALU_cntrl(idEx_reg.funct, idEx_reg.ALUOp);

	/*Perform ALU operation choosing the correct ALU second operand*/
	int alu_result = 0;
	if (idEx_reg.ALUSrc == 0)
		alu_result = alu(idEx_reg.readData1, idEx_reg.readData2, alu_cntrl);
	else if (idEx_reg.ALUSrc == 1)
		alu_result = alu(idEx_reg.readData1, idEx_reg.imm, alu_cntrl);
	exMem_reg.alu_result = alu_result;

	/*Set the write register for next stage*/
	if (idEx_reg.regDst == 1)
		exMem_reg.write_register = idEx_reg.rd;
	else if (idEx_reg.regDst == 0)
		exMem_reg.write_register = idEx_reg.rt;

	exMem_reg.mem_write_data = idEx_reg.readData2;
	/*Pass control signals to mem stage*/
	exMem_reg.memRead = idEx_reg.memRead;
	exMem_reg.memWrite = idEx_reg.memWrite;
	exMem_reg.memToReg = idEx_reg.memToReg;

	exMem_reg.opcode = idEx_reg.opcode;

}

/*Perform the ALU operation corresponding to the alu_cntrl*/
int ExecuteStage::alu(int A, int B, int alu_ctrl)
{
	switch (alu_ctrl)
	{
	case 0:
		return A & B;
	case 1:
		return A | B;
	case 2:
		return A + B;
	case 6:
		return A - B;
	default:
		return A + B; //default is add
	}
}

int ExecuteStage::derive_ALU_cntrl(int funct, int ALUop)
{
	if (ALUop == 0)
		return 2;
	else if (ALUop == 1)
		return 6;
	else
	{
		switch (funct)
		{
		case 32:
			return 2;
		case 34:
			return 6;
		case 36:
			return 0;
		case 37:
			return 1;
		default:
			return 2; //default is add. TODO - check
		}
	}
}