#pragma once
#include "Processor.h"
class FCFS : public Processor
{
public:
	void ScheduleAlgo() override {
		Processor::ScheduleAlgo();
	}
	void AddProcess(Process* process) override {
		Processor::AddProcess(process);
		readyProcesses->Insert(process, process->GetArrivalTime());
	}
	// Returns the process with the given ID. If not found returns nullptr
	// @param id:  The id to search with
	Process* TerminateProcess(int id) {
		Process* ret = nullptr;
		PriorityQueue<Process*>* tempQueue = new PriorityQueue<Process*>();
		while (!readyProcesses->IsEmpty()) {
			Process* tempProcess = readyProcesses->Pop();
			if (tempProcess->GetId() == id)
				ret = tempProcess;
			else
				tempQueue->Insert(tempProcess, tempProcess->GetArrivalTime());
		}
		readyProcesses = tempQueue;
		return ret;
	}
};

