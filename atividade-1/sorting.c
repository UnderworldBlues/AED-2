#include "sorting.h"

void bubbleSort (int *v, int n)
{
    int i, j, aux;
    for (i = 0; i < n; i++)
    {
        for (j = (i + 1); j < n; j++)
        {
            if (v[i] > v[j])
            {
                aux = v[i];
                v[i] = v[j];
                v[j] = aux;
            }
        }
    }
}

void insertionSort (int *v, int n)
{
    int i, j, aux;
    for (i = 1; i < n; i++)
    {
        aux = v[i];
        for (j = i; (j > 0) && (aux < v[j - 1]); j--)
        {
            v[j] = v[j - 1];
        }
        v[j] = aux;
    }
}

void selectionSort (int *v, int n)
{
    int i, j, min, aux;
    for (i = 0; i < (n - 1); i++)
    {
        min = i;
        for (j = (i + 1); j < n; j++)
        {
            if (v[j] < v[min])
            {
                min = j;
            }
        }
        if (v[i] != v[min])
        {
            aux = v[i];
            v[i] = v[min];
            v[min] = aux;
        }
    }
}

void shellSort (int *v, int n)
{
    int i, j, aux, h;
    h = 1;
    do
    {
        h = (h * 3) + 1;
    } while (h < n);
    do
    {
        h /= 3;
        for (i = h; i < n; i++)
        {
            aux = v[i];
            j = i;
            while (v[j - h] > aux)
            {
                v[j] = v[j - h];
                j -= h;
                if (j < h)
                {
                    break;
                }
            }
            v[j] = aux;
        }
    } while (h != 1);
}

void ABCsort (int *v, int i, int j) 
{
    if(v[i] > v[j])
    {
        int aux = v[i];
        v[i] = v[j];
        v[j] = aux;
    }
    if((i+1) >= j)
    {
        return;
    }
    int k = (j-i+1)/3;

    ABCsort(v, i, j-k);
    ABCsort(v, i+k, j);
    ABCsort(v, i, j-k);
}