#ifndef UTILLITY
#define UTILLITY

#include <vector>

namespace Utillity {
    std::vector<std::string> splitString(std::string str, std::string delimiter) {
        std::string buffer = str;
        std::vector<std::string> splits;
        while (buffer.size() != 0) {
            int indexAt = buffer.find(delimiter, 0);
            if (indexAt == -1) {
                splits.push_back(buffer);
                break;
            }
            std::string curr_split = buffer.substr(0, indexAt);
            buffer.erase(0, indexAt + delimiter.size());
            splits.push_back(curr_split);
        }
        return splits;
    }
}

#endif