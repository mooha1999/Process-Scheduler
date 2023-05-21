#pragma once
#include "DataStructures/LinkedList.h"

#include <iostream>
#include <Windows.h>
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
	int choice = 0;
public:
	void displayStartMessage() {
		cout << "Enter Mode:\n[1] Interactive\n[2] Step-by-Step\n[3] Silent\n";
		cin >> choice;
		cout << "Simulation started in Interactive mode\n";
	}
	void displayInfo(int timestep, LinkedList<FCFS*> fcfsList, LinkedList<SJF*> sjfList, LinkedList<RR*> rrList,
		Queue<Process*> blockedProcesses, Queue<Process*> terminatedProcesses)
	{
		if (choice == 3)
			return;
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
		if (choice == 1) {
			cout << "Enter any key to continue";
			getchar();
		}
		else {
			Sleep(1000);
		}
	}
	void displayEndMessage() {
		cout << "Simulation ended";
	}
};
