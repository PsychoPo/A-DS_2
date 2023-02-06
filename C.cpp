#include <iostream>
#include <string>
#include <math.h>
using namespace std;

void Distribution(ifstream &in1, ofstream &out2, ofstream &out3, string FileName1, string FileName2, string FileName3, int n1, int n2, int s)
{
    int b, c, count = 0;

    in1.open(FileName1);
    out2.open(FileName2, ios::trunc);
    out3.open(FileName3, ios::trunc);

    for (size_t i = 0; i < n1; i++)
    {
        for (size_t j = 0; j < n2; j++)
        {
            if (i % 2 == 0)
            {
                in1 >> b;
                out2 << b << endl;
                count++;
            }
            else
            {
                in1 >> c;
                out3 << c << endl;
                count++;
            }

            if (count == s)
            {
                j = n2;
                i = n1;
            }
        }
    }

    in1.close();
    out2.close();
    out3.close();
}

void Direct_Merge(ifstream &in2, ifstream &in3, ofstream &out1, string FileName1, string FileName2, string FileName3, int n2, int s, int k, int countComparison, int countTransposition, int flag)
{
    int b, c, countB = 0, countC = 0, nb = n2 / 2, nc = n2 / 2, cB = 0, cC = 0, maxcB = 0, maxcC = 0, sz = s, halfn2 = n2 / 2;
    double siz = s;

    in2.open(FileName2);
    in3.open(FileName3);
    out1.open(FileName1, ios::trunc);

    for (size_t i = 0; i < ceil(siz / halfn2); i++)
    {
        if ((sz - halfn2 > 0) && (i % 2 == 0))
            maxcB += halfn2;
        else if ((sz - halfn2 > 0) && (i % 2 == 1))
            maxcC += halfn2;
        else if ((sz - halfn2 <= 0) && (i % 2 == 0))
            maxcB += sz;
        else if ((sz - halfn2 <= 0) && (i % 2 == 1))
            maxcC += sz;
        sz -= halfn2;
    }

    for (size_t i = 0; i < ceil(siz / halfn2); i++)
    {
        if ((cC != maxcC) && (cB != maxcB))
        {
            in2 >> b;
            in3 >> c;
        }
        else if (cB != maxcB)
        {
            in2 >> b;
        }
        else if (cC != maxcC)
        {
            in3 >> c;
        }

        for (size_t j = 0; j < n2; j++)
        {
            if ((countB != nb) && (countC != nc) && (cC != maxcC) && (cB != maxcB))
            {
                countComparison++;

                if (b <= c)
                {
                    out1 << b << endl;
                    countTransposition++;

                    countB++;
                    cB++;

                    if (countB != nb)
                        in2 >> b;
                }
                else
                {
                    out1 << c << endl;
                    countTransposition++;

                    countC++;
                    cC++;

                    if (countC != nc)
                        in3 >> c;
                }
            }
            else if ((countB != nb) && (cB != maxcB))
            {
                out1 << b << endl;
                countTransposition++;

                countB++;
                cB++;

                if (countB != nb)
                    in2 >> b;
            }
            else if ((countC != nc) && (cC != maxcC))
            {
                out1 << c << endl;
                countTransposition++;

                countC++;
                cC++;

                if (countC != nc)
                    in3 >> c;
            }
        }
        countB = 0;
        countC = 0;
    }

    in2.close();
    in3.close();
    out1.close();

    if (flag == 1)
    {
        cout << "Iteration №" << k + 1 << endl;
        cout << "Count comparison: " << countComparison << endl;
        cout << "Count transposition: " << countTransposition << endl;
    }
}

void Arrays(int *Array1, int *Array2, int Fib1, int Fib2)
{
    for (size_t i = 0; i < Fib1; i++)
    {
        if (i < Fib2)
        {
            int j = i + Fib1;
            Array2[i] = Array1[i] + Array1[j];
        }
        else
            Array2[i] = Array1[i];
    }
}

