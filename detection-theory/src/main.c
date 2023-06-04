

#include <stdio.h>
#include <stdlib.h>

#include "detection.c"


typedef struct p_observation_s{
    observation_t* getDataMessage;

}p_observation_t;


int main(int argc, char** argv){
    int a, b = 0; 
    int* obs = &a;
    int* obsMessage2 = &b;
    observation_t* getDataObs;
    observation_t* getDataObs2;

    const char* mean_message_1 = "mean1_var.txt";
    const char* mean_message_2 = "mean2_var.txt";

    getDataObs = getDataFile("z1.txt", obs);
    printf("Cant obs in mean1: %d\n", *obs);
    exportMeans(getDataObs, obs, mean_message_1);


    getDataObs2 = getDataFile("z2.txt", obsMessage2);
    exportMeans(getDataObs2, obsMessage2, mean_message_2);
    printf("Cant obs in mean2: %d\n", *obsMessage2);

    detectMaxVerosimilitude(getDataObs, getDataObs2, obs);
    free(getDataObs);
    free(getDataObs2);


    return 0;
}
