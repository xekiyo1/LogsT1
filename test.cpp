#include <bits/stdc++.h>
using namespace std;

int main() {
    string str;

    // Open the binary file for reading
    ifstream file("europa.bin", ios::binary);
    if (!file) {
        cerr << "Error opening file for reading.";
        return 1;
    }

    float hola[2];
    int i=0;
    while (file.read((char*)hola, sizeof(float)*2)) {
    	cout<<"punto "<<++i<<": "<<hola[0]<<' '<<hola[1]<<endl;
    }
    
    // Close file
    file.close();

    printf("encontré %d puntos",i);
    return 0;
}
