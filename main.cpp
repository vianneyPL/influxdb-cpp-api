#include "api.hpp"

#include <algorithm>
#include <chrono>
#include <iomanip>
#include <random>
#include <string>

using api = idb::api::api;
using tag = idb::api::measurement::tag;
using str_field = idb::api::measurement::field<std::string>;
using double_field = idb::api::measurement::field<double>;
using int_field = idb::api::measurement::field<int>;
using measurement = idb::api::measurement::measurement;
using measurements = idb::api::measurement::measurements;

// need C++14 for auto lambda parameters
auto timing = [](auto && F, auto &&... params) {
    auto start = std::chrono::steady_clock::now();
    auto f_result = std::forward<decltype(F)>(F)(std::forward<decltype(params)>(params)...); // execute the function
    return std::make_pair(
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count(),
        f_result);
};

std::pair<measurements, double> generateMeasures(std::size_t number_of_points)
{
    static std::random_device rd;
    measurements measures;

    std::vector<std::pair<double, idb_time_t>> points(number_of_points);

    idb_time_t cursor = 1490206139;
    std::generate(points.begin(), points.end(),
                  [&cursor]() { return std::make_pair(static_cast<double>(cursor), cursor++); });

    double sum = 0.0;

    // auto range = std::make_pair(points.front().second, points.back().second);

    for (const auto & point : points)
    {
        sum += point.first;
        measurement mes("test");
        mes << double_field("double_value", point.first) << point.second;
        measures << mes;
    }
    sum /= points.size();

    return std::make_pair(measures, sum);
}

int main(int argc, char * argv[])
{
    try
    {
        api idb;

        idb = api("http://localhost:8086", "benchmark");

        idb.dropDatabase();
        idb.createDatabase();

        measurements measures;

        auto taken = timing(generateMeasures, 1'000'000);

        std::cout << "Took " << taken.first << " milliseconds" << std::endl;
        measures = taken.second.first;

        {
            std::cout << ":: start ::\n";
            auto start = std::chrono::steady_clock::now();
            idb.insert(measures);
            auto end =
                std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
            std::cout << "Took " << end << " milliseconds" << std::endl;
            std::cout << ":: end ::\n";
        }

        idb.select("MEAN(\"double_value\")", "\"test\"");
        std::cout << std::setprecision(10) << "result should be: " << taken.second.second << "\n";

        // idb.drop(mes);
    }
    catch (std::exception & e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}