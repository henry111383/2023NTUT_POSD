#include <gtest/gtest.h>

#include "json_test.h"
#include "beautify_visitor_test.h"
#include "parser_test.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
