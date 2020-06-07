#pragma once

#include "pipelineRegisters.h"
#include "fetchStage.h"
#include "decodeStage.h"
#include "memStage.h"
#include "executeStage.h"

class Processor
{
private:
	FetchStage* fetch;
	DecodeStage* decode;
	ExecuteStage* execute;
	MemStage* memStage;

	IFID_reg ifId_reg;
	IDEX_reg idEx_reg;
	EXMEM_reg exMem_reg;
	MEMWB_reg memWb_reg;

	int cycles;

	void initialize_pipe_reg();

public:
	Processor();
	~Processor();
	void run();
	void printState();
};
