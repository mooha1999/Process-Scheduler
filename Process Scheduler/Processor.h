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
	virtual void ScheduleAlgo() {
		if (state == IDLE)
		{
			state = BUSY;
			runningProcess = readyProcesses->Pop();
			runningProcess->SetState(Process::RUN);
		}
	}
	virtual void AddProcess(Process* process) {
		waitingTime += process->GetCPUTime();
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

