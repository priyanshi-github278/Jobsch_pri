//Projects III: Job Scheduler design and implemention in C++
//Write a C++ Program to Simulate Job Scheduler for in a Supercomputer

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <fstream>

using namespace std;

// Structure for Job
struct Job {
    int JobId;
    int ArrivalDay;
    int ArrivalHour;
    int MemReq;
    int CPUReg;
    int ExeTime;
    int JobSize;  // For Smallest Job First

    // Constructor
    Job(int id, int day, int hour, int mem, int cpu, int exe)
        : JobId(id), ArrivalDay(day), ArrivalHour(hour), MemReq(mem), CPUReg(cpu), ExeTime(exe) {
        JobSize = exe * cpu * mem;
    }
};

// Structure for Worker Node
struct WorkerNode {
    int availableMem;
    int availableCPU;

    WorkerNode(int mem, int cpu) : availableMem(mem), availableCPU(cpu) {}
};

// Class for Job Scheduler
class JobScheduler {
public:
    void addJob(int JobId, int ArrivalDay, int ArrivalHour, int MemReq, int CPUReg, int ExeTime) {
        jobs.push_back(Job(JobId, ArrivalDay, ArrivalHour, MemReq, CPUReg, ExeTime));
    }

    void sortJobs(string policy) {
        if (policy == "FCFS") {
            // FCFS: Sort by arrival time
            sort(jobs.begin(), jobs.end(), [](Job a, Job b) {
                return a.ArrivalHour < b.ArrivalHour;
            });
        } else if (policy == "ShortestDuration") {
            // Shortest Duration First: Sort by execution time
            sort(jobs.begin(), jobs.end(), [](Job a, Job b) {
                return a.ExeTime < b.ExeTime;
            });
        } else if (policy == "SmallestJob") {
            // Smallest Job First: Sort by job size
            sort(jobs.begin(), jobs.end(), [](Job a, Job b) {
                return a.JobSize < b.JobSize;
            });
        }
    }

    void allocateJobs(string fitPolicy) {
        for (auto& job : jobs) {
            bool jobAllocated = false;
            for (auto& node : workerNodes) {
                if (fitPolicy == "FirstFit") {
                    if (node.availableMem >= job.MemReq && node.availableCPU >= job.CPUReg) {
                        node.availableMem -= job.MemReq;
                        node.availableCPU -= job.CPUReg;
                        jobAllocated = true;
                        break;
                    }
                }
                // Implement other fit policies (BestFit, WorstFit) here
            }
            if (!jobAllocated) {
                cout << "Job " << job.JobId << " could not be allocated." << endl;
            }
        }
    }

    void printJobs() {
        for (const auto& job : jobs) {
            cout << "JobId: " << setw(2) << job.JobId
                 << " Arrival Day: " << setw(2) << job.ArrivalDay
                 << " Time Hour: " << setw(2) << job.ArrivalHour
                 << " MemReq: " << setw(3) << job.MemReq
                 << " CPUReg: " << setw(3) << job.CPUReg
                 << " ExeTime: " << setw(2) << job.ExeTime << endl;
        }
    }

    void addWorkerNode(int mem, int cpu) {
        workerNodes.push_back(WorkerNode(mem, cpu));
    }

    void saveResultsToCSV(const string& filename) {
        ofstream outFile(filename);
        outFile << "JobId,ArrivalDay,ArrivalHour,MemReq,CPUReg,ExeTime\n";
        for (const auto& job : jobs) {
            outFile << job.JobId << "," << job.ArrivalDay << "," << job.ArrivalHour << ","
                    << job.MemReq << "," << job.CPUReg << "," << job.ExeTime << "\n";
        }
        outFile.close();
    }

private:
    vector<Job> jobs;
    vector<WorkerNode> workerNodes;
};

int main() {
    JobScheduler scheduler;

    // Adding jobs
    scheduler.addJob(0, 0, 0, 7, 8, 6);
    scheduler.addJob(1, 0, 0, 14, 6, 7);
    scheduler.addJob(2, 0, 0, 13, 10, 2);
    scheduler.addJob(3, 0, 0, 3, 8, 1);
    scheduler.addJob(4, 0, 0, 20, 4, 7);
    scheduler.addJob(5, 0, 0, 1, 7, 3);
    scheduler.addJob(6, 0, 0, 17, 2, 9);
    scheduler.addJob(7, 0, 0, 8, 10, 3);
    scheduler.addJob(8, 0, 0, 11, 3, 4);

    // Adding worker nodes
    scheduler.addWorkerNode(64, 24); // 64GB RAM, 24 cores
    scheduler.addWorkerNode(64, 24); // Adding another worker node

    // Sort jobs based on FCFS policy
    scheduler.sortJobs("FCFS");

    // Allocate jobs using First Fit policy
    scheduler.allocateJobs("FirstFit");

    // Print jobs
    scheduler.printJobs();

    // Save the results to CSV
    scheduler.saveResultsToCSV("jobs.csv");

    return 0;
}
