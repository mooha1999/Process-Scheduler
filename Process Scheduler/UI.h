#pragma once
#include "DataStructures/LinkedList.h"

#include <iostream>
#include "Processor.h"
#include <string>
#include "SJF.h"
#include "FCFS.h"
#include "RR.h"
using namespace std;
class UI
{
	void displayProcessorInfo(Processor* processor)
	{
		cout << "[" + getProcessorType(processor) + "]: " << processor->GetReadyProcessesCount() << "RDY : ";
		auto ids = *processor->GetReadyIDs();
		for (int i = 0; i < ids.Size(); i++) {
			cout << ids[i] << ", ";
		}
	}
	void displayIDs(Queue<Process*> processes) {
		while (!processes.IsEmpty())
		{
			cout << processes.Pop()->GetId() << ", ";
		}
	}
	string getProcessorType(Processor* processor) {
		SJF* sjf = dynamic_cast<SJF*>(processor);
		if (sjf)
			return "SJF";
		FCFS* fcfs = dynamic_cast<FCFS*>(processor);
		if (fcfs)
			return "FCFS";
		RR* rr = dynamic_cast<RR*>(processor);
		if (rr)
			return "RR";
	}
public:
	void displayStartMessage() {
		cout << "Simulation started in Interactive mode\n";
	}
	void displayInfo(int timestep, LinkedList<FCFS*> fcfsq, LinkedList<SJF*> sjfq, LinkedList<RR*> rrq,
		Queue<Process*> blockedProcesses, Queue<Process*> terminatedProcesses)
	{
		cout << "Current timestep: " << timestep << endl;
		cout << "--------- RDY processes ---------\n";
		int runningProcessorsCount = 0;
		Queue<Processor*> runningProcessors;

		for (int i = 0; i < processors->Size(); i++) {
			auto temp = processors->operator[](i);
			cout << "Processor " << i + 1 << " ";
			displayProcessorInfo(temp);
			if (temp->GetState() == Processor::BUSY)
				runningProcessors.Push(temp);
		}

		cout << "--------- BLK processes ---------\n";
		cout << blockedProcesses->Size() << " BLK: ";
		displayIDs(*blockedProcesses);

		cout << "--------- RUN processes ---------\n";
		cout << runningProcessors.Size() << " RUN: ";
		int I = 1;
		while (!runningProcessors.IsEmpty()) {
			cout << runningProcessors.Pop()->GetRunningProcess()->GetId()
				<< "(P" + to_string(I++) + ")\n";
		}

		cout << "--------- TRM processes ---------\n";
		cout << terminatedProcesses->Size() << " TRM: " << endl;
		displayIDs(*terminatedProcesses);
		cout << "Enter any key to continue";
		getchar();
	}
	void displayEndMessage() {
		cout << "Simulation ended";
	}
};
