#pragma once
#include <iostream>
#include <Eigen/Dense>
#include <Eigen/SVD>

double condA(const Eigen::MatrixXd& A)
{
  Eigen::JacobiSVD<Eigen::MatrixXd> svd(A);
  Eigen::VectorXd singularValuesA = svd.singularValues();
  return singularValuesA.maxCoeff() / singularValuesA.minCoeff();
};

Eigen::VectorXd gradiente_coniugato(const Eigen::MatrixXd& A, const Eigen::VectorXd& x0, const Eigen::VectorXd& b, Eigen::VectorXd& r, const double r_tol)
{
    /*creo una copia di x0*/
    Eigen::VectorXd x = x0;
    Eigen::VectorXd p = r;



    while (r.norm() >= r_tol)
    {
        const double alpha_k = ((p.transpose() * r) / (p.transpose() * A * p)).value();
        x = x + alpha_k * p;
        r = b - A * x;
        const double beta_k=((p.transpose() * A * r) / (p.transpose() * A * p)).value();
        p = r-beta_k*p;

    }


    return x;
}
