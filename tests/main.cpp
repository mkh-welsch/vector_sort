// Copyright (c) 2018 S. D. Adams <s.d.adams.software@gmail.com>

#include <functional>
#include <cstring>
#include <algorithm>
#include <numeric>

#include <vector>
#include <random>
#include <iostream>
#include <thread>

#include "modified_qs_double.hpp"
#include "inplace_qs_double.hpp"
#include "../vector_sort.hpp"

#include "dualPivot.hpp"
#include "qs_int.hpp"
#include "qs_float.hpp"
#include "qs_double.hpp"

#define TEST_DOUBLES 1
#define TEST_FLOATS 1
#define TEST_INTS 1
#define ENABLE_THOROUGH 1

namespace {
int const distribution_min = 1;
int const distribution_max = 100;
int const num_elements = 1000000;
int const test_iterations = 10;
}

// Represents a single run of the algorithm.
struct algorithm_assessment
{
    bool correct;
    int64_t microseconds_duration;

    // Test results can be 'appended', allowing for multiple runs to get a total duration, from which an average can be computed.
    void append(algorithm_assessment const &that)
    {
        this->correct &= that.correct;
        this->microseconds_duration += that.microseconds_duration;
    }
};

// Tests the correctness and time duration of the given sorting algorithm.
template <typename algorithm_type, typename element_type, template <typename container_element_type, typename _Alloc = std::allocator<element_type> > class container_type>
algorithm_assessment
assess_sort_implementation (algorithm_type const sort_implementation, container_type<element_type> & vec)
{
    std::chrono::high_resolution_clock::time_point time_began = std::chrono::high_resolution_clock::now();
    sort_implementation(vec);
    std::chrono::high_resolution_clock::time_point time_finished = std::chrono::high_resolution_clock::now();

    bool const correct = std::is_sorted(vec.begin(), vec.end());
    int64_t const microseconds_duration = std::chrono::duration_cast<std::chrono::microseconds>(time_finished - time_began).count();

    return algorithm_assessment {correct, microseconds_duration};
}

struct algorithm_comparison
{
    algorithm_assessment std_sort_assessment;
    algorithm_assessment avx2_quicksort_assessment;
    algorithm_assessment modified_avx2_quicksort_assessment;
    algorithm_assessment inplace_avx2_quicksort_assessment;
    algorithm_assessment dual_pivot_quicksort_assessment;
    algorithm_assessment vector_sort_assessment;
};

