#include "common.hpp"

#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

#include "sfl/segmented_devector.hpp"
#include "sfl/segmented_vector.hpp"

#include <deque>
#include <vector>

using namespace std::literals;

template <typename Vector>
void emplace_back(ankerl::nanobench::Bench& bench, int num_elements)
{
    const std::string title(name_of_type<Vector>());

    bench.warmup(10).batch(num_elements).unit("emplace_back").run
    (
        title,
        [&]
        {
            Vector vec;

            for (int i = 0; i < num_elements; ++i)
            {
                vec.emplace_back(i);
            }

            ankerl::nanobench::doNotOptimizeAway(vec.size());
        }
    );
}

int main()
{
    const int num_elements = 10'000'000;

    ankerl::nanobench::Bench bench;
    bench.title("emplace_back");
    bench.performanceCounters(false);
    bench.epochs(100);

    emplace_back<std::deque<int>>(bench, num_elements);
    emplace_back<sfl::segmented_devector<int, 1024>>(bench, num_elements);
    emplace_back<sfl::segmented_vector<int, 1024>>(bench, num_elements);
    emplace_back<std::vector<int>>(bench, num_elements);
}
