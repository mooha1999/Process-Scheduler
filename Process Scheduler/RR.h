#pragma once
#include "Processor.h"
class RR : public Processor
{
	int threshold;
	Queue<Process*>* readyProcesses;
public:
	RR(int threshold) : Processor() {
		this->threshold = threshold;
		readyProcesses = new Queue<Process*>();
	}
	void ScheduleAlgo(int timestep) {
		if (!readyProcesses->IsEmpty() && !runningProcess) {
			runningProcess = readyProcesses->Pop();
			runningProcess->SetState(Process::RUN);
			runningProcess->SetResponseTime(timestep);
			return;
		}
		switch (runningProcess->GetState())
		{
		case Process::RUN:
			runningProcess->IncrementExecutionTime();
			if (runningProcess->GetExecutionTime() % threshold == 0) {
				AddProcess(runningProcess);
				runningProcess = nullptr;
			}
			break;
		case Process::BLK:
			blockedProcess = runningProcess;
			runningProcess = nullptr;
			break;
		case Process::TRM:
			finishedProcess = runningProcess;
			finishedProcess->SetTerminationTime(timestep);
			runningProcess = nullptr;
			break;
		default:
			break;
		}
		executingTime++;
	}
	void AddProcess(Process* process) {
		Processor::AddProcess(process);
		readyProcesses->Push(process);
	}
	int GetReadyProcessesCount() {
		return readyProcesses->Size();
	}
	string GetType() { return "RR"; }
	string GetReadyIDs() {
		string ret = "";
		for (auto i : *readyProcesses) {
			ret += to_string(i->GetId());
			ret += ", ";
		}
		if (ret.size() > 0) {
			ret.pop_back();
			ret.pop_back();
		}
		return ret;
	}
};
