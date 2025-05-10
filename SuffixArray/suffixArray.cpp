#include <iostream>
using namespace std;

class SuffixArray {
private:
    struct Suffix {
        int index;
        int rank[2];
    };

    char* array; // array[0] = 'A'
    int size;
    Suffix* suffixies; // suffixies[0] == 14

    void merge(Suffix* suff, int left, int mid, int right) {
        int size1 = mid - left + 1;
        int size2 = right - mid;

        Suffix* L = new Suffix[size1];
        Suffix* R = new Suffix[size2];
        for (int i = 0; i < size1; i++) {
            L[i] = suff[left + i];
        }
        for (int i = 0; i < size2; i++) {
            R[i] = suff[mid + 1 + i];
        }

        int i = 0, j = 0, k = left;
        while (i < size1 && j < size2) {
            if (L[i].rank[0] < R[j].rank[0] || ((L[i].rank[0] == R[j].rank[0]) && (L[i].rank[1] <= R[j].rank[1]))) {
                suff[k++] = L[i++];
            } else {
                suff[k++] = R[j++];
            }
        }
        while (i < size1) suff[k++] = L[i++];
        while (j < size2) suff[k++] = R[j++];

        delete[] L;
        delete[] R;
    }

    void mergeSort(Suffix* suff, int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSort(suff, left, mid);
            mergeSort(suff, mid + 1, right);
            merge(suff, left, mid, right);
        }
    }

public:
    SuffixArray(std::string arr) {
        size = arr.size();
        array = new char[size];
        suffixies = new Suffix[size];
        for (int i = 0; i < size; i++) {
            array[i] = arr[i];
        }
    }

    ~SuffixArray() {
        delete[] array;
        delete[] suffixies;
    }

    void Print() {
        for (int i = 0; i < size; ++i) {
            std::cout << suffixies[i].index << ' ';
        }
        std::cout << '\n';
    }

    void ConstructUsingPrefixDoubling() {

        for (int i = 0; i < size; ++i) {
            suffixies[i].index = i;
            suffixies[i].rank[0] = array[i]; // Initialize with ASCII code k=1
            suffixies[i].rank[1] = (i + 1 < size) ? array[i + 1] : -1; // For k=2 rank of the next char if there is no next -1
        }

        mergeSort(suffixies, 0, size - 1);
        for (int k = 4; k < 2 * size; k *= 2) {
            int currentRank = 0;
            int prevRank = suffixies[0].rank[0];
            suffixies[0].rank[0] = currentRank;

            for (int i = 1; i < size; ++i) {
                if (suffixies[i].rank[0] == prevRank && suffixies[i].rank[1] == suffixies[i - 1].rank[1]) {
                    suffixies[i].rank[0] = currentRank;
                } else {
                    prevRank = suffixies[i].rank[0];
                    suffixies[i].rank[0] = ++currentRank;
                }
            }
            int* rank = new int[size];
            for (int i = 0; i < size; ++i) {
                rank[suffixies[i].index] = i;
            }

            for (int i = 0; i < size; ++i) {
                suffixies[i].rank[1] = (suffixies[i].index + k / 2 < size)? suffixies[rank[suffixies[i].index + k / 2]].rank[0]: -1;
            }
            mergeSort(suffixies, 0, size - 1);
            delete[] rank;
        }
    }
};

int main() {
    SuffixArray t("ACGACTACGATAAC$");
    t.ConstructUsingPrefixDoubling();
    t.Print(); // Prints: 14 11 12 0 6 3 9 13 1 7 4 2 8 10 5
    return 0;
}
