#ifndef FusionEKF_H_
#define FusionEKF_H_

#include <fstream>
#include <string>
#include <vector>
#include "Eigen/Dense"
#include "kalman_filter.h"
#include "measurement_package.h"
#include "tools.h"

class FusionEKF 
{
public:
  FusionEKF();
  virtual ~FusionEKF();

  void processMeasurement(const MeasurementPackage &measurement_pack);

  void initX(const Eigen::VectorXd raw_measurements,
             const MeasurementPackage::SensorType &sensor_type);
  void initP();

  void updateF(const double &delta_t);
  void updateQ(const double &delta_t);  
  void updateJacobianH();
  void updateH(const Eigen::MatrixXd &H_new);
  void updateR(const Eigen::MatrixXd &R_new);

  void updateTimestamp(const long long &new_timestamp);
  void printOutput();

  KalmanFilter ekf_;


 private:
  bool is_initialized_;
  long long previous_timestamp_;
  Eigen::MatrixXd R_laser_;
  Eigen::MatrixXd R_radar_;
  Eigen::MatrixXd H_laser_;
  double noise_ax_;
  double noise_ay_;
};

#endif // FusionEKF_H_
