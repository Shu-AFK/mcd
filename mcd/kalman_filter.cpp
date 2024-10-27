#include "kalman_filter.h"

float Q_angle = 0.001f;             // Process noise variance for the accelerometer
float Q_bias = 0.003f;              // Process noise variance for the gyro bias
float R_measure = 0.03f;            // Measurement noise variance
float angle = 0.0f;                 // The angle calculated by the Kalman filter
float bias = 0.0f;                  // The gyro bias calculated by the Kalman filter
float P[2][2] = {{0, 0}, {0, 0}};   // Error covariance matrix
float rate;

float kalmanFilter(float newAngle, float newRate, float dt) {
    rate = newRate - bias;
    angle += dt * rate;

    // Updating the estimated error covariance ahead of time
    P[0][0] += dt * (dt * P[1][1] - P[0][1] - P[1][0] + Q_angle);
    P[0][1] -= dt * P[1][1];
    P[1][0] -= dt * P[1][1];
    P[1][1] += Q_bias * dt;

    // Measurement update
    float S = P[0][0] + R_measure; // Estimate error
    float K[2];                    // Kalman gain - This is a 2x1 vector
    K[0] = P[0][0] / S;
    K[1] = P[1][0] / S;

    float y = newAngle - angle;
    angle += K[0] * y;
    bias += K[1] * y;

    // Updating the error covariance
    float P00_temp = P[0][0];
    float P01_temp = P[0][1];

    P[0][0] -= K[0] * P00_temp;
    P[0][1] -= K[0] * P01_temp;
    P[1][0] -= K[1] * P00_temp;
    P[1][1] -= K[1] * P01_temp;

    return angle;
}