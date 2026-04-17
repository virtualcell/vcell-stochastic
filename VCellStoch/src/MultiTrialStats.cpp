//
// Created by Jim Schaff on 8/11/23.
//

#include "MultiTrialStats.h"
#include <vector>
#include <iostream>
#include <limits>
#include <math.h>

using std::vector;
using std::string;

MultiTrialStats::MultiTrialStats(int numVars, int numTimePoints) {
    this->numVars = numVars;
    this->numTimePoints = numTimePoints;
    currentTrial = 0;
    init();
}

void MultiTrialStats::init() {
    mean.resize(numTimePoints);
    M2.resize(numTimePoints);
    variance.resize(numTimePoints);
    statMin.resize(numTimePoints);
    statMax.resize(numTimePoints);
    for (int i = 0; i < numTimePoints; ++i) {
        mean[i].resize(numVars,0);
        M2[i].resize(numVars,0);
        variance[i].resize(numVars,0);
        statMin[i].resize(numVars,std::numeric_limits<double>::max());
        statMax[i].resize(numVars,std::numeric_limits<double>::min());
    }
}

void MultiTrialStats::addSample(int timeIndex, double timeValue, double *varVals) {
    if (timeValues.size() <= timeIndex){
        timeValues.push_back(timeValue);
    }
    for (int i = 0; i < numVars; ++i) {
        double currValue = varVals[i];
        double delta = currValue - mean[timeIndex][i];
        mean[timeIndex][i] += delta / (currentTrial);
        M2[timeIndex][i] += delta * (currValue - mean[timeIndex][i]);
        variance[timeIndex][i] = M2[timeIndex][i] / (currentTrial-1);
        statMin[timeIndex][i] = std::min(currValue, statMin[timeIndex][i]) ;
        statMax[timeIndex][i] = std::max(currValue, statMax[timeIndex][i]) ;
    }
}

double MultiTrialStats::getMean(int varIndex, int timeIndex) {
    return mean[timeIndex][varIndex];
}

double MultiTrialStats::getVariance(int varIndex, int timeIndex) {
    return variance[timeIndex][varIndex];
}

double MultiTrialStats::getMin(int varIndex, int timeIndex) {
    return statMin[timeIndex][varIndex];
}

double MultiTrialStats::getMax(int varIndex, int timeIndex) {
    return statMax[timeIndex][varIndex];
}

void MultiTrialStats::startNewTrial() {
    currentTrial += 1;
}

void MultiTrialStats::writeOutput(std::string outfilename, vector<string> listOfVarNames) {
    writeHDF5(outfilename, listOfVarNames);
}

#ifdef USE_HDF5
#include <hdf5.h>

void MultiTrialStats::writeHDF5(string outfilename, vector<string> listOfVarNames){
    // ... existing HDF5 implementation ...
}
#endif

#ifdef USE_PARQUET
#include <arrow/api.h>
#include <parquet/arrow/writer.h>

void MultiTrialStats::writeParquet(std::string outfilename, vector<string> listOfVarNames) {
    // Placeholder for Parquet implementation
    // To be implemented in next phase
    std::cout << "Parquet output not yet implemented" << std::endl;
}
#endif