int main()
{
    std::random_device rnd_device;
    std::mt19937 mersenne_engine(rnd_device());

    std::uniform_int_distribution<int> int_distribution(distribution_min, distribution_max);
    auto int_generator = std::bind(int_distribution, mersenne_engine);

    std::uniform_real_distribution<float> float_distribution(distribution_min, distribution_max);
    auto float_generator = std::bind(float_distribution, mersenne_engine);

#if TEST_DOUBLES
    algorithm_comparison comparison_doubles = {
        {true, 0},
        {true, 0},
        {true, 0},
        {true, 0},
        {true, 0},
        {true, 0}
    };
    for (int i = 0; i < test_iterations; ++i)
    {
        std::vector<double> vec1(num_elements);
        std::generate(begin(vec1), end(vec1), float_generator);

        std::vector<double> vec2(vec1);
        std::vector<double> vec3(vec1);
        std::vector<double> vec4(vec1);
        std::vector<double> vec5(vec1);
        std::vector<double> vec6(vec1);

        comparison_doubles.std_sort_assessment.append(assess_sort_implementation([](std::vector<double> & v) {return std::sort(v.begin(), v.end());}, vec1));
        comparison_doubles.avx2_quicksort_assessment.append(assess_sort_implementation([](std::vector<double> & v){return quickdouble::qs_double(v);}, vec2));
        comparison_doubles.modified_avx2_quicksort_assessment.append(assess_sort_implementation([](std::vector<double> & v){return modified_quickdouble::qs_double(v);}, vec4));
//        comparison_doubles.inplace_avx2_quicksort_assessment.append(assess_sort_implementation([](std::vector<double> & v){return inplace_quickdouble::qs_double(v);}, vec5));
        comparison_doubles.dual_pivot_quicksort_assessment.append(assess_sort_implementation([](std::vector<double> & v){return dualPivot::sort(v);}, vec3));
        comparison_doubles.vector_sort_assessment.append(assess_sort_implementation([](std::vector<double> & v){return vector_sort::sort(v);}, vec6));

#if ENABLE_THOROUGH
        for (int i = 0; i < num_elements; ++i)
        {
            assert (vec6.at(i) == vec1.at(i));
        }
#endif
    }
#endif

#if TEST_FLOATS
    algorithm_comparison comparison_floats = {
        {true, 0},
        {true, 0},
        {true, 0},
        {true, 0},
        {true, 0},
        {true, 0}
    };
    for (int i = 0; i < test_iterations; ++i)
    {
        std::vector<float> vec1(num_elements);
        std::generate(begin(vec1), end(vec1), float_generator);

        std::vector<float> vec2(vec1);
        std::vector<float> vec3(vec1);
        std::vector<float> vec6(vec1);

        comparison_floats.std_sort_assessment.append(assess_sort_implementation([](std::vector<float> & v) {return std::sort(v.begin(), v.end());}, vec1));
        comparison_floats.avx2_quicksort_assessment.append(assess_sort_implementation([](std::vector<float> & v){return quickfloat::qs_float(v);}, vec2));
        comparison_floats.dual_pivot_quicksort_assessment.append(assess_sort_implementation([](std::vector<float> & v){return dualPivot::sort(v);}, vec3));
        comparison_floats.vector_sort_assessment.append(assess_sort_implementation([](std::vector<float> & v){return vector_sort::sort(v);}, vec6));

#if ENABLE_THOROUGH
        for (int i = 0; i < num_elements; ++i)
        {
            assert (vec6.at(i) == vec1.at(i));
        }
#endif
    }
#endif

#if TEST_INTS
    algorithm_comparison comparison_ints = {
        {true, 0},
        {true, 0},
        {true, 0},
        {true, 0},
        {true, 0},
        {true, 0}
    };
    for (int i = 0; i < test_iterations; ++i)
    {
        std::vector<int> vec1(num_elements);
        std::generate(begin(vec1), end(vec1), int_generator);

        std::vector<int> vec2(vec1);
        std::vector<int> vec3(vec1);
        std::vector<int> vec6(vec1);

        comparison_ints.std_sort_assessment.append(assess_sort_implementation([](std::vector<int> & v) {return std::sort(v.begin(), v.end());}, vec1));
        comparison_ints.avx2_quicksort_assessment.append(assess_sort_implementation([](std::vector<int> & v){return quickint::qs_int(v);}, vec2));
        comparison_ints.dual_pivot_quicksort_assessment.append(assess_sort_implementation([](std::vector<int> & v){return dualPivot::sort(v);}, vec3));
        comparison_ints.vector_sort_assessment.append(assess_sort_implementation([](std::vector<int> & v){return vector_sort::sort(v);}, vec6));

#if ENABLE_THOROUGH
        for (int i = 0; i < num_elements; ++i)
        {
            assert (vec6.at(i) == vec1.at(i));
        }
#endif
    }
#endif

#if TEST_DOUBLES
    double const doubles_average_time_per_std_sort             = double(comparison_doubles.std_sort_assessment.microseconds_duration)             / double(test_iterations);
    double const doubles_average_time_per_avx2_quicksort       = double(comparison_doubles.avx2_quicksort_assessment.microseconds_duration)       / double(test_iterations);
    double const doubles_average_time_per_modified_avx2_quicksort = double(comparison_doubles.modified_avx2_quicksort_assessment.microseconds_duration)       / double(test_iterations);
    double const doubles_average_time_per_inplace_avx2_quicksort = double(comparison_doubles.inplace_avx2_quicksort_assessment.microseconds_duration)       / double(test_iterations);
    double const doubles_average_time_per_dual_pivot_quicksort = double(comparison_doubles.dual_pivot_quicksort_assessment.microseconds_duration) / double(test_iterations);
    double const doubles_average_time_per_vector_sort = double(comparison_doubles.vector_sort_assessment.microseconds_duration) / double(test_iterations);

    double const doubles_avx2_quicksort_speed_relative_to_std_sort       = double(comparison_doubles.std_sort_assessment.microseconds_duration) / double(comparison_doubles.avx2_quicksort_assessment.microseconds_duration);
    double const doubles_modified_avx2_quicksort_speed_relative_to_std_sort       = double(comparison_doubles.std_sort_assessment.microseconds_duration) / double(comparison_doubles.modified_avx2_quicksort_assessment.microseconds_duration);
    double const doubles_inplace_avx2_quicksort_speed_relative_to_std_sort       = double(comparison_doubles.std_sort_assessment.microseconds_duration) / double(comparison_doubles.inplace_avx2_quicksort_assessment.microseconds_duration);
    double const doubles_dual_pivot_quicksort_speed_relative_to_std_sort = double(comparison_doubles.std_sort_assessment.microseconds_duration) / double(comparison_doubles.dual_pivot_quicksort_assessment.microseconds_duration);
    double const doubles_vector_sort_speed_relative_to_std_sort = double(comparison_doubles.std_sort_assessment.microseconds_duration) / double(comparison_doubles.vector_sort_assessment.microseconds_duration);
#endif

#if TEST_FLOATS
    double const floats_average_time_per_std_sort             = double(comparison_floats.std_sort_assessment.microseconds_duration)             / double(test_iterations);
    double const floats_average_time_per_avx2_quicksort       = double(comparison_floats.avx2_quicksort_assessment.microseconds_duration)       / double(test_iterations);
    double const floats_average_time_per_dual_pivot_quicksort = double(comparison_floats.dual_pivot_quicksort_assessment.microseconds_duration) / double(test_iterations);
    double const floats_average_time_per_vector_sort = double(comparison_floats.vector_sort_assessment.microseconds_duration) / double(test_iterations);

    double const floats_avx2_quicksort_speed_relative_to_std_sort       = double(comparison_floats.std_sort_assessment.microseconds_duration) / double(comparison_floats.avx2_quicksort_assessment.microseconds_duration);
    double const floats_dual_pivot_quicksort_speed_relative_to_std_sort = double(comparison_floats.std_sort_assessment.microseconds_duration) / double(comparison_floats.dual_pivot_quicksort_assessment.microseconds_duration);
    double const floats_vector_sort_speed_relative_to_std_sort = double(comparison_floats.std_sort_assessment.microseconds_duration) / double(comparison_floats.vector_sort_assessment.microseconds_duration);
#endif

#if TEST_INTS
    double const ints_average_time_per_std_sort             = double(comparison_ints.std_sort_assessment.microseconds_duration)             / double(test_iterations);
    double const ints_average_time_per_avx2_quicksort       = double(comparison_ints.avx2_quicksort_assessment.microseconds_duration)       / double(test_iterations);
    double const ints_average_time_per_dual_pivot_quicksort = double(comparison_ints.dual_pivot_quicksort_assessment.microseconds_duration) / double(test_iterations);
    double const ints_average_time_per_vector_sort = double(comparison_ints.vector_sort_assessment.microseconds_duration) / double(test_iterations);

    double const ints_avx2_quicksort_speed_relative_to_std_sort       = double(comparison_ints.std_sort_assessment.microseconds_duration) / double(comparison_ints.avx2_quicksort_assessment.microseconds_duration);
    double const ints_dual_pivot_quicksort_speed_relative_to_std_sort = double(comparison_ints.std_sort_assessment.microseconds_duration) / double(comparison_ints.dual_pivot_quicksort_assessment.microseconds_duration);
    double const ints_vector_sort_speed_relative_to_std_sort = double(comparison_ints.std_sort_assessment.microseconds_duration) / double(comparison_ints.vector_sort_assessment.microseconds_duration);
#endif

    std::cout << "Test Summary" << std::endl;

#if TEST_DOUBLES
    std::cout << std::endl;
    std::cout << "Element type               : double" << std::endl;
    std::cout << "Number of elements         : " << num_elements << std::endl;
    std::cout << "Number of test iterations  : " << test_iterations << std::endl;
    std::cout << "Correctness" << std::endl;
    std::cout << "    std::sort                          : " << (comparison_doubles.std_sort_assessment.correct             ? "correct" : "incorrect") << std::endl;
    std::cout << "    quickdouble::qs_double             : " << (comparison_doubles.avx2_quicksort_assessment.correct       ? "correct" : "incorrect") << std::endl;
    std::cout << "    modified_quickdouble::qs_double    : " << (comparison_doubles.modified_avx2_quicksort_assessment.correct       ? "correct" : "incorrect") << std::endl;
//    std::cout << "    inplace_quickdouble::qs_double : " << (comparison_doubles.inplace_avx2_quicksort_assessment.correct       ? "correct" : "incorrect") << std::endl;
    std::cout << "    dualPivot::sort                    : " << (comparison_doubles.dual_pivot_quicksort_assessment.correct ? "correct" : "incorrect") << std::endl;
    std::cout << "    vector_sort : " << (comparison_doubles.vector_sort_assessment.correct ? "correct" : "incorrect") << std::endl;
    std::cout << "Average time taken per test (smaller is better)" << std::endl;
    std::cout << "    std::sort                          : " << doubles_average_time_per_std_sort             << "ms" << std::endl;
    std::cout << "    quickdouble::qs_double             : " << doubles_average_time_per_avx2_quicksort       << "ms" << std::endl;
    std::cout << "    modified_quickdouble::qs_double    : " << doubles_average_time_per_modified_avx2_quicksort       << "ms" << std::endl;
//    std::cout << "    inplace_quickdouble::qs_double : " << doubles_average_time_per_inplace_avx2_quicksort       << "ms" << std::endl;
    std::cout << "    dualPivot::sort                    : " << doubles_average_time_per_dual_pivot_quicksort << "ms" << std::endl;
    std::cout << "    vector_sort : " << doubles_average_time_per_vector_sort << "ms" << std::endl;
    std::cout << "Speed relative to std::sort (larger is better)" << std::endl;
    std::cout << "    std::sort                          : " << 1.0 << std::endl;
    std::cout << "    quickdouble::qs_double             : " << doubles_avx2_quicksort_speed_relative_to_std_sort       << std::endl;
    std::cout << "    modified_quickdouble::qs_double    : " << doubles_modified_avx2_quicksort_speed_relative_to_std_sort       << std::endl;
//    std::cout << "    inplace_quickdouble::qs_double : " << doubles_inplace_avx2_quicksort_speed_relative_to_std_sort       << std::endl;
    std::cout << "    dualPivot::sort                    : " << doubles_dual_pivot_quicksort_speed_relative_to_std_sort << std::endl;
    std::cout << "    vector_sort : " << doubles_vector_sort_speed_relative_to_std_sort << std::endl;
#endif

#if TEST_FLOATS
    std::cout << std::endl;
    std::cout << "Element type               : float" << std::endl;
    std::cout << "Number of elements         : " << num_elements << std::endl;
    std::cout << "Number of test iterations  : " << test_iterations << std::endl;
    std::cout << "Correctness" << std::endl;
    std::cout << "    std::sort                          : " << (comparison_floats.std_sort_assessment.correct             ? "correct" : "incorrect") << std::endl;
    std::cout << "    quickfloat::qs_float               : " << (comparison_floats.avx2_quicksort_assessment.correct       ? "correct" : "incorrect") << std::endl;
    std::cout << "    dualPivot::sort                    : " << (comparison_floats.dual_pivot_quicksort_assessment.correct ? "correct" : "incorrect") << std::endl;
    std::cout << "    vector_sort : " << (comparison_floats.vector_sort_assessment.correct ? "correct" : "incorrect") << std::endl;
    std::cout << "Average time taken per test (smaller is better)" << std::endl;
    std::cout << "    std::sort                          : " << floats_average_time_per_std_sort             << "ms" << std::endl;
    std::cout << "    quickfloat::qs_float               : " << floats_average_time_per_avx2_quicksort       << "ms" << std::endl;
    std::cout << "    dualPivot::sort                    : " << floats_average_time_per_dual_pivot_quicksort << "ms" << std::endl;
    std::cout << "    vector_sort : " << floats_average_time_per_vector_sort << "ms" << std::endl;
    std::cout << "Speed relative to std::sort (larger is better)" << std::endl;
    std::cout << "    std::sort                          : " << 1.0 << std::endl;
    std::cout << "    quickfloat::qs_float               : " << floats_avx2_quicksort_speed_relative_to_std_sort       << std::endl;
    std::cout << "    dualPivot::sort                    : " << floats_dual_pivot_quicksort_speed_relative_to_std_sort << std::endl;
    std::cout << "    vector_sort : " << floats_vector_sort_speed_relative_to_std_sort << std::endl;
#endif

#if TEST_INTS
    std::cout << std::endl;
    std::cout << "Element type               : int" << std::endl;
    std::cout << "Number of elements         : " << num_elements << std::endl;
    std::cout << "Number of test iterations  : " << test_iterations << std::endl;
    std::cout << "Correctness" << std::endl;
    std::cout << "    std::sort                          : " << (comparison_ints.std_sort_assessment.correct             ? "correct" : "incorrect") << std::endl;
    std::cout << "    quickint::qs_int                   : " << (comparison_ints.avx2_quicksort_assessment.correct       ? "correct" : "incorrect") << std::endl;
    std::cout << "    dualPivot::sort                    : " << (comparison_ints.dual_pivot_quicksort_assessment.correct ? "correct" : "incorrect") << std::endl;
    std::cout << "    vector_sort : " << (comparison_ints.vector_sort_assessment.correct ? "correct" : "incorrect") << std::endl;
    std::cout << "Average time taken per test (smaller is better)" << std::endl;
    std::cout << "    std::sort                          : " << ints_average_time_per_std_sort             << "ms" << std::endl;
    std::cout << "    quickint::qs_int                   : " << ints_average_time_per_avx2_quicksort       << "ms" << std::endl;
    std::cout << "    dualPivot::sort                    : " << ints_average_time_per_dual_pivot_quicksort << "ms" << std::endl;
    std::cout << "    vector_sort : " << ints_average_time_per_vector_sort << "ms" << std::endl;
    std::cout << "Speed relative to std::sort (larger is better)" << std::endl;
    std::cout << "    std::sort                          : " << 1.0 << std::endl;
    std::cout << "    quickint::qs_int                   : " << ints_avx2_quicksort_speed_relative_to_std_sort       << std::endl;
    std::cout << "    dualPivot::sort                    : " << ints_dual_pivot_quicksort_speed_relative_to_std_sort << std::endl;
    std::cout << "    vector_sort : " << ints_vector_sort_speed_relative_to_std_sort << std::endl;
#endif

    return 0;
}
