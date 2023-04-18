#pragma once
#include "DataStructures/PriorityQueue.h"
#include "DataStructures/LinkedList.h"
#include "Process.h"
class Processor
{
public:
	//Processor ProcessorFactory()
	Processor() {
		runningProcess = nullptr;
		readyProcesses = new PriorityQueue<Process*>();
		state = IDLE;
		executingTime = waitingTime = 0;
	}
	enum State
	{
		BUSY, IDLE
	};
	virtual void ScheduleAlgo() {
		if (state == IDLE)
		{
			state = BUSY;
			runningProcess = readyProcesses->Pop();
			readyIds->Remove(runningProcess->GetId());
			runningProcess->SetState(Process::RUN);
		}
	}
	virtual void AddProcess(Process* process) {
		waitingTime += process->GetCPUTime();
		readyIds->InsertEnd(process->GetId());
	}
	Process* RemoveProcess() {
		Process* temp = nullptr;
		if (state == BUSY) {
			state = IDLE;
			temp = runningProcess;
			runningProcess = nullptr;
		}
		return temp;
	};
	int GetReadyProcessesCount() {
		return readyProcesses->Size();
	}
	void IncrementExecutingTime() {
		if (state == BUSY)
			executingTime++;
	}
	int GetExecutingTime() { return executingTime; }
	Process* GetRunningProcess() { return runningProcess; }
	LinkedList<int>* GetReadyIDs() {
		return readyIds;
	}
	State GetState() { return state; }
protected:
	LinkedList<int>* readyIds;
	Process* runningProcess;
	PriorityQueue<Process*>* readyProcesses;
	State state;
	int executingTime;
	int waitingTime;
};

