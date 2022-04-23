#include <iostream>
#include <vector>

using namespace std;

void quickSort(size_t begin, size_t end, vector<int>& arr){
    if(begin + 1 >= end){
        return;
    }
    int first = begin;
    int last = end - 1;
    int key = arr[first];
    while (first < last) {
        while (first < last && arr[last] >= key) {
            --last;
        }
        arr[first] = arr[last];
        while (first < last && arr[first] <= key) {
            ++first;
        }
        arr[last] = arr[first];
    }
    arr[first] = key;
    quickSort(begin, first, arr);
    quickSort(begin + 1, end, arr);
}

int main(){
    vector<int> a = {6,5,4,3,2};
    quickSort(0, a.size(), a);
    for(auto c: a){
        cout << c << " ";
    }
    return 0;
}