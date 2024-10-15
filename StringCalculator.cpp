
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

class StringCalculator {
public:
    int add(const std::string& numbers) {
        if (numbers.empty()) return 0;

        std::vector<int> nums = ParseNumbers(numbers);
        ValidateNumbers(nums);
        
        int sum = 0;
        for (int num : nums) {
            sum += num;
        }
        return sum;
    }

private:
    std::vector<int> ParseNumbers(const std::string& numbers) {
        std::vector<int> nums;
        std::istringstream stream(numbers);
        std::string token;
        char delimiter = ',';

        while (std::getline(stream, token, delimiter)) {
            std::istringstream lineStream(token);
            while (std::getline(lineStream, token, '\n')) {
                nums.push_back(std::stoi(token));
            }
        }
        return nums;
    }

    void ValidateNumbers(const std::vector<int>& nums) {
        for (int num : nums) {
            if (num < 0) {
                throw std::invalid_argument("Negative numbers are not allowed: " + std::to_string(num));
            }
        }
    }
};

// Test cases
void RunTests() {
    StringCalculator calc;

    // Test empty string
    assert(calc.add("") == 0);

    // Test single number
    assert(calc.add("1") == 1);
    assert(calc.add("5") == 5);

    // Test two numbers
    assert(calc.add("1,2") == 3);
    assert(calc.add("3,4") == 7);

    // Test multiple numbers
    assert(calc.add("1,2,3") == 6);
    assert(calc.add("4,5,6,7") == 22);
    
    // Test new line as separator
    assert(calc.add("1\n2,3") == 6);
    assert(calc.add("1\n2\n3") == 6);

    // Test negative number exception
    try {
        calc.add("1,-2");
    } catch (const std::invalid_argument& e) {
        std::cout << e.what() << std::endl;  // Expected negative number exception
    }
}

int main() {
    RunTests();
    std::cout << "All tests passed!" << std::endl;
    return 0;
}
