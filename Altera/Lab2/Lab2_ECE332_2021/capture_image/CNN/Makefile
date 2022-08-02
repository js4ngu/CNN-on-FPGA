all : a.exe
a.exe : 
    gcc -o a.exe main.o benchmarking.o
main.o : 
    gcc -c main.c parameter.h ifmap_fmap_integer.h cnn_func_integer.h ifmap_fmap_float.h cnn_func_float.h benchmarking.h benchmarking.h
benchmarking.o :
    gcc -c benchmarking.c benchmarking.h

clean:
    rm -f *.o
    rm -f $(TARGET)