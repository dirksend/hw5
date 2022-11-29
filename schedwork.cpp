

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here


// Add your implementation of schedule() and other helper functions here

// Returns true if tree and subtrees are valid.
// Returns false if current node or subtrees are false.
bool schedule_helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    std::vector<size_t>& shiftsAssigned
) {
    if (dailyNeed == 0) return true;
    if (avail.size() == 0) return false;
    // Number of workers
    const size_t numWorkers = avail[0].size();

    // Begin next day if current day is full
    if (sched.size() == 0U || sched.back().size() == dailyNeed) {
        if (sched.size() == avail.size()) return true;
        sched.push_back({});
    }
    
    const size_t dayNum = sched.size() - 1;
    vector<Worker_T>& day = sched[sched.size() - 1];

    Worker_T startAt = 0;
    if (day.size() != 0) startAt = day.back() + 1;

    // Evaluate potential workers for this slot
    day.push_back(0);
    for (Worker_T i = startAt; i < numWorkers; i ++) {
        if (avail[dayNum][i] && shiftsAssigned[i] < maxShifts) {
            sched.back().back() = i;
            shiftsAssigned[i] ++;
            if (schedule_helper(avail, dailyNeed, maxShifts, sched, shiftsAssigned)) {
                return true;
            }
            shiftsAssigned[i] --;
        }
    }
    sched.back().pop_back();
    if (sched.back().size() == 0) sched.pop_back();
    return false;
}

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U || avail[0].size() == 0U){
        return false;
    }
    sched.clear();
    std::vector<size_t> shiftsAssigned(avail[0].size(), 0);
    return schedule_helper(avail, dailyNeed, maxShifts, sched, shiftsAssigned);
}

