#ifndef SFL_BENCHMARK_TABLE_HPP_INCLUDED
#define SFL_BENCHMARK_TABLE_HPP_INCLUDED

#include <iomanip> // fixed, left, setw
#include <vector>
#include <string>
#include <sstream> // ostringstream
#include <utility> // forward

namespace sfl
{

namespace benchmark
{

class table
{
private:

    std::string title_;

    std::vector<std::string> header_;

    std::vector<std::vector<std::string>> rows_;

private:

    template <typename T>
    std::string to_string(T&& value) const
    {
        std::ostringstream oss;
        oss << std::fixed;
        oss << std::forward<T>(value);
        return oss.str();
    }

public:

    template<typename... Args>
    void set_title(Args&&... args)
    {
        std::ostringstream oss;
        (oss << ... << std::forward<Args>(args));
        title_ = oss.str();
    }

    template <typename... Args>
    void set_header(Args&&...args)
    {
        header_.clear();
        (header_.emplace_back(to_string(std::forward<Args>(args))), ...);
    }

    template <typename... Args>
    void add_row(Args&&... args)
    {
        rows_.emplace_back(std::vector<std::string>{to_string(std::forward<Args>(args))...});
    }

    friend std::ostream& operator<<(std::ostream& os, const table& t)
    {
        const std::size_t num_columns = t.header_.size();

        std::vector<std::size_t> column_width(num_columns);

        // Calculate width of columns
        for (std::size_t i = 0; i < column_width.size(); ++i)
        {
            column_width[i] = 0;

            column_width[i] = std::max<std::size_t>
            (
                column_width[i],
                t.header_[i].size()
            );

            for (const auto& row : t.rows_)
            {
                column_width[i] = std::max<std::size_t>
                (
                    column_width[i],
                    row[i].size()
                );
            }
        }

        if (!t.title_.empty())
        {
            os << t.title_ << ":\n";
        }

        if (t.header_.empty())
        {
            return os;
        }

        // Print header
        os << "| ";
        for (std::size_t i = 0; i < num_columns; ++i)
        {
            os << std::left << std::setw(column_width[i]) << t.header_[i] << " | ";
        }
        os << "\n";

        // Print separator
        os << "| ";
        for (std::size_t i = 0; i < num_columns; ++i)
        {
            os << std::string(column_width[i], '-') << " | ";
        }
        os << "\n";

        // Print rows
        for (const auto& row : t.rows_)
        {
            os << "| ";
            for (std::size_t i = 0; i < num_columns; ++i)
            {
                os << std::left << std::setw(column_width[i]) << row[i] << " | ";
            }
            os << "\n";
        }

        return os;
    }
};

} // namespace benchmark

} // namespace sfl

#endif // SFL_BENCHMARK_TABLE_HPP_INCLUDED
