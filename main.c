#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

clockid_t clockRes = CLOCK_PROCESS_CPUTIME_ID;

typedef struct {
  timespec *start;
  timespec *finish;
} Journey;

Journey *makeJourney() {
  Journey *journey = (Journey*) malloc(sizeof(Journey));
  journey->start = (timespec*) malloc(sizeof(timespec));
  journey->finish = (timespec*) malloc(sizeof(timespec));
  // journey->start->timeInterval = (timeval*) malloc(sizeof(timeval));
  // journey->start->timeZone = (timezone*) malloc(sizeof(timezone));
  // journey->finish->timeInterval = (timeval*) malloc(sizeof(timeval));
  // journey->finish->timeZone = (timezone*) malloc(sizeof(timezone));
  return journey;
}

void deleteJourney(Journey *journey) {
  // free(journey->start->timeInterval);
  // free(journey->start->timeZone);
  // free(journey->finish->timeInterval);
  // free(journey->finish->timeZone);
  free(journey->start);
  free(journey->finish);
  free(journey);
}

Journey *measureCall(Journey *journey) {
  clock_gettime(clockRes, journey->start);
  read(0, NULL, 0);
  clock_gettime(clockRes, journey->finish);
  return journey;
}

long secToNanoSec(time_t secs) {
  return (long)secs * (long)1000000000;
}

long getLengthJouneyInNanoSeconds(Journey *journey) {
  long timeAtStart = secToNanoSec(journey->start->tv_sec) + journey->start->tv_nsec;
  long timeAtFinish = secToNanoSec(journey->finish->tv_sec) + journey->finish->tv_nsec;
  return timeAtFinish - timeAtStart; 
}

long getAverageFromNumTests(int iterations) {
  long total = 0;
  
  for (int i = 0; i < iterations; ++i) {
    Journey *journey = measureCall(makeJourney());
    total += getLengthJouneyInNanoSeconds(journey);
    deleteJourney(journey);
  }
  
  return total / (long)iterations;
}

int main(int argc, char*argv[]) {
  printf("%ld nanoseconds\n", getAverageFromNumTests(1000));
}

// https://man7.org/linux/man-pages/man3/clock_gettime.3.html