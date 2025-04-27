#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <functional>
#include <stdexcept>


class ValidatorAbstract {
    public: 
    virtual bool validate(const std::string& text) const = 0;
    virtual std::string getError() const = 0;
};

class ValidateOccurences : ValidatorAbstract {
    public:
    ValidateOccurences(std::function<bool(char)> condition, int target) : 
    condition(condition), target(target) {validate(target);};


    bool validate(const std::string& text) override {
        int counter = 0;
        for (auto c: text) {
            if (condition(c)) {counter++;};
        }
        return counter >= target;
    }

    private:
        std::function<bool(char)> condition;
        int target;

        void validate(int target) {
            if (target <= 0) {
                throw std::invalid_argument("The counter target is cannot not positive");
            };
        }
};



bool isLetter(char c) {
    return std::isalpha(c);
}

bool isDigit(char c) {
    return std::isdigit(c);
}

bool isUppercase(char c) {
    return std::isupper(c);
}

bool isLowercase(char c) {
    return std::islower(c);
}

bool isNonAlphanumeric(char c) {
    return !std::isalnum(c);
}

bool isStringBiggerThanTarget(const std::string& text, int target) {
    return text.size() >= target;
}

bool isCharDistinct(const std::string& text, int charIndex) {
    char target = text[charIndex];
    return (text.find(target, charIndex + 1)) == std::string::npos;
}




bool checkpass(const std::string& password) {
    return true;
}


int main() {



// const std::string passes[] =
// {
// "AbcDe93", "A1b:A1b>", "Ab:Acb<",
// "abc123><", "Zorro@123"
// };


// for (size_t i = 0; i < std::size(passes); ++i) {
// cout << "checking " << passes[i] << endl;
// if (checkpass(passes[i])) cout << "OK" << endl;
// cout << endl;
    // }
}