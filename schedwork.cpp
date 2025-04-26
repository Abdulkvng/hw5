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

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    size_t dailyNeed,
    size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shiftsCount,
    size_t currentDay
) {// Base case: all days scheduled
    if (currentDay == avail.size()) {
        return true;}

    vector<Worker_T> availableWorkers;
  for (Worker_T worker = 0; worker < avail[currentDay].size(); ++worker) {
if (avail[currentDay][worker] && shiftsCount[worker] < maxShifts) {
      availableWorkers.push_back(worker); }}

    // If not enough available workers. ---  backtrack
    if (availableWorkers.size() < dailyNeed) { return false; }

    vector<bool> mask(availableWorkers.size(), false);
    fill(mask.end() - dailyNeed, mask.end(), true);

    do { // Check if this combination is valid (no duplicates)
        set<Worker_T> uniqueWorkers;
        for (size_t i = 0; i < mask.size(); ++i) {
            if (mask[i]) {uniqueWorkers.insert(availableWorkers[i]);} }
        if (uniqueWorkers.size() != dailyNeed) { continue; }

  sched[currentDay].clear();
  for (size_t i = 0; i < mask.size(); ++i) {
  if (mask[i]) { Worker_T worker = availableWorkers[i];
          sched[currentDay].push_back(worker);
      shiftsCount[worker]++; } }

        // Recurse to next day
        if (scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsCount, currentDay + 1)) {    return true; }
        // Backtrack: undo assignments
      for (size_t i = 0; i < mask.size(); ++i) {
      if (mask[i]) { Worker_T worker = availableWorkers[i];
                shiftsCount[worker]--; } }
    } while (next_permutation(mask.begin(), mask.end()));
    return false;}

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
) {
    if (avail.empty() || dailyNeed == 0 || maxShifts == 0) {
        return false;}

  // Initialize schedule and shift counts
    sched.resize(avail.size());
    for (auto& day : sched) {
        day.resize(dailyNeed, INVALID_ID); }
    vector<size_t> shiftsCount(avail[0].size(), 0);

    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shiftsCount, 0);}