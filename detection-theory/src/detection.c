#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "../include/detection.h"


observation_t* getDataFile(const char* filename, int* observations){
    FILE* fp;

    fp = fopen(filename, "r");
    char buff[256];
    int cnt = 0;
    int i;
    while(fgets(buff, MAX_BUFFER_SIZE, fp) != NULL){
        cnt++;
    }
    
    *observations = cnt;
    observation_t* newObservation = malloc(sizeof(observation_t)*cnt);
    newObservation->n_obs = 0;
    newObservation->obs_value = 0.0;
    if (!newObservation){
        perror("Malloc failure");
    }
    rewind(fp);
    int nObs = 0;
    float vObs = 0.0;
    for(i = 0; i < cnt; ++i){
        if(fgets(buff, MAX_BUFFER_SIZE, fp) != NULL){
            fscanf(fp, "%d: %f", &nObs, &vObs);
            newObservation[i].n_obs = nObs;
            newObservation[i].obs_value = vObs;
        }
    }
    cnt = 0;
    fclose(fp);
    return newObservation;

    // free(newObservation);


}

void getFloatData(char* filename, float* m, float* s){
    FILE* newFile;
    char buffer[MAX_BUFFER_SIZE];
    int counter = 0;
    
    newFile = fopen(filename, "r");
    if(newFile == NULL){
        printf("No file detected");
    }
    while(fgets(buffer, MAX_BUFFER_SIZE, newFile) != NULL){
        counter++;
    }
    float a = 0.0;
    float b = 0.0;
    rewind(newFile);
    for(int j = 0; j < counter; j++){
        if(fgets(buffer, MAX_BUFFER_SIZE, newFile) != NULL){
            printf("Corro bien");
            fscanf(newFile, "u: %.5f sigma: %.5f", &a, &b);
        }
    }
    printf("DEsde dentro: %.5f, %.5f\n", a, b);
    m = &a;
    s = &b;
}

float getMean(observation_t* spec_obs, int* totalObs){
    float resMean, sumObs = 0.0;
    int i;

    for(i=0;i < *totalObs; i++){
        sumObs += spec_obs[i].obs_value;
    }
    resMean = 1.0 / (*totalObs);
    printf("Res Mean function: %.3f\n", sumObs);
    return resMean*sumObs;
}

float getVariance(observation_t* var_obs, int *totalObs){
    int i;
    float var;
    float varMean = getMean(var_obs, totalObs);
    for(i = 0; i < *totalObs; i++){
        var += ((pow(var_obs[i].obs_value, 2)) - (pow(varMean, 2)));
    }
    float inv_total_obs = (1.0/(*totalObs));
    return inv_total_obs*var;

}


void exportMeans(observation_t* obsToExport, int* obs_quantity, const char* filename){
    FILE* ep;
    ep = fopen(filename, "w");
    // float sigma =
    fprintf(ep, "u: %.5f sigma: %.5f\n",getMean(obsToExport, obs_quantity), getVariance(obsToExport, obs_quantity));
    
    fclose(ep);
    
}

float maxVerosimilitudeEq(float obs, float mean, float variance){

    return (1.0/(2*PI*variance))*(exp(-(pow((obs - mean), 2))/(2*variance)));
}

void detectMaxVerosimilitude(observation_t* observations, observation_t* observ2, int* obsCant){
    float res_m1, res_m2;
    const char* filename = "res.txt";
    float mean1 , mean2, sigma1, sigma2 = 0.0;
    int* cant;
    observation_t* getResData = getDataFile("z.txt", cant);
    FILE* resFile;
    resFile = fopen(filename, "w");
    mean1 = getMean(observations, obsCant);
    sigma1 = getVariance(observations, obsCant);

    mean2 = getMean(observ2, obsCant);
    sigma2 = getVariance(observ2, obsCant);
    printf("MEAN1 : %.5f, SIGMA1 : %.5f\n", mean1,sigma1);
    printf("MEAN2 : %.5f, SIGMA2 : %.5f\n", mean2,sigma2);

    for(int i = 0; i < *obsCant; i++){
        res_m1 = maxVerosimilitudeEq(getResData[i].obs_value, mean1, sigma1);
        res_m2 = maxVerosimilitudeEq(getResData[i].obs_value, mean2, sigma2);

        if (res_m1 > res_m2){
            fprintf(resFile, "Index: %d, Obs: %.5f, Tipo de mensaje: m1\n", i, getResData[i].obs_value);
        } else {
            fprintf(resFile, "Index: %d, Obs: %.5f, Tipo de mensaje: m2\n", i, getResData[i].obs_value);
        }
    }

}