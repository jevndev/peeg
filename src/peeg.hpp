#pragma once

#include <cstddef>
#include <initializer_list>
#include <type_traits>

#include <string_view>
#include <tuple>

namespace peeg {

struct Terminal;
struct NonTerminal;

template <typename T>
concept TerminalOrNonTerminal =
    std::is_same_v<T, Terminal> || std::is_same_v<T, NonTerminal>;

struct _ {
  constexpr _() noexcept {}

  template <typename... Args>
  constexpr _(Args... args) noexcept
    requires(TerminalOrNonTerminal<Args> && ...)
  {}

  constexpr _ operator|(const _ &other) const noexcept { return *this; }
};

struct Production {
  constexpr Production(const NonTerminal &lhs, const _ &rhs) {}
};

struct Terminal {
  constexpr _ operator|(TerminalOrNonTerminal auto next) { return {}; }
};

struct NonTerminal {
  constexpr Production operator<<=(const _ &rhs) const { return {*this, rhs}; }
};

template <std::size_t N> class Parser {
public:
  constexpr Parser(std::same_as<Production> auto &&...productions) noexcept
      : m_productions{productions...} {}

  void parse(std::string_view sv) const {}

private:
  std::array<Production, N> m_productions;
};

template <typename... Productions>
Parser(Productions &&...) -> Parser<sizeof...(Productions)>;

constexpr NonTerminal operator""_n(const char *s, const std::size_t i) {
  return {};
}

static constexpr auto EOF = Terminal{};

}; // namespace peeg
