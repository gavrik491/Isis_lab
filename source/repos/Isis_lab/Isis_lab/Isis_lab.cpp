// Isis_lab.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <clocale>
#include <omp.h>
#include <vector>
#include <ctime>

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << omp_get_num_procs() << "\n";
    //omp_set_num_threads(8);
    const int n = 300;
    std::vector<std::vector<int>> Bsgl(n, std::vector<int>(n));
    std::vector<std::vector<double>> Bdbl(n, std::vector<double>(n));
    std::vector<std::vector<int>> Csgl(n, std::vector<int>(n));
    std::vector<std::vector<double>> Cdbl(n, std::vector<double>(n));
    std::vector<std::vector<int>> Dsgl(n, std::vector<int>(n));
    std::vector<std::vector<double>> Ddbl(n, std::vector<double>(n));
    for (int i = 0; i < Bsgl.size(); ++i) {
        for (int j = 0; j < Bsgl.size(); j++) {
            Bsgl[i][j] = rand();
            Bdbl[i][j] = rand() / 10.;
            Csgl[i][j] = rand();
            Cdbl[i][j] = rand() / 10.;
        }
    }
    unsigned int st = clock();
    for (int row = 0; row < Bsgl.size(); ++row) {
        for (int col = 0; col < Bsgl.size(); ++col) {
            for (int i = 0; i < Bsgl.size(); ++i) {
                Dsgl[row][col] += Bsgl[row][i] * Csgl[row][i];
            }
        }
    }
    unsigned int et = clock();
    std::cout << "Bsgl * Csgl posled time = " << et - st << "\n";
    st = clock();
    for (int row = 0; row < Bdbl.size(); ++row) {
        for (int col = 0; col < Bdbl.size(); ++col) {
            for (int i = 0; i < Bdbl.size(); ++i) {
                Ddbl[row][col] += Bdbl[row][i] * Cdbl[i][col];
            }
        }
    }
    et = clock();
    std::cout << "Bdbl * Cdbl posled time = " << et - st << "\n";
    st = clock();
    double el;
#pragma omp parallel for reduction(*: el)
    for (int row = 0; row < Bsgl.size(); ++row) {
        for (int col = 0; col < Bsgl.size(); ++col) {
            el = 0;
            for (int i = 0; i < Bsgl.size(); ++i) {
                el += Bsgl[row][i] * Csgl[i][col];
            }
            Dsgl[row][col] = el;
        }
    }
    et = clock();
    std::cout << "Bsgl * Csgl paral time = " << et - st << "\n";
    st = clock();
#pragma omp parallel for reduction(*: el)
    for (int row = 0; row < Bdbl.size(); ++row) {
        for (int col = 0; col < Bdbl.size(); ++col) {
            el = 0;
            for (int i = 0; i < Bdbl.size(); ++i) {
                el += Bdbl[row][i] * Cdbl[i][col];
            }
            Ddbl[row][col] = el;
        }
    }
    et = clock();
    std::cout << "Bdbl * Cdbl paral time = " << et - st << "\n";
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
