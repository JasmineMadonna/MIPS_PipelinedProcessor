#pragma once
#include "constants.h"
#include "pipelineRegisters.h"

class ExecuteStage
{
public:
	ExecuteStage();
	~ExecuteStage();

	void execute(IDEX_reg& idEx_reg, EXMEM_reg& exMem_reg);

private:
	int alu(int A, int B, int alu_ctrl);
	int derive_ALU_cntrl(int funct, int ALUop);
};

