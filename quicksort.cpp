#include "cabecalho.h"

void swap(policial *&a, policial *&b)
{
    policial * aux = a;
    a = b;
    b = aux;
}

int partition(policial ** arr, int low, int high)
{
    policial * pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++)
    {
        if (strcmp(arr[j]->nome, pivot->nome) < 0)
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quicksort(policial ** arr, int low, int high)
{
    if (low < high)
    {
        int pivotIndex = partition(arr, low, high);

        quicksort(arr, low, pivotIndex - 1);
        quicksort(arr, pivotIndex + 1, high);
    }
}