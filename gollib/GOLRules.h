#ifndef GOL_GOLRULES_H
#define GOL_GOLRULES_H

#include <vector>
#include <string>

//GOL rules according to https://www.conwaylife.com/wiki/Rulestring B{num_list}/S{num_list} notation
class GOLRules {
private:
    std::vector<short> bornNumbers;
    std::vector<short> surviveNumbers;
    static const std::string rulestringRegex;

    std::vector<short> numbersFromString(const std::string& numbersString);

public:
    GOLRules() = default;
    explicit GOLRules(const std::string &ruleString);
    GOLRules(GOLRules&& other) noexcept = default;
    GOLRules(GOLRules& other) = default;
    bool shouldBeAlive(int neighborCount, bool currentState);
    std::string getRuleString();

    GOLRules& operator=(GOLRules&& other) = default;
    GOLRules& operator=(const GOLRules& other) = default;
};


#endif //GOL_GOLRULES_H
