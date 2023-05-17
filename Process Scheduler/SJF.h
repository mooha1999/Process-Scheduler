#pragma once
#include "Processor.h"
#include "DataStructures/PriorityQueue.h"
class SJF : public Processor
{
	PriorityQueue<Process*>* readyProcesses;
public:
	void ScheduleAlgo(int timestep) {
		if (!readyProcesses->IsEmpty() && !runningProcess) {
			runningProcess = readyProcesses->Pop();
			runningProcess->SetState(Process::RUN);
			if (runningProcess->GetExecutionTime() == 0)
				runningProcess->SetResponseTime(timestep);
			return;
		}
		switch (runningProcess->GetState())
		{
		case Process::RUN:
			runningProcess->IncrementExecutionTime();
			executingTime++;
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
	}

	void AddProcess(Process* process) {
		Processor::AddProcess(process);
		readyProcesses->Insert(process, process->GetRemainingTime() * -1); //Sorting by CPU time
	}
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
	int GetReadyProcessesCount() {
		return readyProcesses->Size();
	}
	string GetType() { return "SJF"; }
	int GetWaitingTime() {
		int wt = 0;
		for (auto i : *readyProcesses) {
			wt += i->GetRemainingTime();
		}
		return wt;
	}
};
