#pragma once
#include "constants.h"
#include "pipelineRegisters.h"

class FetchStage
{
public:
	FetchStage();
	~FetchStage();
	void fetch(IFID_reg& if_id);

private:
	int m_PC;
	int m_InstrMem[INSTR_MEM_SIZE]; //Instruction memory. 32-bit instrcutions so vector of int is enough

	//loads the instructions from file to instr mem: TODO
	void load_instructions();
};

