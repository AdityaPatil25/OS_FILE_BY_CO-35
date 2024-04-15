#include <iostream>
#include <vector>
using namespace std;

class Process {
public:
    int id, arrival_time, burst_time, completion_time, turnaround_time, waiting_time;

    Process(int _id, int _arrival_time, int _burst_time)
        : id(_id), arrival_time(_arrival_time), burst_time(_burst_time),
          completion_time(0), turnaround_time(0), waiting_time(0) {}
};

class Scheduler {
public:
    void fcfs(vector<Process>& processes) {
        int time = 0;
        float total_waiting_time = 0, total_turnaround_time = 0;

        for (int i = 0; i < processes.size(); ++i) {
            if (processes[i].arrival_time > time) // If no process arrived yet, increment time
                time = processes[i].arrival_time;

            processes[i].completion_time = time + processes[i].burst_time;
            processes[i].turnaround_time = processes[i].completion_time - processes[i].arrival_time;
            processes[i].waiting_time = processes[i].turnaround_time - processes[i].burst_time;

            total_waiting_time += processes[i].waiting_time;
            total_turnaround_time += processes[i].turnaround_time;

            time = processes[i].completion_time; // Move time to next completion
        }

        displayResults(processes, total_waiting_time, total_turnaround_time);
    }

private:
    void displayResults(const vector<Process>& processes, float total_waiting_time, float total_turnaround_time) {
        cout << "Process\tArrival Time\tBurst Time\tCompletion Time\tTurnaround Time\tWaiting Time" << endl;
        for (const auto& p : processes) {
            cout << p.id << "\t\t" << p.arrival_time << "\t\t" << p.burst_time << "\t\t"
                 << p.completion_time << "\t\t" << p.turnaround_time << "\t\t" << p.waiting_time << endl;
        }

        cout << "Average Waiting Time: " << total_waiting_time / processes.size() << endl;
        cout << "Average Turnaround Time: " << total_turnaround_time / processes.size() << endl;
    }
};

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes;
    for (int i = 0; i < n; ++i) {
        cout << "Enter details for process " << i + 1 << endl;
        cout << "Arrival time: ";
        int arrival_time;
        cin >> arrival_time;
        cout << "Burst time: ";
        int burst_time;
        cin >> burst_time;
        processes.emplace_back(i + 1, arrival_time, burst_time);
    }

    Scheduler scheduler;
    scheduler.fcfs(processes);

    return 0;
}
