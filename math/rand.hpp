#include <random>
namespace Rand{
    double fRand(double fMin,double fMax){
        std::uniform_real_distribution<double> unif(fMin,fMax);
        std::default_random_engine re;
        re.seed(rand()%10000);
        double a_random_double = unif(re);
        return a_random_double;
    }
}