#pragma once

struct IFID_reg
{
	int next_PC;
	int instr;
};

struct IDEX_reg
{
	int next_PC;
	int rd;
	int rt;
	int readData1; //RF[rs]
	int readData2; //RF[rt]
	int imm;
	int funct;
	int opcode;

	//Controls
	short regDst;
	short ALUSrc;
	short PCSrc;
	short memToReg;
	short regWrite;
	short memRead;
	short memWrite;
	short branch;
	short ALUOp;
};

struct EXMEM_reg
{
	short branch_out;
	int alu_result;
	int write_register; //The register to which data has to be written
	int mem_write_data;
	int opcode;

	//Controls
	short memWrite;
	short memRead;
	short memToReg;
};

struct MEMWB_reg
{
	int write_register;
	int load_data;
	int alu_result;
	short memToReg;
	int opcode;
};

