#pragma once
#include "DataStructures/PriorityQueue.h"
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
	virtual void ScheduleAlgo() = 0;
	virtual void AddProcess(Process* process) {
		waitingTime += process->GetCPUTime();
	}
	Process* RemoveProcess() {
		Process* temp = nullptr;
		if (runningProcess) {
			temp = runningProcess;
			runningProcess = nullptr;
		}
		return temp;
	};
	void IncrementExecutingTime() {
		if (state == BUSY)
			executingTime++;
	}
	int GetExecutingTime() { return executingTime; }
	Process* GetRunningProcess() { return runningProcess; }
protected:

	Process* runningProcess;
	PriorityQueue<Process*>* readyProcesses;
	State state;
	int executingTime;
	int waitingTime;
};

