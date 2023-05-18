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
#include "UI.h"
#include "DataStructures/Queue.h"
#include <string>
using namespace std;
class Scheduler
{
public:
    Process* process;
    Processor* processor;
    LinkedList<FCFS*>FCFSList;
    LinkedList<SJF*>SJFList;
    LinkedList<RR*>RRList;
    Queue<Process*>NewProcesses;
    Queue<Pair<int, int>*>* KillQueue;
    Queue<Process*>BlkQueue;
    Queue<Process*>TrmQueue;
    double forkProb;
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
        int killid, killtime;
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
            Process*p=new Process(PID, AT, CT);
            for (int j = 0; j < N; j++) {
                int IO_R, IO_D;
                inputFile >> IO_R >> IO_D;
                process->AddPair(IO_R, IO_D);
            }

            NewProcesses.Push(p);
        }

        // Create Processors based on input file data
        for (int i = 0; i < numFCFS; i++) {
            FCFS* fcfs = new FCFS();
            FCFSList.InsertEnd(fcfs);
        }
        for (int i = 0; i < numSJF; i++) {
            SJF* sjf = new SJF();
            SJFList.InsertEnd(sjf);
        }
        for (int i = 0; i < numRR; i++) {
            RR* rr = new RR(timeSlice);
            RRList.InsertEnd(rr);
        }
        while (inputFile >> killid >> killtime)
        {
            KillQueue->Push(new Pair<int, int>(killid, killtime));

        }
        
    }
    bool isFork() {
        return rand() % 100 < forkProb;
    }
    void Simulate()
    {
        UI ui;
        ui.displayStartMessage();
        int timestep = 0;
        while (true)
        {
            //NEW To RDY
            if (!NewProcesses.IsEmpty() && NewProcesses.Peek()->GetArrivalTime() == timestep)
            {
                Processor* shortestp;
                int x = 999999999;
                for(Processor* i : FCFSList)
                {
                    int gwt = i->GetWaitingTime();
                    if (gwt<x)
                    {
                        x = gwt;
                        shortestp = i;
                    }
                }
                for (Processor* i : SJFList)
                {
                    
                    int gwt = i->GetWaitingTime();
                    if (gwt < x)
                    {
                        x = gwt;
                        shortestp = i;
                    }
                }
                for (Processor* i : RRList)
                {
                    
                    int gwt = i->GetWaitingTime();
                    if (gwt < x)
                    {
                        x = gwt;
                        shortestp = i;
                    }
                }
                shortestp->AddProcess(NewProcesses.Pop());
               
            }
            // KillSig
            if (!KillQueue->IsEmpty() && KillQueue->Peek()->GetFirst() == timestep)
            {
                for (auto i : FCFSList)
                {

                    Queue<Process*>killedprocesses= i->killProcess(KillQueue->Peek()->GetSecond(), timestep);
                    for (auto i : killedprocesses)
                    {
                        i->SetTerminationTime(timestep);
                        TrmQueue.Push(i);
                    }

                }
            }
            // Forking
            for (Processor* i : FCFSList)
                {
                    if (i->GetRunningProcess() && isFork())
                    {
                     
                        Process*child= i->GetRunningProcess()->Fork(rand() % 1000, timestep); // Set appropriate ID
                        Processor* shortestprocessor;
                        int x = 999999999;
                        for (Processor* i : FCFSList)
                        {
                            int gwt = i->GetWaitingTime();
                            if (gwt < x)
                            {
                                x = gwt;
                                shortestprocessor = i;
                            }
                        }
                        shortestprocessor->AddProcess(child); // Forked child to shortest FCFS
                    }
                
            }
           
         // RUN to BLK
            for (Processor* i : FCFSList)
            {
                Process* pro = i->GetBlockedProcess();
                if (pro)
                {
                    BlkQueue.Push(pro);
                }
               
            }
            for (Processor* i : SJFList)
            {
                Process* pro = i->GetBlockedProcess();
                if (pro)
                {
                    BlkQueue.Push(pro);
                }
            }
            for (Processor* i : RRList)
            {
                Process* pro = i->GetBlockedProcess();
                if (pro)
                {
                    BlkQueue.Push(pro);
                }
            }
         // END RUN to BLK      
      
         // BLK to RDY
            if (!BlkQueue.IsEmpty())
            {
                if (BlkQueue.Peek()->GetIOTime() == BlkQueue.Peek()->GetIORequests()->Peek()->GetSecond())
                {
                    Process* processblked = BlkQueue.Pop();
                    processblked->GetIORequests()->Pop();
                    Processor* shortestp;
                    int x = 999999999;
                    for (Processor* i : FCFSList)
                    {
                        int gwt = i->GetWaitingTime();
                        if (gwt < x)
                        {
                            x = gwt;
                            shortestp = i;
                        }
                    }
                    for (Processor* i : SJFList)
                    {

                        int gwt = i->GetWaitingTime();
                        if (gwt < x)
                        {
                            x = gwt;
                            shortestp = i;
                        }
                    }
                    for (Processor* i : RRList)
                    {

                        int gwt = i->GetWaitingTime();
                        if (gwt < x)
                        {
                            x = gwt;
                            shortestp = i;
                        }
                    }
                    shortestp->AddProcess(processblked);
                }
                else
                {
                    BlkQueue.Peek()->IncrementIOTime();
                }
            }
         //End BLK to RDY
         
         //RUN to TRM
            for (Processor* i : FCFSList)
            {
                Process* pro = i->GetFinishedProcess();
                if (pro)
                {
                    pro->SetTerminationTime(timestep);
                    TrmQueue.Push(pro);
                }

            }
            for (Processor* i : SJFList)
            {
                Process* pro = i->GetFinishedProcess();
                if (pro)
                {
                    pro->SetTerminationTime(timestep);
                    TrmQueue.Push(pro);
                }
            }
            for (Processor* i : RRList)
            {
                Process* pro = i->GetFinishedProcess();
                if (pro)
                {
                    pro->SetTerminationTime(timestep);
                    TrmQueue.Push(pro);
                }
            }
         // END RUN to TRM
            
          

            ui.displayInfo(timestep,FCFSList,SJFList,RRList,BlkQueue,TrmQueue);
            timestep++;
        }
        ui.displayEndMessage();
    }


 
};
