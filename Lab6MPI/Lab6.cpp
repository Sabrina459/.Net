#include "Header.h"
#include "mpi.h"
#include <iostream>
#include <chrono>

void Task1(void);
void Task2(void);
void Task3(void);
void Task4(void);

int rank;
int size;
MPI_Status status;
MPI_Request request = MPI_REQUEST_NULL;

size_t N;
size_t H;
size_t H4;

int main(int argc, char* argv[]) {

    MPI_Init(&argc, &argv);

    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (size != 4) {
        MPI_Finalize();
        return 0;
    }
    else if (rank == 0) {
        std::cout << "Size of data N:\n";
        std::cin >> N;
        MPI_Send(&N, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
        MPI_Send(&N, 1, MPI_INT, 2, 0, MPI_COMM_WORLD);
        MPI_Send(&N, 1, MPI_INT, 3, 0, MPI_COMM_WORLD);
    }
    else {
        MPI_Recv(&N, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
    }


    H = N / 4;
    H4 = H + N % 4;

    switch (rank)
    {
    case 0:
        Task3();
        break;
    case 1:
        Task2();
        break;
    case 2:
        Task4();
        break;
    case 3:
        Task1();
        break;
    default:
        break;
    }

    MPI_Finalize();

    return 0;
}
void Task1(void)
{
    data MR = new float[N * N];
    data MOH = new float[N * N];
    data MZH = new float[N * N];
    data CH = new float[N * N];
    data ZH = new float[N * N];
    data BH = new float[N * N];

    float a, d;

    std::cout << "T1 is started!" << std::endl;

    {
        data C2H = new float[H + H4];
        data Z2H = new float[H + H4];
        data MO2H = new float[N * (H + H4)];
        data MZ2H = new float[N * (H + H4)];

        MPI_Recv(C2H, H + H4, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(Z2H, H + H4, MPI_FLOAT, 1, 1, MPI_COMM_WORLD, &status);
        MPI_Recv(MO2H, N * (H + H4), MPI_FLOAT, 1, 2, MPI_COMM_WORLD, &status);
        MPI_Recv(MZ2H, N * (H + H4), MPI_FLOAT, 1, 3, MPI_COMM_WORLD, &status);

        Header::cpy(CH, C2H, H);
        Header::cpy(ZH, Z2H, H);
        Header::cpy(MOH, MO2H, N * H);
        Header::cpy(MZH, MZ2H, N * H);

        MPI_Isend(&C2H[H], H4, MPI_FLOAT, 3, 0, MPI_COMM_WORLD, &request);
        MPI_Isend(&Z2H[H], H4, MPI_FLOAT, 3, 1, MPI_COMM_WORLD, &request);
        MPI_Isend(&MO2H[N * H], N * H4, MPI_FLOAT, 3, 2, MPI_COMM_WORLD, &request);
        MPI_Isend(&MZ2H[N * H], N * H4, MPI_FLOAT, 3, 3, MPI_COMM_WORLD, &request);

        delete[] C2H, Z2H, MO2H, MZ2H;
    }

    {
        data B3H = new float[N - H4];

        MPI_Recv(B3H, N - H4, MPI_FLOAT, 3, 0, MPI_COMM_WORLD, &status);
        MPI_Recv(MR, N * N, MPI_FLOAT, 3, 1, MPI_COMM_WORLD, &status);

        Header::cpy(BH, &B3H[2 * H], H);

        MPI_Isend(B3H, 2 * H, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, &request);
        MPI_Isend(MR, N * N, MPI_FLOAT, 1, 1, MPI_COMM_WORLD, &request);

        delete[] B3H;
    }

    {
        float z3 = Header::minVec(H, ZH);
        float bc3 = Header::vecDotVec(H, BH, CH);
        float z4, bc4;

        MPI_Recv(&z4, 1, MPI_FLOAT, 3, 2, MPI_COMM_WORLD, &status);
        MPI_Recv(&bc4, 1, MPI_FLOAT, 3, 3, MPI_COMM_WORLD, &status);

        float z34 = (z3 > z4) ? z4 : z3;
        float bc34 = bc3 + bc4;

        MPI_Isend(&z34, 1, MPI_FLOAT, 1, 2, MPI_COMM_WORLD, &request);
        MPI_Isend(&bc34, 1, MPI_FLOAT, 1, 3, MPI_COMM_WORLD, &request);

        float z12, bc12;

        MPI_Recv(&z12, 1, MPI_FLOAT, 1, 4, MPI_COMM_WORLD, &status);
        MPI_Recv(&bc12, 1, MPI_FLOAT, 1, 5, MPI_COMM_WORLD, &status);

        a = (z12 > z34) ? z34 : z12;
        d = bc12 + bc34;

        MPI_Isend(&a, 1, MPI_FLOAT, 3, 4, MPI_COMM_WORLD, &request);
        MPI_Isend(&d, 1, MPI_FLOAT, 3, 5, MPI_COMM_WORLD, &request);
    }

    data MTH = Header::partRes(N, H, a, d, MOH, MZH, MR);

    std::cout << "Thread T1 is finished!" << std::endl;

    data MT2H = new float[N * (H + H4)];
    Header::cpy(MT2H, MTH, N * H);

    MPI_Recv(&MT2H[N * H], N * H4, MPI_FLOAT, 3, 4, MPI_COMM_WORLD, &status);
    MPI_Isend(MT2H, N * (H + H4), MPI_FLOAT, 1, 5, MPI_COMM_WORLD, &request);

    delete[] MOH, MZH, MR, CH, ZH, BH, MTH, MT2H;
}

void Task2(void)
{
    data MX = new float[N * N];
    data MS = new float[N * N];

    data CH = new float[H];
    data ZH = new float[H];
    data BH = new float[H];


    float a, d;

    std::cout << "T2 is started!" << std::endl;

    if (N < 5)
    {
        MPI_Recv(MX, N * N, MPI_FLOAT, 0, 2, MPI_COMM_WORLD, &status);
        MPI_Recv(MS, N * N, MPI_FLOAT, 0, 3, MPI_COMM_WORLD, &status);
    }
    else
    {
        float num;
        MPI_Recv(&num, 1, MPI_FLOAT, 0, 1, MPI_COMM_WORLD, &status);

        Header::fillMats(N, num, 2, MX, MS);
    }
    auto start = std::chrono::steady_clock::now();

    MPI_Isend(&MX[N * H * 2], N * (H + H4), MPI_FLOAT, 2, 2, MPI_COMM_WORLD, &request);
    MPI_Isend(&MS[N * H * 2], N * (H + H4), MPI_FLOAT, 2, 3, MPI_COMM_WORLD, &request);

    {
        data C3H = new float[2 * H + H4];
        data Z3H = new float[2 * H + H4];

        MPI_Recv(C3H, 2 * H + H4, MPI_FLOAT, 0, 4, MPI_COMM_WORLD, &status);
        MPI_Recv(Z3H, 2 * H + H4, MPI_FLOAT, 0, 5, MPI_COMM_WORLD, &status);

        Header::cpy(CH, C3H, H);
        Header::cpy(ZH, Z3H, H);

        MPI_Isend(&C3H[H], H + H4, MPI_FLOAT, 2, 0, MPI_COMM_WORLD, &request);
        MPI_Isend(&Z3H[H], H + H4, MPI_FLOAT, 2, 1, MPI_COMM_WORLD, &request);

        delete[] C3H, Z3H;
    }

    MPI_Isend(MX, N * H, MPI_FLOAT, 0, 0, MPI_COMM_WORLD, &request);
    MPI_Isend(MS, N * H, MPI_FLOAT, 0, 1, MPI_COMM_WORLD, &request);

    {
        data B2H = new float[2 * H];

        MPI_Recv(B2H, 2 * H, MPI_FLOAT, 2, 0, MPI_COMM_WORLD, &status);

        Header::cpy(BH, &B2H[H], H);

        MPI_Isend(B2H, H, MPI_FLOAT, 0, 2, MPI_COMM_WORLD, &request);

        delete[] B2H;
    }

    {
        float z2 = Header::minVec(H, ZH);
        float bc2 = Header::vecDotVec(H, BH, CH);
        float z1, bc1;

        MPI_Recv(&z1, 1, MPI_FLOAT, 0, 6, MPI_COMM_WORLD, &status);
        MPI_Recv(&bc1, 1, MPI_FLOAT, 0, 7, MPI_COMM_WORLD, &status);

        float z12 = (z1 > z2) ? z2 : z1;
        float bc12 = bc1 + bc2;

        MPI_Isend(&z12, 1, MPI_FLOAT, 2, 4, MPI_COMM_WORLD, &request);
        MPI_Isend(&bc12, 1, MPI_FLOAT, 2, 5, MPI_COMM_WORLD, &request);

        float z34, bc34;

        MPI_Recv(&z34, 1, MPI_FLOAT, 2, 2, MPI_COMM_WORLD, &status);
        MPI_Recv(&bc34, 1, MPI_FLOAT, 2, 3, MPI_COMM_WORLD, &status);

        a = (z12 > z34) ? z34 : z12;
        d = bc12 + bc34;

        MPI_Isend(&a, 1, MPI_FLOAT, 0, 4, MPI_COMM_WORLD, &request);
        MPI_Isend(&d, 1, MPI_FLOAT, 0, 5, MPI_COMM_WORLD, &request);
    }

    data MTH = Header::partRes(N, H, a, d, &MX[N * H], &MS[N * H], MS);

    std::cout << "Thread T2 is finished!" << std::endl;

    delete[] MTH, MX, MS, CH, ZH, BH;
    std::cout << std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::steady_clock::now() - start).count() << std::endl;
    //Header::printMat(N, N, MT, "MT");
    std::cout << "Calculation completed!" << std::endl;
}
void Task3(void)
{
    data D = new float[N];
    data Z = new float[N];
    data MS = new float[N * N];

    data MXH = new float[N * H];
    data MZH = new float[N * H];
    data BH = new float[H];
    float a, d;

    std::cout << "T3 is started!" << std::endl;

    if (N < 5)
    {
        std::cout << "T3 thread input:" << std::endl;
        std::cout << "D:" << std::endl;
        Header::inputVecs(N, 1, D);

        std::cout << "Z:" << std::endl;
        Header::inputVecs(N, 1, Z);
        {
            data MX = new float[N * N];

            std::cout << "T2 thread input:" << std::endl;

            std::cout << "MO:" << std::endl;
            Header::inputMats(N, 1, MX);

            MPI_Send(MX, N * N, MPI_FLOAT, 1, 2, MPI_COMM_WORLD);

            delete[] MX;
        }

        {
            data C = new float[N];
            data MS = new float[N * N];

            std::cout << "T4 thread input:" << std::endl;
            std::cout << "C:" << std::endl;
            Header::inputVecs(N, 1, C);

            MPI_Send(C, N, MPI_FLOAT, 3, 2, MPI_COMM_WORLD);

            std::cout << "MS:" << std::endl;
            Header::inputMats(N, 1, MS);

            MPI_Send(MS, N * N, MPI_FLOAT, 3, 3, MPI_COMM_WORLD);

            delete[] C, MS;
        }
    }
    else
    {
        float num = 0;
        std::cout << "Number to fill all the data(T1):" << std::endl;
        std::cin >> num;

        Header::fillVecs(N, num, 2, D, Z);

        std::cout << "Number to fill all the data(T2):" << std::endl;
        std::cin >> num;

        MPI_Send(&num, 1, MPI_FLOAT, 1, 1, MPI_COMM_WORLD);

        std::cout << "Number to fill all the data(T4):" << std::endl;
        std::cin >> num;

        MPI_Send(&num, 1, MPI_FLOAT, 3, 1, MPI_COMM_WORLD);
    }

    MPI_Isend(&D[H], N - H, MPI_FLOAT, 1, 4, MPI_COMM_WORLD, &request);
    MPI_Isend(&Z[H], N - H, MPI_FLOAT, 1, 5, MPI_COMM_WORLD, &request);

    MPI_Recv(BH, H, MPI_FLOAT, 1, 2, MPI_COMM_WORLD, &status);
    MPI_Recv(MXH, N * H, MPI_FLOAT, 1, 0, MPI_COMM_WORLD, &status);
    MPI_Recv(MZH, N * H, MPI_FLOAT, 1, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(MS, N * N, MPI_FLOAT, 1, 3, MPI_COMM_WORLD, &status);

    float z1 = Header::minVec(H, Z);
    float bc1 = Header::vecDotVec(H, BH, D);

    MPI_Isend(&z1, 1, MPI_FLOAT, 1, 6, MPI_COMM_WORLD, &request);
    MPI_Isend(&bc1, 1, MPI_FLOAT, 1, 7, MPI_COMM_WORLD, &request);

    MPI_Recv(&a, 1, MPI_FLOAT, 1, 4, MPI_COMM_WORLD, &status);
    MPI_Recv(&d, 1, MPI_FLOAT, 1, 5, MPI_COMM_WORLD, &status);

    data MTH = Header::partRes(N, H, a, d, MXH, MZH, MS);

    std::cout << "Thread T3 is finished!" << std::endl;

    MPI_Isend(MTH, N * H, MPI_FLOAT, 1, 8, MPI_COMM_WORLD, &request);

    delete[] MXH, MZH, MS, D, Z, BH, MTH;
}

void Task4(void)
{
    data B = new float[N];
    data MR = new float[N * N];

    data MOH = new float[N * H4];
    data MZH = new float[N * H4];
    data CH = new float[H4];
    data ZH = new float[H4];

    float a, d;

    std::cout << "T4 is started!" << std::endl;

    if (N < 5)
    {
        MPI_Recv(B, N, MPI_FLOAT, 0, 2, MPI_COMM_WORLD, &status);
        MPI_Recv(MR, N * N, MPI_FLOAT, 0, 3, MPI_COMM_WORLD, &status);
    }
    else
    {
        float num;
        MPI_Recv(&num, 1, MPI_FLOAT, 0, 1, MPI_COMM_WORLD, &status);

        Header::fillVecs(N, num, 1, B);
        Header::fillMats(N, num, 1, MR);
    }

    MPI_Isend(B, 3 * H, MPI_FLOAT, 2, 0, MPI_COMM_WORLD, &request);
    MPI_Isend(MR, N * N, MPI_FLOAT, 2, 1, MPI_COMM_WORLD, &request);

    MPI_Recv(CH, H4, MPI_FLOAT, 2, 0, MPI_COMM_WORLD, &status);
    MPI_Recv(ZH, H4, MPI_FLOAT, 2, 1, MPI_COMM_WORLD, &status);
    MPI_Recv(MOH, N * H4, MPI_FLOAT, 2, 2, MPI_COMM_WORLD, &status);
    MPI_Recv(MZH, N * H4, MPI_FLOAT, 2, 3, MPI_COMM_WORLD, &status);

    float z4 = Header::minVec(H4, ZH);
    float bc4 = Header::vecDotVec(H4, &B[3 * H], CH);

    MPI_Isend(&z4, 1, MPI_FLOAT, 2, 2, MPI_COMM_WORLD, &request);
    MPI_Isend(&bc4, 1, MPI_FLOAT, 2, 3, MPI_COMM_WORLD, &request);

    MPI_Recv(&a, 1, MPI_FLOAT, 2, 4, MPI_COMM_WORLD, &status);
    MPI_Recv(&d, 1, MPI_FLOAT, 2, 5, MPI_COMM_WORLD, &status);

    data MTH = Header::partRes(N, H4, a, d, MOH, MZH, MR);

    std::cout << "Thread T4 is finished!" << std::endl;

    MPI_Isend(MTH, N * H4, MPI_FLOAT, 2, 4, MPI_COMM_WORLD, &request);

    delete[] MOH, MZH, MR, CH, ZH, B, MTH;
}
