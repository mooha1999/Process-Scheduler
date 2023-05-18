#pragma once
#include "DataStructures/Queue.h"
#include "DataStructures/Pair.h"
class Process
{
public:
	enum State {
		NEW, RDY, RUN, BLK, TRM, ORPH
	};
private:
	//********Data fetched from file**********
	int id;
	int arrivalTime;
	int cpuTime;
	Queue<Pair<int, int>*>* ioRequests;
	//********Computed Data*********
	int responseTime;
	int terminationTime;
	int executionTime;
	int ioTime;
	State state;
	Process* child;
public:
	Process(int id, int arrivalTime, int cpuTime) {
		this->id = id;
		this->arrivalTime = arrivalTime;
		this->cpuTime = cpuTime;
		executionTime = ioTime = 0;
		responseTime = terminationTime = -1;
		state = State::NEW;
		ioRequests = new Queue<Pair<int, int>*>();
		child = nullptr;
	}

	//	Add a pair of integers to the ioRequests queue.
	//	@param io_r execution interval after which process requests for I/O resources. @param io_d time duration for a process to perform some I/O task.
	void AddPair(int io_r, int io_d) {
		ioRequests->Push(new Pair<int, int>(io_r, io_d));
	}
	//
	//	Sets the response time of a process.
	//	@param responseTime the time the process gets the CPU fot the first time.
	//
	void SetResponseTime(int responseTime) {
		this->responseTime = responseTime - arrivalTime;
	}
	void SetTerminationTime(int terminationTime) {
		this->terminationTime = terminationTime;
	}
	void SetState(State state) {
		this->state = state;
	}

	//	increment the process execution time by one if it is in the running state
	void IncrementExecutionTime() {
		if (state == RUN)
			executionTime++;
		if (!ioRequests->IsEmpty() && executionTime == GetTopIO()->GetFirst()) {
			state = BLK;
		}
		else if (executionTime == cpuTime) {
			state = TRM;
		}
	}
	//	increment the process IO time by one if it is in the BLK state
	void IncrementIOTime() {
		if (state == BLK)
			ioTime++;
	}
	int GetId() { return id; }
	int GetArrivalTime() { return arrivalTime; }
	int GetCPUTime() { return cpuTime; }
	// Can be used with GetCPUTime() to check if the cpuTime is equal to executionTime
	int GetExecutionTime() { return executionTime; }
	int GetResponseTime() { return responseTime; }
	int GetTerminationTime() { return terminationTime; }
	int GetIOTime() { return ioTime; }
	int GetTurnaroundTime() {
		return terminationTime - arrivalTime;
	}
	int GetWaitingTime() {
		return GetTurnaroundTime() - cpuTime;
	}
	int GetRemainingTime() {
		return cpuTime - executionTime;
	}
	Queue<Pair<int, int>*>* GetIORequests() { return ioRequests; }
	Pair<int, int>* RemoveTopIO() {
		return ioRequests->IsEmpty() ? nullptr : ioRequests->Pop();
	}
	Pair<int, int>* GetTopIO() {
		return ioRequests->IsEmpty() ? nullptr : ioRequests->Peek();
	}

	State GetState() { return state; }
	Process* Fork(int id, int arrivalTime) {
		child = new Process(id, arrivalTime, GetRemainingTime());
		child->SetState(ORPH);
		return child;
	}
	Queue<Process*> KillProcess(int timestep) {
		Queue<Process*> processes;
		Process* temp = this;
		while (temp)
		{
			temp->state = TRM;
			temp->terminationTime = timestep;
			processes.Push(temp);
			temp = temp->child;
		}

		return processes;
	}
};
