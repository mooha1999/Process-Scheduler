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
	State state;
public:
	Process(int id, int arrivalTime, int cpuTime) {
		this->id = id;
		this->arrivalTime = arrivalTime;
		this->cpuTime = cpuTime;
		executionTime = 0;
		responseTime = terminationTime = -1;
		state = NEW;
		ioRequests = new Queue<Pair<int, int>*>();
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
	void SetState(State state) {
		this->state = state;
	}
	
	//	increment the process execution time by one if it is in the running state
	void IncrementExecutionTime() {
		if (state == RUN)
			executionTime++;
	}

	int GetId() { return id; }
	int GetArrivalTime() { return arrivalTime; }
	int GetCPUTime() { return cpuTime; }
	// Can be used with GetCPUTime() to check if the cpuTime is equal to executionTime
	int GetExecutionTime() { return executionTime; }
	int GetResponseTime() { return responseTime; }
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
	State GetState() { return state; }

};

