#pragma once
#include "DataStructures/Queue.h"
#include "Process.h"
class Processor
{
public:
	//Processor ProcessorFactory()
	Processor() {
		runningProcess = nullptr;
		blockedProcesses = new Queue<Process*>();
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
	virtual Process* RemoveProcess() {
		
	};
	void IncrementExecutingTime() {
		if (state == BUSY)
			executingTime++;
	}
	int GetExecutingTime() { return executingTime; }
	Process* GetRunningProcess() { return runningProcess; }
protected:

	Process* runningProcess;
	Queue<Process*>* blockedProcesses;
	State state;
	int executingTime;
	int waitingTime;
};

