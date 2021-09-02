# How-instruction-set-influences-GFLOPS-in-matvec

Let you have Intel compiler (icpc for c++), and some modern CPU, and you want to check how instruction set on this CPU influences on GFLOPS this CPU produces.
Here SSE, AVX, AVX2, AVX512 instructions are examined.

Using:
bash bash.sh > result.txt

Main loop of the test ("matvec"):
#pragma parallel always
for (int i = 0; i < N; i++)
{
    b[i] = (T)0.0;
    for (int j = 0; j < N; j++)
    {
        b[i] += A[i*N+j] * x[j];
    }
}

It requires 2*N*N floating-point operations. Formula for GFLOPS:
GFLOPS = 2*N*N^2 / (run-time-in-nanosec)

GFLOPS for purely scalar operations, without instruction level parallelism and cores-parallelism should be equal to CPU frequency, like
GFLOPS = GHz

