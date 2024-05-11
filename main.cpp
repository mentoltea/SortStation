#include "SortStation.hpp"

using namespace MySortStation;
using namespace std;
int main() {
    initialize();

    string q = "1 + 1/(2+1) - (3*3)/(1.5*1.5)";
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