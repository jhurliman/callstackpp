#include "callstackpp.hpp"

namespace callstackpp {

static backward::SignalHandling* shptr = nullptr;

void AddCallstackSignalHandler() {
  shptr = new backward::SignalHandling();
}

void RemoveCallstackSignalHandler() {
  if (shptr != nullptr) {
    delete shptr;
    shptr = nullptr;
  }
}

void PrintCurrentCallstack(FILE *fp, size_t depth) {
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

} // namespace callstackpp
