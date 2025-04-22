#include <bitset>
#include <iostream>
#include <stdexcept> 
#include <cstdint>
#include <vector>
#include <iomanip>



class ShiftAndMask {
private:
    int position;
    int digits_used;
    std::string name;

    void validate(int position, int digits_used) {
        if (digits_used <= 0 || digits_used > 16)
            throw std::invalid_argument("Digits cannot be bigger than 16");

        if (position < 0 || position > 15)
            throw std::invalid_argument("Choose bit from 0 to 15");
    }

public:
    ShiftAndMask(int position, int digits_used, std::string name) {
        validate(position, digits_used);
        set_position(position);
        set_digits(digits_used);
        set_name(name);
    }

    int get_position() const { return this->position; }
    int get_digits_used() const { return this->digits_used;}
    std::string get_name() const {return this->name;}

    void set_position(int position) {
        this->position = position;
    }
    void set_digits(int digits_used) {
        this->digits_used = digits_used;
    }
    void set_name(std::string name) {
        this->name = name;
    }

    uint16_t get_mask() const {
        int ones_repr = (1 << digits_used) - 1;
        return ones_repr << position;
    }

};

class EncoderService {
    private:
        std::vector<ShiftAndMask> bitLayout;

    void validate(const std::vector<ShiftAndMask>& bitLayout) 
        uint16_t all_masks = 0;
        for (const auto& element : bitLayout) {
            uint16_t mask = element.get_mask();
            if ((all_masks & mask) != 0)
                throw std::invalid_argument("The masks are overlapping");
            all_masks |= mask;
        }
    
    public:
        MasksAndShiftsService(const std::vector<ShiftAndMask>& bitLayout)
            : bitLayout(bitLayout) {validate(bitLayout);}
    
        uint16_t encode(const std::vector<int>& values) {
            if (bitLayout.size() != values.size())
            throw std::invalid_argument("The number of masks needs to match values");

            uint16_t result = 0;
            for (int i = 0; i < values.size(); i++) {
                result |= (values[i] << bitLayout[i].get_position());
            }
            return result;
        }
    };

class FromCodeToValuesService {
    private:
    uint16_t code;


    public: 
    FromCodeToValuesService(uint16_t code);
    
    uint16_t getCode() {return this->code;}
    void printValues(std::vector<ShiftAndMask> set) {
        for (auto& element: set) {
            uint16_t value = (code & element.get_mask()) >> element.get_position();
            std::cout << std::setw(20) << std::left <<(element.get_name() + ":") << value <<  '\n';
        }
    };

}
    

unsigned short encode(int sex,
    int marit,
    int age,
    int edu,
    int place, int region,
    int answer) {

    // SMMAAEEPPRRRRAAA
    ShiftAndMask sex_code(15, 1, "sex");
    ShiftAndMask marital_code(13, 2, "marital status");
    ShiftAndMask age_code(11, 2, "age group");
    ShiftAndMask edu_code(9, 2, "education");
    ShiftAndMask place_code(7, 2, "living place");
    ShiftAndMask region_code(3, 4, "region");
    ShiftAndMask answer_code(0, 3, "answer");

    std::vector<int> values = { sex, marit, age, edu, place, region, answer };
    std::vector<ShiftAndMask> set = { sex_code, marital_code, age_code, edu_code, place_code, region_code, answer_code };
    MasksAndShiftsService service(w_divorced_3145_uni_country_12_6);
    uint16_t calculate_number = service.setValues(set);

    return calculate_number;
}


// void info(unsigned short code) {
//     ShiftAndMask sex_code(15, 1, "sex");
//     ShiftAndMask marital_code(13, 2, "marital status");
//     ShiftAndMask age_code(11, 2, "age group");
//     ShiftAndMask edu_code(9, 2, "education");
//     ShiftAndMask place_code(7, 2, "living place");
//     ShiftAndMask region_code(3, 4, "region");
//     ShiftAndMask answer_code(0, 3, "answer");

//     std::vector<ShiftAndMask> set = { sex_code, marital_code, age_code, edu_code, place_code, region_code, answer_code };

//     for (auto& element: set) {
//         uint16_t value = (code & element.get_mask()) >> element.get_position();
//         std::cout << std::setw(20) << std::left <<(element.get_name() + ":") << value <<  '\n';
//     }
// }

int main() {
    try{
        unsigned short w_married_3145__elementary_bigCity_13_6 = encode(0, 1, 1, 0, 3, 13, 6);
        unsigned short w_divorced_3145_uni_country_12_6 = encode(0,3,2,3,0,12,6);
        unsigned short m_bachelor_3145_highschool_smallCity_6_7 = encode(1,0,3,1,3,6,7);

        std::cout << "---------------------------------------------" << '\n';
        std::cout << "result for w_married_3145__elementary_bigCity_13_6: " << '\n' <<  
        std::bitset<16>(w_married_3145__elementary_bigCity_13_6) << '\n';
        // ShiftAndMask sex_code(15, 1, "sex");
        // ShiftAndMask marital_code(13, 2, "marital status");
        // ShiftAndMask age_code(11, 2, "age group");
        // ShiftAndMask edu_code(9, 2, "education");
        // ShiftAndMask place_code(7, 2, "living place");
        // ShiftAndMask region_code(3, 4, "region");
        // ShiftAndMask answer_code(0, 3, "answer");
        // std::vector<ShiftAndMask> set = { sex_code, marital_code, age_code, edu_code, place_code, region_code, answer_code };
        // FromCodeToValuesService codeService(w_divorced_3145_uni_country_12_6);
        // codeService.printValues();
        // info(w_married_3145__elementary_bigCity_13_6);

        std::cout << "---------------------------------------------"<< '\n';
        std::cout << "result for w_divorced_3145_uni_country_12_6: " << '\n' << 
        std::bitset<16>(w_divorced_3145_uni_country_12_6) << '\n';
        // info(w_divorced_3145_uni_country_12_6);

        std::cout << "---------------------------------------------"<< '\n';
        std::cout << "result for m_bachelor_3145_highschool_smallCity_6_7 : " << '\n' <<  
        std::bitset<16>(m_bachelor_3145_highschool_smallCity_6_7 ) << '\n';
        // info(m_bachelor_3145_highschool_smallCity_6_7);


    }
    catch (std::invalid_argument const& ex)
    {
        std::cout << "Invalid argument:  " << ex.what() << '\n';
    }
    return 0;
}
