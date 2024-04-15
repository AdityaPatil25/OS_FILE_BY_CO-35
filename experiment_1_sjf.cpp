#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

class Process {
public:
    int id;
    int arrivalTime;
    int burstTime;
    bool completed;

    Process(int _id, int _arrivalTime, int _burstTime) : id(_id), arrivalTime(_arrivalTime), burstTime(_burstTime), completed(false) {}
};

bool compareArrivalTime(const Process &a, const Process &b) {
    return a.arrivalTime < b.arrivalTime;
}

bool compareBurstTime(const Process &a, const Process &b) {
    return a.burstTime < b.burstTime;
}

class Scheduler {
public:
    void shortestJobFirst(vector<Process> &processes) {
        int n = processes.size();
        sort(processes.begin(), processes.end(), compareArrivalTime);

        int currentTime = 0;
        int totalWaitTime = 0;
        int totalTurnaroundTime = 0;
        int completedProcesses = 0;

        cout << "Pid\tAT\tBT\tWT\tTAT\n";

        while (completedProcesses < n) {
            int shortestBurst = numeric_limits<int>::max();
            int shortestIndex = -1;

            for (int i = 0; i < n; i++) {
                if (!processes[i].completed && processes[i].arrivalTime <= currentTime && processes[i].burstTime < shortestBurst) {
                    shortestBurst = processes[i].burstTime;
                    shortestIndex = i;
                }
            }

            if (shortestIndex == -1) {
                currentTime++;
                continue; // No process remaining to execute, move to next time unit
            }

            Process &currentProcess = processes[shortestIndex];
            currentProcess.completed = true;

            cout << currentProcess.id << "\t" << currentProcess.arrivalTime << "\t" << currentProcess.burstTime << "\t";

            totalWaitTime += currentTime - currentProcess.arrivalTime;
            totalTurnaroundTime += currentTime + currentProcess.burstTime - currentProcess.arrivalTime;

            currentTime += currentProcess.burstTime;

            cout << currentTime - currentProcess.arrivalTime - currentProcess.burstTime << "\t";
            cout << currentTime - currentProcess.arrivalTime << endl;

            completedProcesses++;
        }

        cout << "Average Waiting Time: " << static_cast<double>(totalWaitTime) / n << endl;
        cout << "Average Turnaround Time: " << static_cast<double>(totalTurnaroundTime) / n << endl;
    }
};

int main() {
    vector<Process> processes = {// for each process
        Process(1, 0, 6),        //{pid,AT,BT}
        Process(2, 2, 8),
        Process(3, 5, 7),
        Process(4, 5, 3)
    };

    Scheduler scheduler;
    scheduler.shortestJobFirst(processes);

    return 0;
}
