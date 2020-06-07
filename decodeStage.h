#pragma once
#include "constants.h"
#include "pipelineRegisters.h"

class DecodeStage
{
public:
	DecodeStage();
	~DecodeStage();

	void decode(IFID_reg& decode_in, IDEX_reg& idEx_reg);
	void write_back(MEMWB_reg memWb_reg);
	void print_rf_contents();

private:
	int RegisterFile[32]; //32 registers

	/*Set the control signals based on the opcode*/
	void derive_controls(IDEX_reg& idEx_reg, int opcode);
};
