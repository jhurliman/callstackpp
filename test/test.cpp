#include <callstackpp.hpp>
#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

static bool Contains(const std::string_view haystack, const std::string_view needle) {
  return haystack.find(needle) != std::string::npos;
}

TEST_CASE("VERSION_STRING") { REQUIRE(CALLSTACKPP_VERSION_STRING == std::string("1.0.0")); }

TEST_CASE("StackPrintFormatting") {
  std::stringstream ss;
  callstackpp::PrintCurrentCallstack(ss);
  const std::string stack = ss.str();

  CAPTURE(stack);
  CHECK(Contains(stack, "TEST_CASE(\"StackPrintFormatting\") {"));
}

TEST_CASE("FileDescriptor") {
#ifdef __unix__
  FILE *fp = fopen("/dev/null", "w");
#elif defined(_WIN32) || defined(WIN32)
  FILE *fp = fopen("nul", "w");
#else
  FILE *fp = nullptr;
#endif
  callstackpp::PrintCurrentCallstack(fp);
  fclose(fp);
}

TEST_CASE("SignalHandler") {
  callstackpp::AddCallstackSignalHandler();
  raise(SIGUSR2);
  callstackpp::RemoveCallstackSignalHandler();
}
