3 библиотеки:                                        <br>
              Eigen, Boost -- header only            <br> 
              FFTW         -- требуется линковка     <br>

Установка: 

- **Eigen** 3.4.0: https://eigen.tuxfamily.org
- **Boost** 1.82 (только заголовки; проект использует `boost::random::normal_distribution`)
- **FFTW** 3.3.10: https://www.fftw.org
              
Сборка:                                              <br>

cmd /c chcp 65001>nul && C:\msys64\ucrt64\bin\g++.exe<br> 
    -fdiagnostics-color=always                       <br> 
    -g                                               <br>
    -I "C:\Program Files\eigen\eigen-3.4.0"          <br> 
    -I "C:\Program Files\boost\boost_1_82_0"         <br>
    -I "C:\Program Files\fftw"                       <br>
    -L "C:\Program Files\fftw"                       <br>
    -lfftw3-3                                        <br>
    check_program.cpp                                <br> 
    main.cpp                                         <br>
    -o C:\Project_dir\main.exe                       <br>
