#include "GOLRules.h"

#include <regex>
#include <stdexcept>
#include <algorithm>
#include <iostream>

const std::string GOLRules::rulestringRegex = "[Bb](\\d*)\\/[Ss](\\d*)";

GOLRules::GOLRules(const std::string &ruleString) {
    std::regex ruleStringRegex = std::regex(GOLRules::rulestringRegex);
    std::smatch match;
    if(!std::regex_match(ruleString, match, ruleStringRegex))
    {
        throw std::invalid_argument("GOLRules: invalid ruleString");
    }

    bornNumbers = numbersFromString(match.str(1));
    surviveNumbers = numbersFromString(match.str(2));
    std::cout << "Born numbers" << '\n';
    for(short i : bornNumbers)
    {
        std::cout << i << '\n';
    }
    std::cout << "Survive numbers" << '\n';
    for(short i : surviveNumbers)
    {
        std::cout << i << '\n';
    }
}

bool GOLRules::shouldBeAlive(int neighborCount, bool currentState) {
    if(currentState)
    {
        return std::find(surviveNumbers.begin(), surviveNumbers.end(), neighborCount) != surviveNumbers.end();
    } else{
        return std::find(bornNumbers.begin(), bornNumbers.end(), neighborCount) != bornNumbers.end();
    }
}

std::vector<short> GOLRules::numbersFromString(const std::string &numbersString) {
    if(numbersString.empty())
    {
        return std::vector<short>();
    }
    std::vector<short> temp = std::vector<short>();
    for(char c : numbersString)
    {
        short value = c - '0';
        //If number is not already in the vector
        if(std::find(temp.begin(), temp.end(), value) == temp.end())
        {
            temp.push_back(value);
        }
    }

    return temp;
}

std::string GOLRules::getRuleString() {
    std::string output = std::string();
    output.append('B',1);
    for(auto val : bornNumbers)
    {
        output.append(static_cast<char>(val)+'0',1);
    }
    output.append("/S");
    for(auto val : surviveNumbers)
    {
        output.append(static_cast<char>(val)+'0',1);
    }

    return output;
}
