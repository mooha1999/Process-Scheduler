#pragma once
#include<fstream>
#include<iostream>
#include "DataStructures/PriorityQueue.h"
#include "DataStructures/LinkedList.h"
#include "Process.h"
#include "FCFS.h"
#include "RR.h"
#include "SJF.h"
#include "Processor.h"
#include "DataStructures/Queue.h"
#include <string>
using namespace std;
class Scheduler
{
public:
    Process* process;
    Processor* processor;
    LinkedList<FCFS>FCFSList;
    LinkedList<SJF>SJFList;
    LinkedList<RR>RRList;
    Scheduler(string file) {

    }
    void loadFromFile(string inputfile) {
        ifstream inputFile(inputfile);
        if (!inputFile.is_open()) {
            cout << "Error opening file." << endl;
            return;
        }
        int numFCFS, numSJF, numRR, timeSlice, RTF, MaxW, STL, numProcesses;
        double forkProb;
        inputFile >> numFCFS >> numSJF >> numRR;
        //---------------------------------------------------------------------------------
        inputFile >> timeSlice;
        //---------------------------------------------------------------------------------
        inputFile >> RTF >> MaxW >> STL >> forkProb;
        //---------------------------------------------------------------------------------
        inputFile >> numProcesses;
        //---------------------------------------------------------------------------------

        // Read each process and create a Process object

        for (int i = 0; i < numProcesses; i++) {
            int AT, PID, CT, N;
            inputFile >> AT >> PID >> CT >> N;
            Process p(PID, AT, CT);
            for (int j = 0; j < N; j++) {
                int IO_R, IO_D;
                inputFile >> IO_R >> IO_D;
                process->AddPair(IO_R, IO_D);
            }
            Newprocesses.enqueue(p);
        }

        // Create Processors based on input file data
        for (int i = 0; i < numFCFS; i++) {
            FCFS* fcfs = new FCFS();
            FCFSList.InsertEnd(fcfs);
        }
        for (int i = 0; i < numSJF; i++) {
            FCFS* sjf = new SJF();
            FCFSList.InsertEnd(sjf);
        }
        for (int i = 0; i < numRR; i++) {
            FCFS* rr = new RR(timeSlice);
            FCFSList.InsertEnd(timeSlice);
        }
    }
};
