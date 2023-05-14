
#include <iostream>
#include <chrono>
using namespace std;
void merge(int *arr, int low, int mid, int high)
{
    int tmp[300];
    int i = low, k = low, j = mid + 1;
    while (i <= mid and j <= high)
    {
        if (arr[i] < arr[j])
        {
            tmp[k] = arr[i];
            i++;
            k++;
        }
        else
        {
            tmp[k] = arr[j];
            j++;
            k++;
        }
    }
    while (i <= mid)
    {
        tmp[k] = arr[i];
        i++;
        k++;
    }
    while (j <= high)
    {
        tmp[k] = arr[j];
        k++;
        j++;
    }
    for (int i = low; i < k; i++)
    {
        arr[i] = tmp[i];
    }
}
void Mergesort(int *arr, int low, int high)
{
    int mid;
    if (low < high)
    {
        mid = (low + high) / 2;
        Mergesort(arr, low, mid);
        Mergesort(arr, mid + 1, high);
        merge(arr, low, mid, high);
    }
}
int main()
{
    cout << "Enter number of elements to be sorted:";
    int num;
    cin >> num;
    int arr[num];
    cout << "Enter " << num << " elements to be sorted:";
    for (int i = 0; i < num; i++)
    {
        cin >> arr[i];
    }
    //  int start=clock();
    auto start = chrono::high_resolution_clock::now();
    Mergesort(arr, 0, num - 1);
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::nanoseconds>(stop - start);
    // int stop=clock();
    cout << "The duration is" << duration.count() << endl;
    cout << "Sorted array\n";
    for (int i = 0; i < num; i++)
    {
        cout << arr[i] << "\t";
    }
}