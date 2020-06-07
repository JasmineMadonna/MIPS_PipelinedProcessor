#include "memStage.h"

MemStage::MemStage()
{
}

MemStage::~MemStage()
{
}

void MemStage::accessMemory(EXMEM_reg& exMem_reg, MEMWB_reg& memWb_reg)
{
	if (exMem_reg.memRead)
		memWb_reg.load_data = DataMemory[exMem_reg.alu_result];

	if (exMem_reg.memWrite)
		DataMemory[exMem_reg.alu_result] = exMem_reg.mem_write_data;

	/*Pass other data and control*/
	memWb_reg.alu_result = exMem_reg.alu_result;
	memWb_reg.memToReg = exMem_reg.memToReg;
	memWb_reg.write_register = exMem_reg.write_register;

	memWb_reg.opcode = exMem_reg.opcode;
}