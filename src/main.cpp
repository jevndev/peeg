#include "peeg.hpp"

using namespace peeg;

static constexpr NonTerminal E{};
static constexpr NonTerminal T{};
static constexpr NonTerminal F{};

static constexpr Parser parser( //
    E <<= _{E, "+"_n, T} | T,   //
    T <<= _{T, "*"_n, F} | F,   //
    F <<= _{E} | EOF            //
);

int main(int argc, char const *argv[]) {
  using namespace std::string_view_literals;

  parser.parse(""sv);
  return 0;
}
