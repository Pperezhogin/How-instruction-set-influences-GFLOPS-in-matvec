#include <iostream>
#include <random>
#include <chrono>
#include <cmath>
#include <string>

using namespace std;
using namespace std::chrono;

string padTo(int val, const size_t num, const char paddingChar = ' ')
{
    string str = to_string(val);
    if(num > str.size())
        str.insert(0, num - str.size(), paddingChar);
    return str;
}

template < typename T >
class matvec_gflops
{
    public:
    T *A;
    T *x;
    T *b;
    int N;
    int niter;
    float gflops;

    matvec_gflops () {}
    ~matvec_gflops() {}

    // input -- kilobytes
    void allocate(int kib) {
        float N_float = sqrt((float)kib * 1.e+3 / sizeof(T)) - 2.;
        N = max((int)N_float,1);
        b = new T[N];
        x = new T[N];
        A = new T[N*N];

        random_device rd; 
        mt19937 gen(rd());
        uniform_real_distribution<> dis(-0.5, 0.5);
        for (int i = 0; i < N; i++)
        {
            x[i] = dis(gen);
            b[i] = dis(gen);
        }
        for (int i = 0; i < N*N; i++)
        {
            A[i] = dis(gen);
        }
    }
    void deallocate() {
        delete[] b;
        delete[] x;
        delete[] A;
    }
    // Nops = N_columnms * (N_sum + N_prod) = 2N^2
    void matvec() {
        #pragma parallel always
        for (int i = 0; i < N; i++)
        {
            b[i] = (T)0.0;
            for (int j = 0; j < N; j++)
            {
                b[i] += A[i*N+j] * x[j];
            }
        }
    }
    // Nops -- approximate desired FLOAT operations, around 1e+9
    void measure_gflops(float Nops_total) {
        float Nops = 2. * (float)N * (float)N; // FLOAT operations per 1 matvec
        niter = Nops_total / Nops;
        niter = max(niter, 1);

        auto start = high_resolution_clock::now();
        for (int i = 0; i < niter; i++)
            matvec();
        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(stop - start);

        float sec = (float)duration.count() * 1.e-6;
        float flops = Nops * (float)niter / sec;
        gflops = flops * 1.e-9;    
    }

    void print_gflops() {
        int kib = N * (N+2) * sizeof(T) / 1024;

        cout << "Data type: " << typeid(T).name() 
             << ", Memory size, kB: " << padTo(kib,6) 
             << ", Matrix size: " << padTo(N,4)
             << ", iterations number: " << padTo(niter,8)
             << ", gflops: " << gflops << endl;
    }

    void measure_and_print(int kib, float Nops)
    {
        allocate(kib);
        matvec();
        measure_gflops(Nops);
        print_gflops();
        deallocate();
    }

};

int main(int argc, char** argv) {
    float Nops;
    int kib[4] = {32, 1024, 16896, 200000};
    if (argc > 1)
        Nops = 1.e+9 * std::stoi(argv[1]);
    else
        Nops = 1.e+9;

    matvec_gflops<float>  data_float;
    matvec_gflops<double> data_double;

    for (int i = 0; i < 4; i++) {
        data_float.measure_and_print(kib[i], Nops);
        data_double.measure_and_print(kib[i], Nops);
    }

    return 0;
}