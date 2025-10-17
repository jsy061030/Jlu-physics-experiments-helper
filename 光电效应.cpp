#include <iostream>
#include <vector>
#include <boost/math/statistics/linear_regression.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

int main()
{
    std::vector<int> waveLength = { 365, 405, 436, 546, 577};
    std::vector<double> frequency;
    std::vector<double> stopVoltage;
    const double c = 2.998e8;
    std::cout << "请输入对应波长（单位：纳米）的截止电压（单位：伏特 V，取正数）：\n";
    for (int i = 0; i < 5; i++) {
        double vot;
        std::cout << waveLength[i] << " nm: ";
        std::cin >> vot;
        stopVoltage.push_back(vot);
        frequency.push_back(c / (waveLength[i] * 1e-9));
    }
    auto [c0, c1] = boost::math::statistics::simple_ordinary_least_squares(frequency, stopVoltage);
    std::cout << "回归截距: " << c0 << ", 斜率: " << c1 << std::endl;
	std::cout << "计算得普朗克常数 h = 斜率 * 电荷量 e = " << c1 * 1.602e-19 << " J·s" << std::endl;
	std::cout << "计算得金属逸出功 W = -截距 * 电荷量 e = " << -c0 * 1.602e-19 << " J" << std::endl;
	std::cout << "样本相关系数 r = " << boost::math::statistics::correlation_coefficient(frequency, stopVoltage) << std::endl;

    return 0;
}

