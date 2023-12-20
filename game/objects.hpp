#include <vector>
#include <string>

class notePattern {

    public:
        void decode(std::string fpath);

    private:
        std::vector<int> notevector;
        int BPM;
};