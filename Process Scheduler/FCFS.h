#pragma once
#include "Processor.h"
class FCFS : public Processor
{
public:
	void ScheduleAlgo() override {

	}
	void AddProcess(Process* process) override {
		Processor::AddProcess(process);
		readyProcesses->Insert(process, process->GetArrivalTime());
	}
};

