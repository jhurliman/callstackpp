#pragma once

#include "backward/backward.hpp"

namespace callstackpp {

void AddCallstackSignalHandler();

void RemoveCallstackSignalHandler();

void PrintCurrentCallstack(FILE* fp = stderr, size_t depth = 32);

void PrintCurrentCallstack(std::ostream& os, size_t depth = 32);

}  // namespace callstackpp
