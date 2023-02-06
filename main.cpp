#include <fstream>
#include <iostream>
using namespace std;
#include "C.cpp"
#include <ctime>

// Вариант №20.

int main()
{
  int answer = 0;
  while (answer != 10)
  {
    cout << "\n1 - Sorting one random array.\n2 - Accumulation of statistical data.\n";
    cout << "10 - EXIT.\nEnter: ";
    cin >> answer;
    cout << endl;
    switch (answer)
    {
    case 1:
    {
      long size = 0, dBorder = 0, hBorder = 0;
      string FileName1 = "A.txt", FileName2 = "B.txt", FileName3 = "C.txt";
      ifstream in1, in2, in3;
      ofstream out1, out2, out3;

      out1.open(FileName1, ios::trunc);
      if (!out1)
      {
        cout << "\n No file";
        return 1;
      }

      cout << "Enter number of the Array: ";
      cin >> size;
      cout << "Specify the range of values of the array elements.\nEnter the smallest number: ";
      cin >> dBorder;
      cout << "Enter the biggest number: ";
      cin >> hBorder;
      cout << endl;

      for (long i = 0; i < size; i++)
      {
        long o;
        o = rand() % (hBorder - dBorder + 1) + dBorder;
        out1 << o << endl;
      }
      cout << "\nDone.\n"
           << endl;

      out1.close();

      int answer2 = 0;
      while (answer2 != 10)
      {
        cout << "\n1 - Sorting an array by DirectMerge.\n2 - Sorting an array by POLYPHASE.\n";
        cout << "10 - BACK.\nEnter: ";
        cin >> answer2;
        cout << endl;
        switch (answer2)
        {
        case 1:
        {
          int n1, n2 = 2, degreeoftwo = 1, size_two, k = 0, countComparison = 0, countTransposition = 0;

          while (pow(2, degreeoftwo) < size)
            degreeoftwo++;

          size_two = pow(2, degreeoftwo);
          n1 = size_two;

          for (n2 = 2; n2 <= size_two; n2 *= 2)
          {
            Distribution(in1, out2, out3, FileName1, FileName2, FileName3, n1, n2 / 2, size);
            Direct_Merge(in2, in3, out1, FileName1, FileName2, FileName3, n2, size, k, countComparison, countTransposition, 1);

            n1 /= 2;

            k++;
          }
        }
        break;

        case 2:
        {
          int k = 0, countComparison = 0, countTransposition = 0;

          int *Fib = new int[2];
          Fib[0] = 0;
          Fib[1] = 1;

          while (Fib[0] + Fib[1] < size)
            if (Fib[0] < Fib[1])
              Fib[0] += Fib[1];
            else
              Fib[1] += Fib[0];

          int *Array1 = new int[(Fib[0] + Fib[1])];
          int *Array2 = new int[Fib[1]];

          for (size_t i = 0; i < (Fib[0] + Fib[1]); i++)
          {
            Array1[i] = 1;

            if (i >= size)
              Array1[i] = 0;
          }

          InitialDistribution(in1, out2, out3, FileName1, FileName2, FileName3, size, Fib, -1);

          while (Fib[0] + Fib[1] != 1)
          {
            if (k % 2 == 0)
            {
              delete[] Array2;

              if (Fib[0] < Fib[1])
              {
                Multiphase_Merge(Fib[1], Fib[0], in2, in3, out1, out3, FileName2, FileName3, FileName1, size, k, Array1, -1, countComparison, countTransposition, 1);

                Array2 = new int[Fib[1]];
                Arrays(Array1, Array2, Fib[1], Fib[0]);

                Fib[1] -= Fib[0];
              }
              else
              {
                Multiphase_Merge(Fib[0], Fib[1], in2, in3, out1, out3, FileName2, FileName3, FileName1, size, k, Array1, -1, countComparison, countTransposition, 1);

                Array2 = new int[Fib[0]];
                Arrays(Array1, Array2, Fib[0], Fib[1]);

                Fib[0] -= Fib[1];
              }
            }
            else
            {
              delete[] Array1;

              if (Fib[0] < Fib[1])
              {
                Multiphase_Merge(Fib[1], Fib[0], in2, in3, out1, out3, FileName2, FileName3, FileName1, size, k, Array1, -1, countComparison, countTransposition, 1);

                Array1 = new int[Fib[1]];
                Arrays(Array2, Array1, Fib[1], Fib[0]);

                Fib[1] -= Fib[0];
              }
              else
              {
                Multiphase_Merge(Fib[0], Fib[1], in2, in3, out1, out3, FileName2, FileName3, FileName1, size, k, Array1, -1, countComparison, countTransposition, 1);

                Array1 = new int[Fib[0]];
                Arrays(Array2, Array1, Fib[0], Fib[1]);

                Fib[0] -= Fib[1];
              }
            }
            k++;
          }
          delete[] Array1;
          delete[] Array2;
        }
        break;
        }
      }
      size = 0;
      out1.close();
    }
    break;

    case 2:
    {
      long size = 0, dBorder = 0, hBorder = 0, s = 0;
      string FileName1 = "A.txt", FileName2 = "B.txt", FileName3 = "C.txt", FileNameTime = "Time.txt";
      ifstream in1, in2, in3;
      ofstream out, out1, out2, out3;
      int lim;

      cout << "Enter number of the Array: ";
      cin >> size;
      cout << "Specify the range of values of the array elements.\nEnter the smallest number: ";
      cin >> dBorder;
      cout << "Enter the biggest number: ";
      cin >> hBorder;
      cout << "Enter the step of the creation an array: ";
      cin >> s;
      cout << endl;

      int answer2 = 0;
      while (answer2 != 10)
      {
        cout << "\n1 - Create a random array.";
        cout << "\n2 - Create a straight order array.";
        cout << "\n3 - Create a reversed order array.";
        cout << "\n10 - BACK.\nEnter: ";
        cin >> answer2;
        cout << endl;
        switch (answer2)
        {
        case 1:
        {
          out1.open(FileName1, ios::trunc);

          for (long i = 0; i < size; i++)
          {
            long o;
            o = rand() % (hBorder - dBorder + 1) + dBorder;
            out1 << o << endl;
          }
          cout << "\nDone.\n"
               << endl;

          out1.close();

          int answer3 = 0;
          cout << "\n1 - DirectMerge.\n2 - MultiPhaseMerge.\nEnter: ";
          cin >> answer3;
          cout << endl;
          switch (answer3)
          {
          case 1:
          {
            out.open(FileNameTime, ios::trunc);

            for (long c = s; c <= size; c += s)
            {
              int n1, n2 = 2, degreeoftwo = 1, size_two, k = 0, countComparison = 0, countTransposition = 0;

              while (pow(2, degreeoftwo) < c)
                degreeoftwo++;

              size_two = pow(2, degreeoftwo);
              n1 = size_two;

              clock_t t0 = clock();
              for (n2 = 2; n2 <= size_two; n2 *= 2)
              {
                Distribution(in1, out2, out3, FileName1, FileName2, FileName3, n1, n2 / 2, c);
                Direct_Merge(in2, in3, out1, FileName1, FileName2, FileName3, n2, c, k, countComparison, countTransposition, 2);

                n1 /= 2;

                k++;
              }
              clock_t t1 = clock();

              out << "Sorting by DirectMerge" << endl
                  << "Elements in array: " << c << endl
                  << "Time: " << (long double)(t1 - t0) / CLOCKS_PER_SEC << endl
                  << endl;
            }
          }
          break;

          case 2:
          {
            out.open(FileNameTime, ios::trunc);

            int k = 0, countComparison = 0, countTransposition = 0;

            int *Fib = new int[2];
            Fib[0] = 0;
            Fib[1] = 1;

            for (long c = s; c <= size; c += s)
            {
              while (Fib[0] + Fib[1] < c)
                if (Fib[0] < Fib[1])
                  Fib[0] += Fib[1];
                else
                  Fib[1] += Fib[0];

              int *Array1 = new int[(Fib[0] + Fib[1])];
              int *Array2 = new int[Fib[1]];

              for (size_t i = 0; i < (Fib[0] + Fib[1]); i++)
              {
                Array1[i] = 1;

                if (i >= c)
                  Array1[i] = 0;
              }

              InitialDistribution(in1, out2, out3, FileName1, FileName2, FileName3, c, Fib, -1);

              clock_t t0 = clock();
              while (Fib[0] + Fib[1] != 1)
              {
                if (k % 2 == 0)
                {
                  delete[] Array2;

                  if (Fib[0] < Fib[1])
                  {
                    Multiphase_Merge(Fib[1], Fib[0], in2, in3, out1, out3, FileName2, FileName3, FileName1, c, k, Array1, -1, countComparison, countTransposition, 1);

                    Array2 = new int[Fib[1]];
                    Arrays(Array1, Array2, Fib[1], Fib[0]);

                    Fib[1] -= Fib[0];
                  }
                  else
                  {
                    Multiphase_Merge(Fib[0], Fib[1], in2, in3, out1, out3, FileName2, FileName3, FileName1, c, k, Array1, -1, countComparison, countTransposition, 1);

                    Array2 = new int[Fib[0]];
                    Arrays(Array1, Array2, Fib[0], Fib[1]);

                    Fib[0] -= Fib[1];
                  }
                }
                else
                {
                  delete[] Array1;

                  if (Fib[0] < Fib[1])
                  {
                    Multiphase_Merge(Fib[1], Fib[0], in2, in3, out1, out3, FileName2, FileName3, FileName1, c, k, Array1, -1, countComparison, countTransposition, 1);

                    Array1 = new int[Fib[1]];
                    Arrays(Array2, Array1, Fib[1], Fib[0]);

                    Fib[1] -= Fib[0];
                  }
                  else
                  {
                    Multiphase_Merge(Fib[0], Fib[1], in2, in3, out1, out3, FileName2, FileName3, FileName1, c, k, Array1, -1, countComparison, countTransposition, 1);

                    Array1 = new int[Fib[0]];
                    Arrays(Array2, Array1, Fib[0], Fib[1]);

                    Fib[0] -= Fib[1];
                  }
                }
                k++;
              }
              clock_t t1 = clock();

              delete[] Array1;
              delete[] Array2;

              out << "Sorting by MultiPhaseMerge" << endl
                  << "Elements in array: " << c << endl
                  << "Time: " << (long double)(t1 - t0) / CLOCKS_PER_SEC << endl
                  << endl;
            }
          }
          break;
          }
        }
        break;

        case 2:
        {
          out1.open(FileName1, ios::trunc);

          while (dBorder < hBorder)
          {
            out1 << dBorder << endl;
            dBorder++;
          }
          cout << "\nDone.\n"
               << endl;

          out1.close();

          int answer3 = 0;
          cout << "\n1 - DirectMerge.\n2 - MultiPhaseMerge.\nEnter: ";
          cin >> answer3;
          cout << endl;
          switch (answer3)
          {
          case 1:
          {
            out.open(FileNameTime, ios::trunc);

            for (long c = s; c <= size; c += s)
            {
              int n1, n2 = 2, degreeoftwo = 1, size_two, k = 0, countComparison = 0, countTransposition = 0;

              while (pow(2, degreeoftwo) < c)
                degreeoftwo++;

              size_two = pow(2, degreeoftwo);
              n1 = size_two;

              clock_t t0 = clock();
              for (n2 = 2; n2 <= size_two; n2 *= 2)
              {
                Distribution(in1, out2, out3, FileName1, FileName2, FileName3, n1, n2 / 2, c);
                Direct_Merge(in2, in3, out1, FileName1, FileName2, FileName3, n2, c, k, countComparison, countTransposition, 2);

                n1 /= 2;

                k++;
              }
              clock_t t1 = clock();

              out << "Sorting by DirectMerge" << endl
                  << "Elements in array: " << c << endl
                  << "Time: " << (long double)(t1 - t0) / CLOCKS_PER_SEC << endl
                  << endl;
            }
          }
          break;

          case 2:
          {
            out.open(FileNameTime, ios::trunc);

            int k = 0, countComparison = 0, countTransposition = 0;

            int *Fib = new int[2];
            Fib[0] = 0;
            Fib[1] = 1;

            for (long c = s; c <= size; c += s)
            {
              while (Fib[0] + Fib[1] < c)
                if (Fib[0] < Fib[1])
                  Fib[0] += Fib[1];
                else
                  Fib[1] += Fib[0];

              int *Array1 = new int[(Fib[0] + Fib[1])];
              int *Array2 = new int[Fib[1]];

              for (size_t i = 0; i < (Fib[0] + Fib[1]); i++)
              {
                Array1[i] = 1;

                if (i >= c)
                  Array1[i] = 0;
              }

              InitialDistribution(in1, out2, out3, FileName1, FileName2, FileName3, c, Fib, -1);

              clock_t t0 = clock();
              while (Fib[0] + Fib[1] != 1)
              {
                if (k % 2 == 0)
                {
                  delete[] Array2;

                  if (Fib[0] < Fib[1])
                  {
                    Multiphase_Merge(Fib[1], Fib[0], in2, in3, out1, out3, FileName2, FileName3, FileName1, c, k, Array1, -1, countComparison, countTransposition, 1);

                    Array2 = new int[Fib[1]];
                    Arrays(Array1, Array2, Fib[1], Fib[0]);

                    Fib[1] -= Fib[0];
                  }
                  else
                  {
                    Multiphase_Merge(Fib[0], Fib[1], in2, in3, out1, out3, FileName2, FileName3, FileName1, c, k, Array1, -1, countComparison, countTransposition, 1);

                    Array2 = new int[Fib[0]];
                    Arrays(Array1, Array2, Fib[0], Fib[1]);

                    Fib[0] -= Fib[1];
                  }
                }
                else
                {
                  delete[] Array1;

                  if (Fib[0] < Fib[1])
                  {
                    Multiphase_Merge(Fib[1], Fib[0], in2, in3, out1, out3, FileName2, FileName3, FileName1, c, k, Array1, -1, countComparison, countTransposition, 1);

                    Array1 = new int[Fib[1]];
                    Arrays(Array2, Array1, Fib[1], Fib[0]);

                    Fib[1] -= Fib[0];
                  }
                  else
                  {
                    Multiphase_Merge(Fib[0], Fib[1], in2, in3, out1, out3, FileName2, FileName3, FileName1, c, k, Array1, -1, countComparison, countTransposition, 1);

                    Array1 = new int[Fib[0]];
                    Arrays(Array2, Array1, Fib[0], Fib[1]);

                    Fib[0] -= Fib[1];
                  }
                }
                k++;
              }
              clock_t t1 = clock();

              delete[] Array1;
              delete[] Array2;

              out << "Sorting by MultiPhaseMerge" << endl
                  << "Elements in array: " << c << endl
                  << "Time: " << (long double)(t1 - t0) / CLOCKS_PER_SEC << endl
                  << endl;
            }
          }
          break;
          }
        }
        break;

        case 3:
        {
          out.open(FileNameTime, ios::trunc);

          while (hBorder > dBorder)
          {
            out1 << hBorder << endl;
            hBorder--;
          }
          cout << "\nDone.\n"
               << endl;

          out1.close();

          int answer3 = 0;
          cout << "\n1 - DirectMerge.\n2 - MultiPhaseMerge.\nEnter: ";
          cin >> answer3;
          cout << endl;
          switch (answer3)
          {
          case 1:
          {
            out.open(FileNameTime, ios::trunc);

            for (long c = s; c <= size; c += s)
            {
              int n1, n2 = 2, degreeoftwo = 1, size_two, k = 0, countComparison = 0, countTransposition = 0;

              while (pow(2, degreeoftwo) < c)
                degreeoftwo++;

              size_two = pow(2, degreeoftwo);
              n1 = size_two;

              clock_t t0 = clock();
              for (n2 = 2; n2 <= size_two; n2 *= 2)
              {
                Distribution(in1, out2, out3, FileName1, FileName2, FileName3, n1, n2 / 2, c);
                Direct_Merge(in2, in3, out1, FileName1, FileName2, FileName3, n2, c, k, countComparison, countTransposition, 2);

                n1 /= 2;

                k++;
              }
              clock_t t1 = clock();

              out << "Sorting by DirectMerge" << endl
                  << "Elements in array: " << c << endl
                  << "Time: " << (long double)(t1 - t0) / CLOCKS_PER_SEC << endl
                  << endl;
            }
          }
          break;

          case 2:
          {
            out.open(FileNameTime, ios::trunc);

            int k = 0, countComparison = 0, countTransposition = 0;

            int *Fib = new int[2];
            Fib[0] = 0;
            Fib[1] = 1;

            for (long c = s; c <= size; c += s)
            {
              while (Fib[0] + Fib[1] < c)
                if (Fib[0] < Fib[1])
                  Fib[0] += Fib[1];
                else
                  Fib[1] += Fib[0];

              int *Array1 = new int[(Fib[0] + Fib[1])];
              int *Array2 = new int[Fib[1]];

              for (size_t i = 0; i < (Fib[0] + Fib[1]); i++)
              {
                Array1[i] = 1;

                if (i >= c)
                  Array1[i] = 0;
              }

              InitialDistribution(in1, out2, out3, FileName1, FileName2, FileName3, c, Fib, -1);

              clock_t t0 = clock();
              while (Fib[0] + Fib[1] != 1)
              {
                if (k % 2 == 0)
                {
                  delete[] Array2;

                  if (Fib[0] < Fib[1])
                  {
                    Multiphase_Merge(Fib[1], Fib[0], in2, in3, out1, out3, FileName2, FileName3, FileName1, c, k, Array1, -1, countComparison, countTransposition, 1);

                    Array2 = new int[Fib[1]];
                    Arrays(Array1, Array2, Fib[1], Fib[0]);

                    Fib[1] -= Fib[0];
                  }
                  else
                  {
                    Multiphase_Merge(Fib[0], Fib[1], in2, in3, out1, out3, FileName2, FileName3, FileName1, c, k, Array1, -1, countComparison, countTransposition, 1);

                    Array2 = new int[Fib[0]];
                    Arrays(Array1, Array2, Fib[0], Fib[1]);

                    Fib[0] -= Fib[1];
                  }
                }
                else
                {
                  delete[] Array1;

                  if (Fib[0] < Fib[1])
                  {
                    Multiphase_Merge(Fib[1], Fib[0], in2, in3, out1, out3, FileName2, FileName3, FileName1, c, k, Array1, -1, countComparison, countTransposition, 1);

                    Array1 = new int[Fib[1]];
                    Arrays(Array2, Array1, Fib[1], Fib[0]);

                    Fib[1] -= Fib[0];
                  }
                  else
                  {
                    Multiphase_Merge(Fib[0], Fib[1], in2, in3, out1, out3, FileName2, FileName3, FileName1, c, k, Array1, -1, countComparison, countTransposition, 1);

                    Array1 = new int[Fib[0]];
                    Arrays(Array2, Array1, Fib[0], Fib[1]);

                    Fib[0] -= Fib[1];
                  }
                }
                k++;
              }
              clock_t t1 = clock();

              delete[] Array1;
              delete[] Array2;

              out << "Sorting by MultiPhaseMerge" << endl
                  << "Elements in array: " << c << endl
                  << "Time: " << (long double)(t1 - t0) / CLOCKS_PER_SEC << endl
                  << endl;
            }
          }
          break;
          }
        }
        break;
        }
      }
    }
    break;
    }
  }
  return 0;
}