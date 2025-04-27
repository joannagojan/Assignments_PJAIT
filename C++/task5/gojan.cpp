#include <iostream>
#include <string>
#include <cctype>
#include <vector>



class ValidatorAbstract {
    public: 
    virtual bool validateText(std::string text;);
}

class ValidateOccurences {
    public: 
    int target;
    ValidatorAbstract validator;

    ValidateOccurences(int target, ValidatorAbstract validator, std::string text) : target(target), validator(validator) {
        validateTarget(target)
    }
    countOccurences();

    private:
    bool validateTarget(int target) [
        return target >= 0;
    ]

}

class ValidatePassword {
    public: 
    std::vector<ValidateOccurences> 
}

class ValidateAlpha : class ValidatorAbstract {
    validateText()
}

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


}


int main() {
    std::cout << isLetter('3') << '\n';

using std::cout; using std::endl;


const std::string passes[] =
{
"AbcDe93", "A1b:A1b>", "Ab:Acb<",
"abc123><", "Zorro@123"
};


for (size_t i = 0; i < std::size(passes); ++i) {
cout << "checking " << passes[i] << endl;
if (checkpass(passes[i])) cout << "OK" << endl;
cout << endl;

    }
}