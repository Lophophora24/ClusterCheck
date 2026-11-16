3 библиотеки: Eigen, Boost -- header only 
              FFTW         -- требуется линковка
Сборка:

cmd /c chcp 65001>nul && C:\msys64\ucrt64\bin\g++.exe 
    -fdiagnostics-color=always 
    -g 
    -I "C:\Program Files\eigen\eigen-3.4.0" 
    -I "C:\Program Files\boost\boost_1_82_0" 
    -I "C:\Program Files\fftw" 
    -L "C:\Program Files\fftw" 
    -lfftw3-3 
    check_program.cpp 
    main.cpp 
    -o C:\Project_dir\main.exe
