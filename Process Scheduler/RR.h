#pragma once
#include "Processor.h"
class RR : public Processor
{
	Queue<Process*>* readyProcesses;
	int threshold;
public:
	RR(int threshold) : Processor() {
		this->threshold = threshold;
		readyProcesses = new Queue<Process*>();
	}
	void ScheduleAlgo() override {

	}
	void AddProcess(Process* process) override {
		Processor::AddProcess(process);
		readyProcesses->Push(process);
	}
	
};

