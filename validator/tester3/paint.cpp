#include<cstring>
#include<cassert>
#include<unordered_set>
#include"testlib.h"

constexpr int MN_STRLEN[] = {1, 1, 1, 1};
constexpr int MX_STRLEN[] = {10, 1000000, 1000, 1000000};
constexpr long long MN_COLOR[] = {1, 1, 1, 1};
constexpr long long MX_COLOR[] = {3, 2, 3, 7};
int subtask(int argc, char* argv[]) {
    for (int i=1; i<argc; i++) {
        if (!strcmp("--testcase", argv[i-1])) {
            return atoi(argv[i]);
        }
    }
    assert(0);
    return -1;
}
int main(int argc,char* argv[]) {
    registerValidation(argc, argv);
    int s = subtask(argc, argv);
    
    std::string instr = inf.readString("[a-zA-Z]{" + std::to_string(MN_STRLEN[s]) + "," + std::to_string(MX_STRLEN[s]) + "}");

    std::unordered_set<char> ht;
    for(auto chr: instr){
        ht.insert(chr);
    }
    if(ht.size() < MN_COLOR[s] || ht.size() > MX_COLOR[s]){
        quit(_wa, ("Number of char type(s) of input string " + instr + " violates the range [" + toHumanReadableString(MN_COLOR[s]) + ", " + toHumanReadableString(MX_COLOR[s]) +
                           "]").c_str());
    }
    
    inf.readEof();
}