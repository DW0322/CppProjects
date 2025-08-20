#include <iostream>
#include <cmath>
#include <vector>

struct Joints
{
  double length;
  double angle;
};

std::vector<std::vector<double>> rotationMatrix (double angle)
{
  return {{std::cos(angle), -std::sin(angle)}};
}
int main()
{
  std::vector<std::vector<double>> matrix;
  Joints l1{10, 1};
  std::vector<std::vector<double>> rotation = rotationMatrix(l1.angle);
  for(int i{};i< rotation.size(); ++i)
    for(int j{};j< rotation.size(); ++j)
      std::cout << rotation[i][j] << std::endl;
  return 0;
}
