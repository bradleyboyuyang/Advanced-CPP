#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>

using InputFunction = std::function<double()>;
using OutputFunction = std::function<void(const std::vector<double>&)>;

class TMPClass final {
private:
    std::vector<double> vec;
    InputFunction inFunc;
    OutputFunction outFunc;
public:
    TMPClass() = default;
    TMPClass(std::size_t n, double startValue, InputFunction iFunction, OutputFunction oFunction): inFunc(iFunction), outFunc(oFunction)
    {
        vec.assign(n, startValue);
    }
    void compute() {
        double multiplier = inFunc();
        std::transform(vec.begin(), vec.end(), vec.begin(), [this](double& d) {return (this->inFunc()) * d; });
        outFunc(vec);
    }
};

int main()
{
    /// Part (A) Create a single class TMPClass consisting of a vector, 
    /// input device and output device. Build the code for the algorithm
    // See the class implementation above

    /// Part (B) The input device produces a hard-coded value 
    /// while you should implement the output device by a rangebased loop applied to the modified vector
    std::vector<double> testVec(5);
    double startValue = 15;
    double multiplier = 10;
    // Preprocessor: get the value that multiplies the elements of the vector
    InputFunction infunc = [multiplier]() {return multiplier; };

    // output device: use range-based loop
    OutputFunction outfunc = [](const std::vector<double>& vec) {
        for (const auto& element : vec) {
            std::cout << element << std::endl;
        }
    };
    std::size_t N = 5;
    TMPClass tmp(N, startValue, infunc, outfunc);
    tmp.compute();
}



    


