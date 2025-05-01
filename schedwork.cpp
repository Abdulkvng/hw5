#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

#include "schedwork.h"
using namespace std;

static const Worker_T INVALID_ID = (unsigned int)-1;

bool tryWorkerAssignment(
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
 size_t maxShifts,
 DailySchedule& sched,
    vector<size_t>& shiftsCount,
size_t currentDay,
    size_t workerIndex,
size_t assignedCount
);

bool scheduleHelper(
    const AvailabilityMatrix& avail,
  size_t dailyNeed,
  size_t maxShifts,
   DailySchedule& sched,
 vector<size_t>& shiftsCount,
    size_t currentDay
) {
    // Base case would be - all days scheduled
    if (currentDay == avail.size()) {
        return true;}

    // use recursion to get 
    return tryWorkerAssignment(avail, dailyNeed, maxShifts, sched, 
                             shiftsCount, currentDay, 0, 0);}

bool tryWorkerAssignment(
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftsCount,
    size_t currentDay,
    size_t workerIndex,
    size_t assignedCount
) {
    // Base case: enough workers assigned for this day
    if (assignedCount == dailyNeed) {
        return scheduleHelper(avail, dailyNeed, maxShifts, 
          sched, shiftsCount, currentDay + 1); }

    // case of no more workers to try
    if (workerIndex >= avail[currentDay].size()) {
        return false;}
    // 
    if (avail[currentDay][workerIndex] && shiftsCount[workerIndex] < maxShifts) {
        // Assign worker
        sched[currentDay].push_back(workerIndex);
        shiftsCount[workerIndex]++;

        bool success = tryWorkerAssignment(avail, dailyNeed, maxShifts, sched,
        //     shiftsCount, currentDay, workerIndex, 
 shiftsCount, currentDay, workerIndex, 
  assignedCount + 1);
if (success) return true;
        
        // Backtrack
    sched[currentDay].pop_back();
    shiftsCount[workerIndex]--; }

    return tryWorkerAssignment(avail, dailyNeed, maxShifts, sched,
       shiftsCount, currentDay, workerIndex + 1, assignedCount);
}

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
) {
    if (avail.empty() || dailyNeed == 0 || maxShifts == 0) {
        return false; }

    // Initialize schedule and shift counts
    sched.resize(avail.size());
    for (auto& day : sched) {
        day.reserve(dailyNeed);
    }
    vector<size_t> shiftsCount(avail[0].size(), 0);

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsCount, 0);
}