#include "processor.h"
#include "pipelineRegisters.h"
#include "fetchStage.h"
#include "memStage.h"
#include "decodeStage.h"
#include "executeStage.h"
#include "memStage.h"
#include <iostream>

Processor::Processor()
{
	fetch = new FetchStage();
	decode = new DecodeStage();
	execute = new ExecuteStage();
	memStage = new MemStage();

	/*Initiallize pipeline registers*/
	initialize_pipe_reg();

	cycles = 0;
}

Processor::~Processor()
{
	delete fetch;
	delete decode;
	delete execute;
	delete memStage;
}

void Processor::initialize_pipe_reg()
{
	/*Fetch to decode reg*/
	ifId_reg.next_PC = 0;
	ifId_reg.instr = 0;

	/*Decode to ex reg*/
	idEx_reg.next_PC = 0;
	idEx_reg.readData1 = 0;
	idEx_reg.readData2 = 0;
	idEx_reg.imm = 0;
	idEx_reg.funct = 0;
	idEx_reg.rd = 0;
	idEx_reg.rt = 0;

	idEx_reg.ALUOp = 2; //keeping default as AND
	idEx_reg.ALUSrc = 0;
	idEx_reg.regDst = 1; //default reg dest is rd field
	idEx_reg.regWrite = 0; //No reg write
	idEx_reg.PCSrc = 0;
	idEx_reg.memRead = 0;
	idEx_reg.memWrite = 0;
	idEx_reg.memToReg = 0;
	idEx_reg.opcode = 0;

	/*Ex to mem reg*/
	exMem_reg.memRead = 0;
	exMem_reg.memWrite = 0;
	exMem_reg.memToReg = 0;
	//exMem_reg.branch_out = 0;
	exMem_reg.alu_result = 0;
	exMem_reg.write_register = 0;
	exMem_reg.mem_write_data = 0;
	exMem_reg.opcode = 0;

	/*Mem to wb*/
	memWb_reg.alu_result = 0;
	memWb_reg.load_data = 0;
	memWb_reg.memToReg = 0;
	memWb_reg.write_register = 0;
	memWb_reg.opcode = 0;
}

void Processor::run()
{
	while (1)
	{
		if (memWb_reg.opcode == 63)
		{
			std::cout << "Machine halted \n";
			std::cout << "Cycles : " << cycles << "\n\n";
			decode->print_rf_contents();
			exit(0);
		}
		decode->write_back(memWb_reg);
		memStage->accessMemory(exMem_reg, memWb_reg);
		execute->execute(idEx_reg, exMem_reg);
		decode->decode(ifId_reg, idEx_reg);
		fetch->fetch(ifId_reg);

		printState();
		cycles++;
	}

}

void Processor::printState()
{
	std::cout << "Cycle : " << cycles << "\n";
	std::cout << "***** IF ID reg : ******\n";
	std::cout << "next PC : " << ifId_reg.next_PC << "\n";
	std::cout << "instr : " << ifId_reg.instr << "\n";

	std::cout << "***** ID EX reg : ******\n";
	std::cout << "next PC : " << idEx_reg.next_PC << "\n";
	std::cout << "read data 1 : " << idEx_reg.readData1 << "\n";
	std::cout << "read data 2 : " << idEx_reg.readData2 << "\n";
	std::cout << "opcode : " << idEx_reg.opcode << "\n";
	std::cout << "funct : " << idEx_reg.funct << "\n";
	std::cout << "rd : " << idEx_reg.rd << "\n";
	//std::cout << "read data 2 : " << ifId_reg.readData2 << "\n";
	std::cout << "ALUOp : " << idEx_reg.ALUOp << "\n";
	std::cout << "reg write : " << idEx_reg.regWrite << "\n";


	std::cout << "***** EX Mem reg : ******\n";
	std::cout << "opcode : " << exMem_reg.opcode << "\n";
	std::cout << "alu result : " << exMem_reg.alu_result << "\n";
	std::cout << "write reg : " << exMem_reg.write_register << "\n";

	std::cout << "***** Mem WB reg : ******\n";
	std::cout << "opcode : " << memWb_reg.opcode << "\n";
	std::cout << "alu result : " << memWb_reg.alu_result << "\n";
	std::cout << "write reg : " << memWb_reg.write_register << "\n";

	std::cout << "\n";
}


int main()
{
	Processor* processor = new Processor();
	processor->run();


	//FetchStage *fetch = new FetchStage();
	//std::cout << "Hello \n";

	return 0;
}