3 библиотеки: Eigen, Boost -- header only            <br> 
              FFTW         -- требуется линковка     <br>
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
