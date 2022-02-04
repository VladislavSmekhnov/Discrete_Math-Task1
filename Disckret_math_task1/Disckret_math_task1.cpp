// Смехнов Владислав, 09-011.
#include <iostream>

using namespace std;

const unsigned int SIZE = 10;

int graph[SIZE][SIZE] // Граф в матричном виде
{
    {0, 1, 1, 1, 0, 0, 0, 0, 1, 1},
    {1, 0, 1, 0, 0, 1, 0, 1, 0, 1},         // Здесь можно заполнить значения                                        
    {1, 1, 0, 1, 1, 0, 0, 1, 0, 0},         // графа в матрице смежности
    {1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
    {0, 0, 1, 1, 0, 0, 1, 1, 0, 0},
    {0, 1, 0, 0, 0, 0, 1, 1, 0, 0},
    {0, 0, 0, 0, 1, 1, 0, 1, 0, 0},
    {0, 1, 1, 0, 1, 1, 1, 0, 0, 0},
    {1, 0, 0, 1, 0, 0, 0, 0, 0, 1},
    {1, 1, 0, 0, 0, 0, 0, 0, 1, 0}
};

int Chrom(int *C);

int main()
{
    int *C = new int[SIZE]; // Вектор, где C[i] - номер цвета, который получает i-ая вершина
    
    cout << "Matrix graph:" << endl;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
            cout << graph[i][j] << " ";
        
        cout << endl;
    }
    cout << endl;

    cout << "Chromatic number: " << Chrom(C) << endl;
    cout << endl;
    cout << "Number of color for each graph vertex:" << endl; // Номер цвета для каждой вершины графа
    for (int i = 0; i < SIZE; i++)
        cout << C[i] << " ";

    cout << endl;
    
    return 0;
}

int max(int *C)
{ // Ищем максимум в векторе 'C'
    int maximum = 0;

    for (int i = 0; i < SIZE; i++)
    {
        if (C[i] > maximum)
            maximum = C[i];
    }

    return maximum;
}

bool Color(int h, int &hnew, int *C)
{
    C[0] = 1;
    for (int i = 1; i < SIZE; i++)
        C[i] = 0;

    int i = 1;
    while (i >= 1 && i <= SIZE)
    {
        C[i]++;
        bool f = true;
        if (C[i] > h - 1)
        {
            C[i] = 0;
            i--;
        }
        else
        {
            int j = 0;
            while (f && j < SIZE)
            {
                if (graph[i][j] == 1)
                    f &= (C[i] != C[j]);
                if (f)
                    j++;
            }
            if (f)
                i++;
        }
    }
    if (i == 0)
        return false;
    else
    {
        hnew = max(C);
        return true;
    }
        
}

int Chrom(int *C)
{
    int hnew; // Число использованных красок
    int h = SIZE; // Хроматическое число
    
    int *buf = new int[SIZE];

    for (int i = 0; i < SIZE; i++)
        C[i] = i;

    while (Color((h - 1), hnew, buf))
    {
        h = hnew;
        for (int i = 0; i < SIZE; i++)
            C[i] = buf[i];
    }

    return h;
}
