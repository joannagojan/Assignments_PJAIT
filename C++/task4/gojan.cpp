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
    
        void validate(const std::vector<ShiftAndMask>& bitLayout) {
            uint16_t all_masks = 0;
            for (const auto& element : bitLayout) {
                uint16_t mask = element.get_mask();
                if ((all_masks & mask) != 0)
                    throw std::invalid_argument("The masks are overlapping");
                all_masks |= mask;
            }
        }
    
    public:
        EncoderService(const std::vector<ShiftAndMask>& bitLayout)
            : bitLayout(bitLayout) { validate(bitLayout); }
    
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

    
    class DecoderService {
        private:
            uint16_t code;
            std::vector<ShiftAndMask> layout;
        
        public:
            DecoderService(uint16_t code, const std::vector<ShiftAndMask>& layout)
                : code(code), layout(layout) {}
        
            uint16_t getCode() { return this->code; }
        
            void printValues() const {
                for (const auto& mask : layout) {
                    uint16_t value = (code & mask.get_mask()) >> mask.get_position();
                    std::cout << std::setw(20) << std::left << (mask.get_name() + ":") << value << '\n';
                }
            }
        };
    
std::vector<ShiftAndMask> createLayout() {
    return {
        ShiftAndMask(15, 1, "sex"),
        ShiftAndMask(13, 2, "marital status"),
        ShiftAndMask(11, 2, "age group"),
        ShiftAndMask(9, 2, "education"),
        ShiftAndMask(7, 2, "living place"),
        ShiftAndMask(3, 4, "region"),
        ShiftAndMask(0, 3, "answer")
    };
}





int main() {
    try{

        std::vector<ShiftAndMask> layout = createLayout();
        EncoderService encoder(layout);

        std::vector<int> w_married_3145_elementary_bigCity_13_6 = {0, 1, 1, 0, 3, 13, 6};
        std::vector<int> w_divorced_3145_uni_country_12_6 = {0, 3, 2, 3, 0, 12, 6};
        std::vector<int> m_bachelor_3145_highschool_smallCity_6_7 = {1, 0, 3, 1, 3, 6, 7};

        uint16_t code_married = encoder.encode(w_married_3145_elementary_bigCity_13_6);
        uint16_t code_divorced = encoder.encode(w_divorced_3145_uni_country_12_6);
        uint16_t code_bachelor = encoder.encode(m_bachelor_3145_highschool_smallCity_6_7);


        std::cout << "Result w_married_3145_elementary_bigCity_13_6: " << std::bitset<16>(code_married ) << '\n';
        DecoderService decoder_married(code_married, layout);
        decoder_married.printValues();

        std::cout << "Result w_divorced_3145_uni_country_12_6: " << std::bitset<16>(code_divorced) << '\n';
        DecoderService decoder_divorced(code_divorced, layout);
        decoder_divorced.printValues();

        std::cout << "Result m_bachelor_3145_highschool_smallCity_6_7: " << std::bitset<16>(code_bachelor) << '\n';
        DecoderService decoder_bachelor(code_bachelor, layout);
        decoder_bachelor.printValues();


    }
    catch (std::invalid_argument const& ex)
    {
        std::cout << "Invalid argument:  " << ex.what() << '\n';
    }
    return 0;
}
