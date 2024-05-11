#include "SortStation.hpp"

using namespace MySortStation;
using namespace std;
int main() {
    initialize();

    auto tk = tokenize("1 + 1/(2*6)");

    for (int i=0; i<tk.size(); i++) {
        cout << tk[i].data << " ";
    }
    cout << endl;

    auto answer = sort(tk);
    float a = stof("3$");
    cout << a << endl;
    auto res = enumerate(answer);

    cout << res.data << endl;

    return 0;
}