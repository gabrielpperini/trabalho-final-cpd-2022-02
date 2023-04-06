#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <algorithm>

#include "infra.cpp"

using namespace std;

class Quicksort
{
private:

    string order;

    int getPivotIndex(int left, int right)
    {
        return (left + right) / 2.0;
    }

    int particione_hoare(std::vector<PlayerData> *v, int p, int r, PlayerData pivot)
    {
        int i = p - 1, j = r + 1;

        while (true)
        {
            do
            {
                i++;
            } while (order == "DESC" ? v->at(i).rating > pivot.rating : v->at(i).rating < pivot.rating);
            do
            {
                j--;
            } while (order == "DESC" ? v->at(j).rating < pivot.rating : v->at(j).rating > pivot.rating);
            if (i >= j)
            {
                return j;
            }
            swap((*v)[i], (*v)[j]);
        }
    }

    int particione(std::vector<PlayerData> *v, int p, int r)
    {
        int pivotIndex = getPivotIndex(p, r);
        PlayerData pivot = v->at(pivotIndex);
        swap((*v)[pivotIndex], (*v)[r]);
        return particione_hoare(v, p, r, pivot);
    }

    void _quicksort(std::vector<PlayerData> *v, int i, int f)
    {
        int p; // índice do pivô
        if (f > i)
        {
            p = particione(v, i, f);
            _quicksort(v, i, p);
            _quicksort(v, p + 1, f);
        }
    }

public:
    Quicksort(string _order){
        order = _order;
    }

    //--------------------------------------------------------------
    void sort(std::vector<PlayerData> *v, int tam)
    //--------------------------------------------------------------
    {
        _quicksort(v, 0, tam - 1);
    }
};

// int main(int argc, char const *argv[])
// {
//     std::vector<float> io{1.0, 4.0, 3.0, 2.0, 5.0};
//     Q<float> o;

//     o.sort(&io, io.size());

//     for (auto &&i : io)
//     {
//         cout << i << endl;
//     }

//     return 0;
// }
