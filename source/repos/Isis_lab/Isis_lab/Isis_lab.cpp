// Isis_lab.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <clocale>
#include <omp.h>
#include <vector>
#include <ctime>

int Asgl[1000000] = { rand() };

int main()
{
    setlocale(LC_ALL, "rus");
    std::cout << omp_get_num_procs() << "\n";
    omp_set_num_threads(32);
    std::vector<int> Asgl(100000000);
    std::vector<double> Adbl(100000000);
    for (int i = 0; i < Asgl.size(); ++i) {
        Asgl[i] = rand();
        Adbl[i] = rand();
    }
    unsigned int st = clock();
    int Asgl_sum = 0;
    double Adbl_sum = 0;
    for (auto x : Asgl)
        Asgl_sum += x;
    unsigned int et = clock();
    std::cout << "Asgl_sum time = " << et - st << "\n";
    st = clock();
    for (auto x : Adbl)
        Adbl_sum += x;
    et = clock();
    std::cout << "Adbl_sum time = " << et - st << "\n";
    Asgl_sum = 0;
    Adbl_sum = 0;
    st = clock();
#pragma omp parallel for reduction(+: Asgl_sum)
    for (int i = 0; i < Asgl.size(); ++i) {
        Asgl_sum += Asgl[i];
    }
    et = clock();
    std::cout << "Prl asgl time = " << et - st << "\n";
    st = clock();
#pragma omp parallel for reduction(+: Adbl_sum)
    for (int i = 0; i < Adbl.size(); ++i) {
        Adbl_sum += Adbl[i];
    }
    et = clock();
    std::cout << "Prl adbl time = " << et - st << "\n";
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
