#include <iostream>
#include <vector>
#include<cassert>

using namespace std;

int dotProduct(const vector<int>& v1, const vector<int>& v2) {
    assert(v1.size() == v2.size() && "Los vectores deben tener la misma longitud");

    int result = 0;
    for (size_t i = 0; i < v1.size(); ++i) {
        result += v1[i] * v2[i];
    }
    return result;
}

int main() {
    vector<int> vector1 = {1, 2, 3, 7};
    vector<int> vector2 = {4, 5, 6, 8};

    cout << "Vector 1: ";
    for (int x : vector1) cout << x << " ";
    cout << "\nVector 2: ";
    for (int x : vector2) cout << x << " ";

    int result = dotProduct(vector1, vector2);

    cout << "\n\nEl producto punto de los dos vectores es: " << result << endl;

    return 0;
}
