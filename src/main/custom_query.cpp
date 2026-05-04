#include "../RTree.cpp"
#include <string>
#include <vector>
#include <fstream>
using namespace std;

#define SHOW_USAGE cout << "Usage: " << argv[0] << " [RTree filename on bin/trees)] [x1] [y1] [x2] [y2]" << endl
#define CSV_OUT "customQuery.csv"

int main(const int argc, char ** argv) {

    if (constexpr int expected_arguments = 5; argc != expected_arguments + 1){
        cout << "Wrong number of arguments, received: " << argc - 1 << endl;
        SHOW_USAGE;
        return 0;
    }

    const float x1 =  stof(argv[2]),
    y1 =  stof(argv[3]),
    x2 =  stof(argv[4]),
    y2 =  stof(argv[5]);

#ifdef LOGLEVEL
    if constexpr (LOGLEVEL) cout<<x1<<' '<<y1<<' '<<x2<<' '<<y2<<endl;
#endif

    RTree arbol(argv[1]);

    const vector<float> results = arbol.encontrarPuntos(x1, y1, x2, y2);

    cout << "Se encontraron " << (results.size()>>1) << " puntos." << endl;

    ofstream csv(CSV_OUT);

    for (unsigned i = 0; i < results.size(); i+=2)
        csv << results[i] << ';' << results[i+1] << '\n';
    csv.close();
    return 0;
}