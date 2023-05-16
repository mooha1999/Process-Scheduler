#pragma once
#include "DataStructures/PriorityQueue.h"
#include "DataStructures/LinkedList.h"
#include "Process.h"
class Processor
{
public:
	//Processor ProcessorFactory()
	Processor() {
		runningProcess = finishedProcess = blockedProcess = nullptr;
		state = IDLE;
		executingTime = 0;
	}
	enum State
	{
		BUSY, IDLE
	};
	virtual void ScheduleAlgo() = 0;
	virtual void AddProcess(Process* process) {
		process->SetState(Process::RDY);
	};
	virtual int GetReadyProcessesCount() = 0;
	int GetExecutingTime() { return executingTime; }
	Process* GetRunningProcess() { return runningProcess; }
	Process* GetFinishedProcess() {
		auto ret = finishedProcess;
		finishedProcess = nullptr;
		return ret;
	}
	Process* GetBlockedProcess() {
		auto ret = blockedProcess;
		blockedProcess = nullptr;
		return blockedProcess;
	}
	virtual string GetReadyIDs() = 0;
	virtual string GetType() = 0;
	State GetState() { return state; }
protected:
	Process* runningProcess;
	Process* finishedProcess;
	Process* blockedProcess;
	State state;
	int executingTime;
};
