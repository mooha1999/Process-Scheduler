#pragma once
#include "Processor.h"
class FCFS : public Processor
{
	Queue<Process*> readyProcesses;
public:
	void ScheduleAlgo() override {

	}
	void AddProcess(Process* process) override {
		Processor::AddProcess(process);
	}
};

