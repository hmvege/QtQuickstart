#include <iostream>
#include <vector>

class ValuesClass {
private:
    std::vector<double> m_values;
public:
    ValuesClass() {}
    ~ValuesClass() {}

    void printValues() {
        for (int i = 0; i < m_values.size(); i++) {
            std::cout << m_values[i] << std::endl;
        }
    }

    ValuesClass &operator+=(const ValuesClass other) {
        m_values.insert(m_values.end(), other.m_values.begin(), other.m_values.end());
        return *this;
    }

    ValuesClass &operator+=(const double other) {
        m_values.push_back(other);
        return *this;
    }
};

int main()
{
    ValuesClass val1;
    ValuesClass val2;

    val1 += 3.0;
    val1 += 4.0;
    val2 += 1.0;
    val2 += 2.0;
    val2 += val1;

    std::cout << "Printing values:" << std::endl;
    val2.printValues();

    return 0;
}