#pragma once
#include "Processor.h"
#include "DataStructures/PriorityQueue.h"
class SJF : public Processor
{
	PriorityQueue<Process*, int> readyProcesses;
public:
	void ScheduleAlgo() override{

	}
	void AddProcess(Process* process) override {
		Processor::AddProcess(process);
		readyProcesses.Insert(process, process->GetCPUTime() * -1);
	}
};

