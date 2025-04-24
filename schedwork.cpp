#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shifts, 
    size_t day, 
    size_t slot);


bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    size_t numDays = avail.size();
    size_t numWorkers = avail[0].size();

    for(size_t i = 0; i < numDays; i++) {
      sched.push_back(vector<Worker_T>(dailyNeed, INVALID_ID));
    }

    vector<size_t> shifts(numWorkers, 0); 
    return scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, 0, 0);
}

bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& shifts, 
    size_t day, 
    size_t slot)
  {
    size_t numDays = avail.size();
    size_t numWorkers = avail[0].size();
    if(day == numDays) return true;

    if(slot == dailyNeed) return scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, day + 1, 0);

    for(Worker_T w = 0; w < numWorkers; w++) {
      if(avail[day][w] && shifts[w] < maxShifts) {
        bool alreadyScheduled = false;
        for(size_t i = 0; i < slot; i++) {
          if(sched[day][i] == w) {
            alreadyScheduled = true;
            break;
          }
        }

        if(!alreadyScheduled) {
          sched[day][slot] = w;
          shifts[w]++;
          if(scheduleHelper(avail, dailyNeed, maxShifts, sched, shifts, day, slot + 1)) {
            return true;
          }

          sched[day][slot] = INVALID_ID;
          shifts[w]--;
        }
      }
    }
    return false;
  }


