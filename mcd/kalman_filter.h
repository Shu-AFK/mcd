#ifndef MCD_KALMAN_FILTER_H
#define MCD_KALMAN_FILTER_H

extern float Q_angle;
extern float Q_bias;
extern float R_measure;
extern float angle;
extern float bias;
extern float P[2][2];
extern float rate;

float kalmanFilter(float newAngle, float newRate, float dt);

#endif //MCD_KALMAN_FILTER_H