void InitialDistribution(ifstream &in1, ofstream &out2, ofstream &out3, string FileName1, string FileName2, string FileName3, int size, int Fib[], int limit)
{
    int b, c, count = 0;

    in1.open(FileName1);
    out2.open(FileName2, ios::trunc);
    out3.open(FileName3, ios::trunc);

    if (Fib[0] < Fib[1])
    {
        for (size_t i = 0; i < Fib[1]; i++)
        {
            in1 >> b;
            out2 << b << "\n\n";
        }

        for (size_t i = 0; i < Fib[0]; i++)
        {
            if (size - Fib[1] > count)
            {
                in1 >> c;
                out3 << c << "\n\n";
                count++;
            }
            else
                out3 << limit << "\n\n";
        }
    }
    else
    {
        for (size_t i = 0; i < Fib[0]; i++)
        {
            in1 >> b;
            out2 << b << "\n\n";
        }

        for (size_t i = 0; i < Fib[1]; i++)
        {
            if (size - Fib[0] > count)
            {
                in1 >> c;
                out3 << c << "\n\n";
                count++;
            }
            else
                out3 << limit << "\n\n";
        }
    }

    in1.close();
    out2.close();
    out3.close();
}

void Multiphase_Merge(int SeriesB, int SeriesC, ifstream &in2, ifstream &in3, ofstream &out1, ofstream &out3, string FileName2, string FileName3, string FileName1, int s, int k, int *Array, int limit, int countComparison, int countTransposition, int flag)
{
    int b, c, countB = 0, countC = 0, maxcB, maxcC;

    if (k % 2 == 0)
    {
        out1.open(FileName1, ios::trunc);
        in2.open(FileName2);
    }
    else
    {
        out1.open(FileName2, ios::trunc);
        in2.open(FileName1);
    }

    in3.open(FileName3);

    for (size_t i = 0; i < SeriesC; i++)
    {
        maxcB = Array[i];
        maxcC = Array[i + SeriesB];

        in2 >> b;
        in3 >> c;

        for (size_t j = 0; j < (maxcB + maxcC); j++)
        {
            if ((b <= c) && (countB != maxcB))
            {
                countComparison++;

                out1 << b << endl;
                countTransposition++;

                countB++;

                if (countB != maxcB)
                    in2 >> b;
            }
            else if ((c < b) && (c != limit) && (countC != maxcC))
            {
                countComparison++;

                out1 << c << endl;
                countTransposition++;

                countC++;

                if (countC != maxcC)
                    in3 >> c;
            }
            else if (countB != maxcB)
            {
                out1 << b << endl;
                countTransposition++;

                countB++;

                if (countB != maxcB)
                    in2 >> b;
            }
            else if ((c != limit) && (countC != maxcC))
            {
                out1 << c << endl;
                countTransposition++;

                countC++;

                if (countC != maxcC)
                    in3 >> c;
            }

            if (j == (maxcB + maxcC - 1))
            {
                out1 << "\n\n";

                in2.get();
                in2.get();

                in3.get();
                in3.get();
            }
        }
        countB = 0;
        countC = 0;
    }
    in3.close();
    out1.close();

    out3.open(FileName3, ios::trunc);

    for (size_t i = SeriesC; i < SeriesB; i++)
    {
        maxcB = Array[i];

        in2 >> b;

        for (size_t j = 0; j < maxcB; j++)
        {
            out3 << b << endl;
            countTransposition++;

            countB++;

            if (countB != maxcB)
                in2 >> b;

            if (j == (maxcB - 1))
            {
                out3 << "\n\n";

                in2.get();
                in2.get();
            }
        }
        countB = 0;
    }

    out3.close();
    in2.close();

    if (flag == 1)
    {
        cout << "Iteration №" << k + 1 << endl;
        cout << "Count comparisons: " << countComparison << endl;
        cout << "Count transposition: " << countTransposition << endl;
    }
}