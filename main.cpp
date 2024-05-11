#include "SortStation.hpp"

using namespace MySortStation;
using namespace std;
int main(int argc, char** argv) {
    if (argc<2) return 0;
    string q = argv[1];
    
    initialize();
    cout << q << endl;
    auto tk = tokenize(q);

    for (int i=0; i<tk.size(); i++) {
        cout << tk[i].data << " ";
    }
    cout << endl;

    auto answer = sort(tk);
    auto ans = answer;

    for (; !ans.empty(); ans.pop()) {
        cout << ans.front().data << " ";
    }
    cout << endl;
    
    auto res = enumerate(answer);

    cout << res.data << endl;

    return 0;
}