//
// Created by legokol on 11.03.2022.
//

#include <Eigen/Dense>

#include <gtest/gtest.h>
TEST(TEST, EIGEN){
    Eigen::Vector3d vector{1, 2, 3};
    std::cout << vector << std::endl;
}