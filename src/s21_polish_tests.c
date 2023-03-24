#include <check.h>

#include "s21_polish.h"

#define FAIL "FAIL"

START_TEST(funcWithoutBracket) {
  char *res;
  char *res2;
  char *res3;
  char *res4;
  char *res5;

  res = Parser("(-9+5)");
  res2 = Parser("(3%2)");
  res3 = Parser("(+5-2)");
  res4 = Parser("(2^2)");
  res5 = Parser("(1/2)");

  ck_assert_msg(strcmp(res, "-4.000000") == 0, FAIL);
  ck_assert_msg(strcmp(res2, "1.000000") == 0, FAIL);
  ck_assert_msg(strcmp(res3, "3.000000") == 0, FAIL);
  ck_assert_msg(strcmp(res4, "4.000000") == 0, FAIL);
  ck_assert_msg(strcmp(res5, "0.500000") == 0, FAIL);

  free(res);
  free(res2);
  free(res3);
  free(res4);
  free(res5);
}

START_TEST(funcWithBracket) {
  char *res;
  char *res2;
  char *res3;
  char *res4;
  char *res5;

  res = Parser("(-(-9)+(-5))");
  res2 = Parser("(-(5+5))");
  res3 = Parser("(-(5-5))");
  res4 = Parser("(-(5*2^2))");
  res5 = Parser("(-(1/2)*(-5))");

  ck_assert_msg(strcmp(res, "4.000000") == 0, FAIL);
  ck_assert_msg(strcmp(res2, "-10.000000") == 0, FAIL);
  ck_assert_msg(strcmp(res3, "0.000000") == 0, FAIL);
  ck_assert_msg(strcmp(res4, "-20.000000") == 0, FAIL);
  ck_assert_msg(strcmp(res5, "2.500000") == 0, FAIL);

  free(res);
  free(res2);
  free(res3);
  free(res4);
  free(res5);
}

START_TEST(trigFuncWithoutBracket) {
  char *res;
  char *res2;
  char *res3;
  char *res4;

  res = Parser("(cos(0))");
  res2 = Parser("(sin(0))");
  res3 = Parser("(tan(1))");
  res4 = Parser("(sqrt(4+ln(1)))");

  ck_assert_msg(strcmp(res, "1.000000") == 0, FAIL);
  ck_assert_msg(strcmp(res2, "0.000000") == 0, FAIL);
  ck_assert_msg(strcmp(res3, "1.557408") == 0, FAIL);
  ck_assert_msg(strcmp(res4, "2.000000") == 0, FAIL);

  free(res);
  free(res2);
  free(res3);
  free(res4);
}

START_TEST(trigFuncWithBracket) {
  char *res;
  char *res2;
  char *res3;
  char *res4;
  char *res5;
  char *res6;
  char *res7;

  res = Parser("(-(-acos(0)))");
  res2 = Parser("(-asin(0))");
  res3 = Parser("(+atan(1))");
  res4 = Parser("(sqrt(4))");
  res5 = Parser("(ln(10))");
  res6 = Parser("(log(10))");
  res7 = Parser("(-5.1+(cos(4+(sqrt(36)))))");

  ck_assert_msg(strcmp(res, "1.570796") == 0, FAIL);
  ck_assert_msg(strcmp(res2, "0.000000") == 0, FAIL);
  ck_assert_msg(strcmp(res3, "0.785398") == 0, FAIL);
  ck_assert_msg(strcmp(res4, "2.000000") == 0, FAIL);
  ck_assert_msg(strcmp(res5, "2.302585") == 0, FAIL);
  ck_assert_msg(strcmp(res6, "1.000000") == 0, FAIL);
  ck_assert_msg(strcmp(res7, "-5.939072") == 0, FAIL);

  free(res);
  free(res2);
  free(res3);
  free(res4);
  free(res5);
  free(res6);
  free(res7);
}

Suite *Suite_create(void) {
  Suite *s21_SmartCalc = suite_create("s21_SmartCalc");
  TCase *tcase_test = tcase_create("test");

  tcase_add_test(tcase_test, funcWithoutBracket);
  tcase_add_test(tcase_test, funcWithBracket);
  tcase_add_test(tcase_test, trigFuncWithoutBracket);
  tcase_add_test(tcase_test, trigFuncWithBracket);

  suite_add_tcase(s21_SmartCalc, tcase_test);

  return s21_SmartCalc;
}

int main(void) {
  Suite *suite = Suite_create();
  SRunner *suite_runner = srunner_create(suite);

  srunner_run_all(suite_runner, CK_NORMAL);

  int failed_count = srunner_ntests_failed(suite_runner);

  srunner_free(suite_runner);

  return (failed_count != 0) ? EXIT_FAILURE : EXIT_SUCCESS;
}
