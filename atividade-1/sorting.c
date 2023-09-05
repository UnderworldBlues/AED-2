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

void mergeSort (int *v, int n)
{
    int *w; 
    w = (int *)malloc(n * sizeof(int));
    mergeSortRec(v, w, 0, n - 1);
    free(w);
}

void mergeSortRec (int *v, int *w, int ini, int fim)
{
    int meio;
    if (ini < fim)
    {
        meio = (ini + fim) / 2;
        mergeSortRec(v, w, ini, meio);
        mergeSortRec(v, w, meio + 1, fim);
        merge(v, w, ini, meio, fim);
    }
}

void merge (int *v, int *w, int ini, int meio, int fim)
{
    int i, j, k;
    i = ini;
    j = meio + 1;
    k = ini;
    while ((i <= meio) && (j <= fim))
    {
        if (v[i] < v[j])
        {
            w[k++] = v[i++];
        }
        else
        {
            w[k++] = v[j++];
        }
    }
    while (i <= meio)
    {
        w[k++] = v[i++];
    }
    while (j <= fim)
    {
        w[k++] = v[j++];
    }
    for (i = ini; i <= fim; i++)
    {
        v[i] = w[i];
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