#include "common.hpp"

#define ANKERL_NANOBENCH_IMPLEMENT
#include "nanobench.h"

#include "sfl/segmented_devector.hpp"
#include "sfl/segmented_vector.hpp"

#include <deque>
#include <vector>

template <typename Vector>
void emplace_front(ankerl::nanobench::Bench& bench, int num_elements)
{
    const std::string title(name_of_type<Vector>());

    bench.warmup(10).batch(num_elements).unit("emplace_front").run
    (
        title,
        [&]
        {
            Vector vec;

            for (int i = 0; i < num_elements; ++i)
            {
                vec.emplace_front(i);
            }

            ankerl::nanobench::doNotOptimizeAway(vec.size());
        }
    );
}

int main()
{
    const int num_elements = 10'000'000;

    ankerl::nanobench::Bench bench;
    bench.title("emplace_front (" + std::to_string(num_elements) + " elements)");
    bench.performanceCounters(false);
    bench.epochs(100);

    emplace_front<std::deque<int>>(bench, num_elements);
    emplace_front<sfl::segmented_devector<int, 1024>>(bench, num_elements);
}
