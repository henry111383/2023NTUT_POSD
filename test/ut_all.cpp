#include <gtest/gtest.h>
#include "ut_node.h"
#include "ut_file.h"
#include "ut_folder.h"
#include "ut_null_iterator.h"
#include "ut_iterator.h"
#include "ut_dfs_iterator.h"

// #include "ut_file.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
