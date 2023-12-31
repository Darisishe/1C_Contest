#include "metric/metric.h"
#include <gtest/gtest.h>
#include <directories_comparator.h>
#include <metric/levenshtein.h>
#include <metric/LCS.h>

static void equal_files_test(const IStringMetric& metric) {
  DirectoriesComparator comparator("../testing_directories/test_dir1", "../testing_directories/test_dir2", 0, metric);
  auto result = comparator.calculateSimilarities();
  ASSERT_EQ(result.similar[0].to_string(), "../testing_directories/test_dir1/aaa - ../testing_directories/test_dir2/bbb");
}

TEST(ComparatorTestSuite, EqualFilesTestLevenshtein) {
  LevenshteinMetric metric;
  equal_files_test(metric);
}

TEST(ComparatorTestSuite, EqualFilesTestLCS) {
  LCSMetric metric;
  equal_files_test(metric);
}

static void unique_files_test(const IStringMetric& metric) {
  DirectoriesComparator comparator("../testing_directories/test_dir3", "../testing_directories/test_dir4", 20, metric);
  auto result = comparator.calculateSimilarities();

  // similarity of files should be less then 20%
  ASSERT_EQ(result.unique_in_dir1.size(), 1);
  ASSERT_EQ(result.unique_in_dir2.size(), 1);
  ASSERT_EQ(result.unique_in_dir1[0], "../testing_directories/test_dir3/ccc");
  ASSERT_EQ(result.unique_in_dir2[0], "../testing_directories/test_dir4/ccc");
}

TEST(ComparatorTestSuite, UniqueFilesTestLevenshtein) {
  LevenshteinMetric metric;
  unique_files_test(metric);
}

TEST(ComparatorTestSuite, UniqueFilesTestLCS) {
  LCSMetric metric;
  unique_files_test(metric);
}

