#include "fetchStage.h"

FetchStage::FetchStage()
{
	m_PC = 0;
	load_instructions();
}

FetchStage::~FetchStage()
{
}

void FetchStage::fetch(IFID_reg& if_id)
{
	if_id.instr = m_InstrMem[m_PC];
	m_PC = m_PC + 1;
	if_id.next_PC = m_PC;
}

//loads the instructions from file to instr mem: TODO
void FetchStage::load_instructions()
{
	//m_InstrMem[0] = 0; // NOP
	m_InstrMem[0] = 2234400;
	m_InstrMem[1] = 8728610;
	m_InstrMem[2] = 15222820;
	m_InstrMem[3] = 4227858432; //hlt instr
}