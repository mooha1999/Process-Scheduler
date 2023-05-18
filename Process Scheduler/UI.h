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
	void displayIDs(Queue<Process*> processes) {
		while (!processes.IsEmpty())
		{
			cout << processes.Pop()->GetId() << ", ";
		}
		cout << endl;
	}
public:
	void displayStartMessage() {
		cout << "Simulation started in Interactive mode\n";
	}
	void displayInfo(int timestep, LinkedList<FCFS*> fcfsList, LinkedList<SJF*> sjfList, LinkedList<RR*> rrList,
		Queue<Process*> blockedProcesses, Queue<Process*> terminatedProcesses)
	{
		cout << "Current timestep: " << timestep << endl;
		cout << "--------- RDY processes ---------\n";
		int runningProcessorsCount = 0;
		int I = 1;
		for (FCFS* processor : fcfsList) {
			cout << "Processor " << I++ << "[FCFS]: " << processor->GetReadyProcessesCount() << "RDY: " << processor->GetReadyIDs() << endl;
			if (processor->GetRunningProcess()) runningProcessorsCount++;
		}
		for (SJF* processor : sjfList) {
			cout << "Processor " << I++ << "[SJF]: " << processor->GetReadyProcessesCount() << "RDY: " << processor->GetReadyIDs() << endl;
			if (processor->GetRunningProcess()) runningProcessorsCount++;
		}
		for (RR* processor : rrList) {
			cout << "Processor " << I++ << "[RR]: " << processor->GetReadyProcessesCount() << "RDY: " << processor->GetReadyIDs() << endl;
			if (processor->GetRunningProcess()) runningProcessorsCount++;
		}

		cout << "--------- BLK processes ---------\n";
		cout << blockedProcesses.Size() << " BLK: ";
		displayIDs(blockedProcesses);

		cout << "--------- RUN processes ---------\n";
		cout << runningProcessorsCount << " RUN: ";

		I = 1;
		for (FCFS* processor : fcfsList) {
			if (processor->GetRunningProcess()) {
				cout << processor->GetRunningProcess()->GetId() << " (P" << I << "), ";
			}
			I++;
		}
		for (SJF* processor : sjfList) {
			if (processor->GetRunningProcess()) {
				cout << processor->GetRunningProcess()->GetId() << " (P" << I << "), ";
			}
			I++;
		}
		for (RR* processor : rrList) {
			if (processor->GetRunningProcess()) {
				cout << processor->GetRunningProcess()->GetId() << " (P" << I << "), ";
			}
			I++;
		}
		cout << "--------- TRM processes ---------\n";
		cout << terminatedProcesses.Size() << " TRM: " << endl;
		displayIDs(terminatedProcesses);
		cout << "Enter any key to continue";
		getchar();
	}
	void displayEndMessage() {
		cout << "Simulation ended";
	}
};
