#ifndef SON8_CAPACITY_EXPONENT_HXX
#define SON8_CAPACITY_EXPONENT_HXX

#include <cassert>
#include <cstddef>
#include <limits>
#include <optional>
#include <type_traits>
#include <utility>

namespace son8::capacity {
    // Exponent class template
    template<
        typename T, // unsigned integral types only
        typename = std::enable_if_t< std::is_integral_v< T > && std::is_unsigned_v< T > && sizeof(T) <= sizeof(std::size_t) >
    >
    class Exponent {
        T size_{};
        [[nodiscard]] constexpr // TODO: add platform-specific solution?
        auto next_power2(std::size_t x) const noexcept -> std::size_t {
            if (x == 0) return 0;
            --x;
            x |= x >> 1;
            x |= x >> 2;
            x |= x >> 4;
            if constexpr (sizeof(T) > 1) x |= x >> 8;
            if constexpr (sizeof(T) > 2) x |= x >> 16;
            if constexpr (sizeof(T) > 4) x |= x >> 32;
            if (x == max_size()) return x;
            return x + 1;
        }
    public:
        using OptUpdateCapacity = std::optional< std::size_t >;
        constexpr
        Exponent() = default;
        constexpr
        Exponent(std::size_t n) { std::ignore = add(n); }
        [[nodiscard]] constexpr
        OptUpdateCapacity add(std::size_t n) {
            assert(static_cast< T >(size_ + n) > size_);
            auto old = capacity();
            size_ += n;
            auto cap = capacity();
            return cap > old ? cap : OptUpdateCapacity{};
        }
        [[nodiscard]] constexpr
        OptUpdateCapacity sub(std::size_t n) {
            assert(static_cast< T >(size_ - n) < size_);
            auto old = capacity();
            size_ -= n;
            auto cap = capacity();
            return cap < old ? cap : OptUpdateCapacity{};
        }
        [[nodiscard]] // assert on n == size (logic error?)
        OptUpdateCapacity assign(std::size_t n) {
            if (n > size_) return add(n - size_);
            else return sub(size_ - n);
        }
        [[nodiscard]] constexpr
        auto capacity() const noexcept -> std::size_t { return next_power2(size_); }
        [[nodiscard]] constexpr
        auto size() const noexcept -> std::size_t { return size_; }
        [[nodiscard]] constexpr
        auto last() const noexcept -> std::size_t { assert(size_ != 0); return size_ - 1; }
        [[nodiscard]] constexpr
        static auto max_size() noexcept -> std::size_t { return std::numeric_limits< T >::max(); }
    }; // class Exponent

} // namespace son8::capacity

#endif//SON8_CAPACITY_EXPONENT_HXX

// Ⓒ 2025 Oleg'Ease'Kharchuk ᦒ
