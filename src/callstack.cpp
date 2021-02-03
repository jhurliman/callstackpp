#include <memory>

#include "callstackpp.hpp"

namespace callstackpp {

static std::unique_ptr<backward::SignalHandling> shptr;

void AddCallstackSignalHandler() { shptr = std::make_unique<backward::SignalHandling>(); }

void RemoveCallstackSignalHandler() { shptr.reset(); }

void PrintCurrentCallstack(FILE* fp, size_t depth) {
  backward::Printer printer;

  backward::StackTrace st;
  st.load_here(depth + 1);
  st.skip_n_firsts(1);

  printer.address = true;
  printer.print(st, fp);
}

void PrintCurrentCallstack(std::ostream& os, size_t depth) {
  backward::Printer printer;

  backward::StackTrace st;
  st.load_here(depth + 1);
  st.skip_n_firsts(1);

  printer.address = true;
  printer.print(st, os);
}

}  // namespace callstackpp
