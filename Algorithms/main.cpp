#include <iostream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>
using namespace std;

//fastest
//Insertion Sort: O(n^2) && Theta(n^2) && omega(n) STABLE
template<class T>
void Insertion_Sort(vector<T>&a, int n){
    int i,j;
    for(i=1 ; i<n ; i++){
        //if(a[i]<a[i-1]){
            T temp = a[i];
            j=i;
            for( ; j>0 && temp < a[j-1]; j--){
               /* if(temp>=a[j-1]){
                    break;
                }*/
                a[j] = a[j-1];
            }
            a[j] = temp;
        //}
    }
}

//intermediate
//Selection Sort: O(n^2) && Theta (n^2) && Omega(n^2) NOT STABLE
template<class T>
void Selection_Sort(vector<T>& a, int n){
    int i, j, min_index;
    for(j=0 ; j<n ; j++) {
        min_index = j ;
        for (i = j+1 ; i < n; i++) {
            if(a[i]<a[min_index]){
                min_index = i;
            }
        }
        if(min_index != j) {
            T temp = a[j];
            a[j] = a[min_index];
            a[min_index] = temp;
        }
    }
}

//slow
//Bubble Sort Bottom-up: O(n^2) && Theta(n^2) && Omega(n)//without flag (n^2) STABLE
template<class T>
void Bubble_Sort(T a[], int n){
    for(int j=0 ; j<n-1 ; j++) {
        bool flag = false;
        for (int i = n-1 ; i > j; --i) {
            if (a[i] < a[i - 1]) {
                /*a[i] ^= a[i + 1];
                a[i + 1] ^= a[i];
                a[i] ^= a[i + 1];*/
                flag = true;
                T temp = a[i];
                a[i] = a[i - 1];
                a[i - 1] = temp;
            }
        }
        if(!flag) break;
    }
}

//Shell Sort O(n^2) && Theta(O^1.5) && Omega(nlog(n))
template <class T>
void Shell_Sort(T a[], int n){
    for(int gap=n/2; gap>0; gap/=2){
        for(int i=gap; i<n ; i++){
            T temp = a[i];
            int j=i;
            for( ; j>=gap && temp<a[j-gap] ; j-=gap){
                a[j] = a[j-gap];
            }
            a[j] = temp;
        }
    }
}

//Merge sort: Merge O(n) and mergesort is called O(log(n))--> in total O(nlog(n))
// Space O(n) STABLE
template <typename T>
void merge(T arr[], int left, int mid, int right) {
    int size1 = mid - left + 1;
    int size2 = right - mid;
    T L[size1], R[size2];
    for (int i = 0; i < size1; i++) {
        L[i] = arr[left + i];
    }
    for (int i = 0; i < size2; i++) { //the mis is in the L so i = 1 to start R from the element after mid
        R[i] = arr[mid + 1 + i];
    }
    int i = 0, j = 0, k = left;
    while (i < size1 && j < size2) {
        if (L[i] > R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {                   //if R >= L  stable sort
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < size1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < size2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
template <typename T>
void Merge_Sort(T arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        Merge_Sort(arr, left, mid);
        Merge_Sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

//Quick Sort: O(n) && Theta(nlog(n)) && Omega(nlog(n)) NOT STABLE
template<class T>
void Quick_Sort(T a[], int left, int right){
    int i = left, j=right;
    T temp;
    T pivot = a[(left+right)/2];
    while(i<=j){
        while(a[i]<pivot){
            i++;
        }
        while(a[j]>pivot){
            j--;
        }
        if(i<=j){
            temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            i++;
            j--;
        }
    }
    if(left < j){
        Quick_Sort(a, left, j);
    }
    if(right > i){
        Quick_Sort(a, i, right);
    }
}

//Count Sort O(n+k) stable sort
void Count_Sort(std::vector<int>& arr) {
    // Find the maximum element in the array
    int maxElement = *max_element(arr.begin(), arr.end());

    // Create a count array to store the count of each unique element
    std::vector<int> count(maxElement + 1, 0);

    // Store the count of each element
    for (int num : arr) {
        count[num]++;
    }

    // Update the original array with sorted elements
    int index = 0;
    for (int i = 0; i <= maxElement; i++) {
        while (count[i] > 0) {
            arr[index++] = i;
            count[i]--;
        }
    }
}

//Radix Sort theta (d*(n+k))
// Stable sort
// Time Complexity : O(nk)
// Space Complexity : O(n + k)
template <typename T>
void radixSort(vector<T>& v) {
    int n = v.size();
    vector<int> count(10, 0);
    vector<T> temp(n);

    auto getDigit = [](T num) {
        if constexpr (is_integer_v<T>) {
            return num / pow(10, floor(log10(num)) + 1);
        } else {
            return 0;
        }
    };

    for (int exp = 1; n > 0 && find(v.begin(), v.end(), true) != v.end();
         exp *= 10) {
        fill(count.begin(), count.end(), 0);
        for (int i = 0; i < n; i++) {
            count[getDigit(v[i]) + 1]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            temp[count[getDigit(v[i]) + 1] - 1] = v[i];
            count[getDigit(v[i]) + 1]--;
        }

        v = temp;
    }

    return;
}

//Bucket Sort theta(n) + sum(i=0 to n-1)O(n(i)^2)  STABLE
void Bucket_Sort(vector<float>&arr){
    int n = arr.size();
    if(n<=0) return;
    vector<vector<float>> buckets(n);

    for(int i=0 ; i<n ;i++){
        int bucketIndex = n*arr[i];
        buckets[bucketIndex].push_back(arr[i]);
    }

    for(int i=0 ; i<n ;i++){
        Insertion_Sort(buckets[i],buckets[i].size());
    }

    int index = 0;
    for(int i=0 ;i<n ;i++){
        for(int j=0 ; j<buckets[i].size();j++){
            arr[index++] = buckets[i][j];
        }
    }
}
/*// Stable sort
// Time Complexity : O(n)
// Space Complexity : O(n)
template <typename T>
void bucketSort(vector<T>& v) {
  int n = v.size();
  vector<int> count(100, 0);
  vector<T> temp(n);
  double maxVal = *max_element(v.begin(), v.end());
  double minVal = *min_element(v.begin(), v.end());
  double range = maxVal - minVal + 1;

  for (int i = 0; i < n; i++) {
    count[(int)(v[i] * 100 / range)]++;
    temp[count[(int)(v[i] * 100 / range)] - 1] = v[i];
    count[(int)(v[i] * 100 / range)]--;
  }

  for (int i = 1; i <= 100; i++) {
    count[i] += count[i - 1];
  }

  for (int i = n - 1; i >= 0; i--) {
    temp[count[(int)(v[i] * 100 / range)] - 1] = v[i];
    count[(int)(v[i] * 100 / range)]--;
  }

  v = temp;
  return;}
  */
int main() {
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
