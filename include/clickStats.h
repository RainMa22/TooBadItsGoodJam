// CLICKER STYLES
// This file defines the basic tracking and stats operations for the clicker game.

// Guard
#ifndef CLICK_STATS_H
#define CLICK_STATS_H

typedef struct 
{
    int lifetimeClicks; // Clicks accumulated thus far in this instance.
    int currentClicks; // Clicks "currently avaliable" for use.
} ClickStats;

// Create a new click stats object and return it.
ClickStats newClickStats(void) {
    ClickStats stats = {0, 0};
    return stats;
}

// Add a number of clicks.
void addClicks(ClickStats* clickStatsPtr, int amount) {
    (*clickStatsPtr).currentClicks += amount;
    (*clickStatsPtr).lifetimeClicks += amount;
}

// Clamp the number of current clicks at zero.
void clampCurrentClickCount(ClickStats* clickStatsPtr) {
    if ((*clickStatsPtr).currentClicks < 0) {
        (*clickStatsPtr).currentClicks = 0;
    }
}

// Consume a number of clicks, but no negative values allowed in result!
void consumeClicks(ClickStats* clickStatsPtr, int amount) {
    (*clickStatsPtr).currentClicks -= amount;
    clampCurrentClickCount(clickStatsPtr);
}



// Reset click counters to zero.
void resetClicks(ClickStats* clickStatsPtr) {
    (*clickStatsPtr).currentClicks = 0;
    (*clickStatsPtr).lifetimeClicks = 0;
}

#endif //CLICK_STATS_H