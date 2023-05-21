#pragma once
#include "Processor.h"
#include <string>;
using namespace std;
class FCFS : public Processor
{
	LinkedList<Process*>* readyProcesses = new LinkedList<Process*>();
public:
	void ScheduleAlgo(int timestep) {
		if (!readyProcesses->IsEmpty() && !runningProcess) {
			runningProcess = (*readyProcesses)[0];
			readyProcesses->Remove(runningProcess);
			runningProcess->SetState(Process::RUN);
			if (runningProcess->GetExecutionTime() == 0)
				runningProcess->SetResponseTime(timestep);
			return;
		}
		switch (runningProcess->GetState())
		{
		case Process::RUN:
		case Process::ORPH:
			runningProcess->IncrementExecutionTime();
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
		readyProcesses->InsertEnd(process);
	}
	int GetReadyProcessesCount() {
		return readyProcesses->Size();
	}
	Process* forkProcess(int id, int timestep) {
		Process* ret = nullptr;
		//Check running process
		if (runningProcess && runningProcess->GetState() == Process::RUN) {
			ret = runningProcess->Fork(id, timestep);
		}
		return ret;
	}
	Queue<Process*> killProcess(int id, int timestep) {
		Queue<Process*> ret;
		//Check running process
		if (runningProcess && runningProcess->GetId() == id) {
			ret = runningProcess->KillProcess(timestep);
			runningProcess = nullptr;
		}
		else {
			Process* toBeRemoved = nullptr;
			for (auto i : *readyProcesses) {
				if (i->GetId() == id) {
					ret = i->KillProcess(timestep);
					toBeRemoved = i;
					break;
				}
			}
			if (!ret.IsEmpty()) readyProcesses->Remove(toBeRemoved);
		}
		return ret;
	}
	string GetType() { return "FCFS"; }
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
	int GetWaitingTime() {
		int wt = 0;
		for (auto i : *readyProcesses) {
			wt += i->GetRemainingTime();
		}
		return wt;
	}
};
