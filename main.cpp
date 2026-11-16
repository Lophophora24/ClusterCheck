#include "main.h"

#include <fftw3.h>

void init()
{
    std::cout << "Starting init()....\n";

    fill();                   // fill x-coordinate and t-time arrays

    //-----------------HIGH TEMPERATURE INITIAL CONDITIONS-------------------------//
    

    //init_();                  // fill the covariance matrices for Wigner functional
    //init_for_generating();    // Generate N=10000 initial conditions with the 
                              // high-temperature Wigner functional

    
    //-----------------------------------------------------------------------------//

    //------------------ARBITRARY GAUSSIAN INITIAL CONDITIONS----------------------//

    init_for_generating_arbitrary_initial_conditions();  
                              // Generate N=10000 initial conditions with the 
                              // general Gaussian Wigner functional

    //-----------------------------------------------------------------------------//

    std::cout << "Exit init()....\n";
}



int main()
{
    clock_t time_start = clock();

    //init();
 
    //average();

    //calculate_phi_exact();

    //calculate_observables();

    sanity_check_all();

    printf("time: %.2fs\n", (double)(clock() - time_start) / CLOCKS_PER_SEC);
    
    return 0;
}

