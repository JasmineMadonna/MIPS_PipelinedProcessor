#pragma once
#include "constants.h"
#include "pipelineRegisters.h"

class MemStage
{
public:
	MemStage();
	~MemStage();

	void accessMemory(EXMEM_reg& exMem_reg, MEMWB_reg& memWb_reg);

private:
	int DataMemory[DATA_MEM_SIZE];
};
