import os
for t in [2]:
    # print("NUMT = %d" % t)
    for s in [ 1000, 10000, 100000,  10000000, 32000000, 64000000, 128000000 ]:
    # for s in [ 1000]:
        # print("NUM = %d" % s)
        # icpc -o proj5 proj5.cpp -lm -openmp -align -qopt-report=3 -qopt-report-phase=vec -no-vec
        cmd = "icpc -DNUMS=%d -DNUMT=%d proj5.cpp -o proj5 -lm -openmp -align -qopt-report=3  -qopt-report-phase=vec -no-vec" % ( s, t )
        os.system( cmd )
        cmd = "./proj5"
        os.system( cmd )
        #                                                    