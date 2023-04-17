#pragma once
#include "Processor.h"
class RR : public Processor
{
	int threshold;
public:
	RR(int threshold) : Processor() {
		this->threshold = threshold;
	}
	void ScheduleAlgo() override {
		Processor::ScheduleAlgo();
	}
	void AddProcess(Process* process) override {
		Processor::AddProcess(process);
		readyProcesses->Insert(process, process->GetArrivalTime());
	}
	
};

