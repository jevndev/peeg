#include <cstddef>
#include <initializer_list>
#include <type_traits>

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

class Parser {
public:
  constexpr Parser(
      const std::initializer_list<Production> &productions) noexcept {}
};

static constexpr NonTerminal E{};
static constexpr NonTerminal T{};
static constexpr NonTerminal F{};

static constexpr Terminal s{};
static constexpr Terminal g{};

static constexpr Parser parser{
    E <<= _{E, s} | _{F}, //
    F <<= _{g}            //
};

int main(int argc, char const *argv[]) { return 0; }
