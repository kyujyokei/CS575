import os
for t in [ 1024, 8192, 65536, 524288, 2097152, 4194304, 8388608 ]:
# for t in [ 8388608]:
    # print("NUMT = %d" % t)
    for s in [ 1, 4, 16, 32, 64, 128, 256, 512, 1024 ]:
    # for s in [ 1024 ]:
        # print("NUM = %d" % s)
        # cmd = "g++ -DLOCAL_SIZE=%d -DNMB=%d -o first_1 first_1.cpp /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp -w" % ( s, t )
        # cmd = "g++ -DLOCAL_SIZE=%d -DNMB=%d -o first_2 first_2.cpp /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp -w" % ( s, t )
        cmd = "g++ -DLOCAL_SIZE=%d -DNMB=%d -o first_3 first_3.cpp /scratch/cuda-7.0/lib64/libOpenCL.so -lm -fopenmp -w" % ( s, t )
        os.system( cmd )
        cmd = "./first_3"
        os.system( cmd )
#                                                     