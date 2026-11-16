// check_programm.cpp
#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <algorithm> 
#include <vector>

#include <Eigen/Dense>
#include <boost/version.hpp>
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/normal_distribution.hpp>
#include <fftw3.h>

namespace { constexpr double kPi = 3.14159265358979323846; }

// ---------------------------------------------------------------- Eigen
static int test_eigen()
{
    Eigen::Matrix3d A;
    A << 1, 2,  3,
         4, 5,  6,
         7, 8, 10;

    Eigen::Matrix3d B = A.inverse() * A;
    if (!B.isApprox(Eigen::Matrix3d::Identity(), 1e-12)) {
        std::fprintf(stderr, "Eigen: A^-1 * A != I\n");
        return 1;
    }
    if (std::abs(A.sum() - 46.0) > 1e-12) {
        std::fprintf(stderr, "Eigen: sum mismatch (%.6f)\n", A.sum());
        return 1;
    }

    std::printf("Eigen OK (version %d.%d.%d)\n",
                EIGEN_WORLD_VERSION, EIGEN_MAJOR_VERSION, EIGEN_MINOR_VERSION);
    return 0;
}

// ---------------------------------------------------------------- Boost
static int test_boost()
{
    boost::mt19937 rng(20241116u);
    boost::random::normal_distribution<double> dist(0.0, 1.0);

    const int N = 200000;
    double sum  = 0.0;
    double sum2 = 0.0;
    for (int i = 0; i < N; ++i) {
        double x = dist(rng);
        sum  += x;
        sum2 += x * x;
    }
    double mean = sum  / N;
    double var  = sum2 / N - mean * mean;


    if (std::abs(dist.mean() - 0.0) > 1e-12 ||
        std::abs(dist.sigma() - 1.0) > 1e-12) {
        std::fprintf(stderr, "Boost.Random: mean()/sigma() mismatch\n");
        return 1;
    }

    std::printf("Boost OK (version %d.%d.%d, normal mean=%.4f, var=%.4f)\n",
                BOOST_VERSION / 100000,
                BOOST_VERSION / 100 % 1000,
                BOOST_VERSION % 100,
                mean, var);
    return 0;
}

// ---------------------------------------------------------------- FFTW

static int test_fftw()
{
    const int    N     = 256;
    const double L     = 32.0;
    const double dx    = L / N;
    const double sigma = 2.0;

    fftw_complex* in   = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    fftw_complex* out  = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);
    fftw_complex* back = (fftw_complex*) fftw_malloc(sizeof(fftw_complex) * N);

    for (int n = 0; n < N; ++n) {
        double x = (n - N / 2) * dx;
        in[n][0] = std::exp(-x * x / (2.0 * sigma * sigma)) / (sigma * std::sqrt(2.0 * kPi));
        in[n][1] = 0.0;
    }

    fftw_plan pf = fftw_plan_dft_1d(N, in,  out,  FFTW_FORWARD,  FFTW_ESTIMATE);
    fftw_plan pb = fftw_plan_dft_1d(N, out, back, FFTW_BACKWARD, FFTW_ESTIMATE);

    fftw_execute(pf);
    fftw_execute(pb);

    double rt_err = 0.0;
    for (int n = 0; n < N; ++n) {
        double e = std::max(std::abs(back[n][0] / N - in[n][0]),
                            std::abs(back[n][1] / N - in[n][1]));
        if (e > rt_err) rt_err = e;
    }

    fftw_destroy_plan(pf);
    fftw_destroy_plan(pb);
    fftw_free(in);
    fftw_free(out);
    fftw_free(back);

    int rc = 0;
    if (rt_err > 1e-10) { std::fprintf(stderr, "FFTW: rt_err=%.2e\n", rt_err); rc = 1; }

    if (rc == 0) {
        std::printf("FFTW OK (c2c, version %s, rt=%.2e)\n",
                    fftw_version, rt_err);
    }
    return rc;
}

// ---------------------------------------------------------------- driver
int sanity_check_all()
{
    std::printf("=== Sanity check: Boost / Eigen / FFTW ===\n");
    int rc = 0;
    rc |= test_eigen();
    rc |= test_boost();
    rc |= test_fftw();
    if (rc == 0) std::printf("All OK\n");
    else         std::fprintf(stderr, "FAILED\n");
    return rc;
}