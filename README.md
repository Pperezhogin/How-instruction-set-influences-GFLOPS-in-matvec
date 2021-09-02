# How-instruction-set-influences-GFLOPS-in-matvec

Let you have Intel compiler (icpc for c++), and some modern CPU, and you want to check how instruction set on this CPU influences on GFLOPS this CPU produces.\
Here SSE, AVX, AVX2, AVX512 instructions are examined in matrix-vector multiplication problem for float/double data type\
and matrix sizes fitting L1, L2, L3 cache for given 12 core processor.

Usage:
~~~
bash bash.sh > result.txt
~~~

Main loop in this test is "matvec":
~~~
#pragma parallel always
for (int i = 0; i < N; i++)
{
    b[i] = (T)0.0;
    for (int j = 0; j < N; j++)
    {
        b[i] += A[i*N+j] * x[j];
    }
}
~~~

It requires 2*N^2 floating-point operations. Formula for GFLOPS in this case:
~~~
GFLOPS = 2*N^2 / (run-time-in-nanosec)
~~~

GFLOPS for purely scalar operations, without instruction level parallelism and parallelism among cores, should be equal to CPU frequency, like
~~~
GFLOPS = GHz = 3
~~~
Theoretical peak for Fused Multiply Add (FMA) instructions with 512-bit registers and float(4) should be at least:
~~~
GFLOPS = GHz * 2 * (512/4/8) = 100
~~~
Theoretical peak for multicore processor (with 10 cores):
~~~
GFLOPS = 1000
~~~

Nevertheless, some loops can give only
~~~
GFLOPS=0.5
~~~
