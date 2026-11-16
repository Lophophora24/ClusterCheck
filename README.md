3 библиотеки:                                        <br>
              Eigen, Boost -- header only            <br> 
              FFTW         -- требуется линковка     <br>

Установка: 

- **Eigen** 3.4.0: https://eigen.tuxfamily.org
- **Boost** 1.82 (только заголовки; проект использует `boost::random::normal_distribution`)
- **FFTW** 3.3.10: https://www.fftw.org
              
Сборка:                                              <br>
                                                     
    -g                                              
    -I "C:\...\eigen\eigen-3.4.0"          
    -I "C:\...\boost\boost_1_82_0"         
    -I "C:\...\fftw"                       
    -L "C:\...\fftw"                       
    -lfftw3-3                                        
    check_program.cpp                                 
    main.cpp                                         
    -o C:\Project_dir\main.exe                       
