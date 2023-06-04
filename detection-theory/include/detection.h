#ifndef DETECTION_H
#define DETECTION_H

#define MAX_BUFFER_SIZE 256
#define PI 3.141593
typedef struct observation_s {
  int n_obs;
  float obs_value;

} observation_t;

typedef struct mean_n_sigma_s{
  float mean;
  float sigma;
} mean_n_sigma_t;

observation_t* getDataFile(const char *, int*);
float getMean(observation_t*, int*);
void detectMaxVerosimilitude(observation_t* , observation_t*,  int* );
float maxVerosimilitudeEq(float, float, float);
void exportMeans(observation_t* , int*, const char*);
void getFloatData(char*, float*, float*);
#endif
