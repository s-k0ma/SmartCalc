#include <check.h>

#include "../backend/bank.h"
#include "../backend/calc.h"

START_TEST(test_plus) {
  char str[256] = "1.25+3.45";
  double res = calculation(str);
  ck_assert_int_eq(4.700000, res);
}
END_TEST

START_TEST(test_minus) {
  char str[256] = "3.45-1.25";
  double res = calculation(str);
  ck_assert_int_eq(2.200000, res);
}
END_TEST

START_TEST(test_mul) {
  char str[256] = "1.25*3.45";
  double res = calculation(str);
  ck_assert_int_eq(4.312500, res);
}
END_TEST

START_TEST(test_div) {
  char str[256] = "3.45/1.25";
  double res = calculation(str);
  ck_assert_int_eq(2.760000, res);
}
END_TEST

START_TEST(test_sin) {
  char str[256] = "sin(1)";
  double res = calculation(str);
  ck_assert_int_eq(0.8414710, res);
}
END_TEST

START_TEST(test_log) {
  char str[256] = "log(100)";
  double res = calculation(str);
  ck_assert_int_eq(2.0000000, res);
}
END_TEST

START_TEST(test_tan) {
  char str[256] = "-tan(3)";
  double res = calculation(str);
  ck_assert_int_eq(0.1425465, res);
}
END_TEST

START_TEST(test_compl1) {
  char str[256] = "sin(4) ^ 2 + cos(4) ^ 2";
  double res = calculation(str);
  ck_assert_int_eq(1.00000, res);
}
END_TEST

START_TEST(test_compl2) {
  char str[] = "asin(-1) + acos(1) * atan(3) - sqrt(log(1000))";
  double res = calculation(str);
  ck_assert_int_eq(-3.30285, res);
}
END_TEST

START_TEST(test_compl3) {
  char str[] = "ln(55mod32)";
  double res = calculation(str);
  ck_assert_int_eq(3.13549, res);
}
END_TEST

START_TEST(test_err) {
  char str[] = ")+5";
  double res = calculation(str);
  ck_assert(isnan(res));
}
END_TEST

START_TEST(graph) {
  Axises* praxis = drawingGraph("sin(X)", 10, -10);
  for (double i = 0; i < 2; i++) {
    ck_assert_int_eq(sin(-10), praxis->axisY[0]);
  }
  free(praxis);
}

START_TEST(credit) {
  double total = 0;
  double overpayment = 0;
  double month = 0;

  annuityCredit(100000, 12, 30, &month, &overpayment, &total);
  ck_assert_int_eq(9748.71, month);
  ck_assert_int_eq(16984.52, overpayment);
  ck_assert_int_eq(116984.52, total);
}

START_TEST(differCredit) {
  DiffNode* node = differentialPayment(100000, 30, 6);

  ck_assert_int_eq(16666.67, node[0].mainPay);
  ck_assert_int_eq(2465, node[0].persentPay);
  ck_assert_int_eq(19132, node[0].monthPay);
  ck_assert_int_eq(83333.33, node[0].dept);
  free(node);
}

START_TEST(deposit) {
  DebetNode* debetNode = (DebetNode*)calloc((13), sizeof(DebetNode));
  debetNode[0].balance = 100000;
  standartDeposit(40, 12, 0, &debetNode);

  ck_assert_int_eq(480000, debetNode[12].payment);
  ck_assert_int_eq(580000, debetNode[12].balance);
  ck_assert_int_eq(58500, calculateTax(&debetNode[12].balance, 13));

  free(debetNode);
}

START_TEST(depositCap) {
  DebetNode* debetNode = (DebetNode*)calloc((13), sizeof(DebetNode));
  debetNode[0].balance = 100000;
  standartDeposit(40, 12, 1, &debetNode);

  ck_assert_int_eq(0, debetNode[12].payment);
  ck_assert_int_eq(5669391, debetNode[12].balance);
  ck_assert_int_eq(720120, calculateTax(&debetNode[12].balance, 13));

  free(debetNode);
}

int main(void) {
  Suite* s1 = suite_create("\033[97m\033[106mSMART CALC\033[0m");
  TCase* tc1_1 = tcase_create("calculator");
  SRunner* sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, test_plus);
  tcase_add_test(tc1_1, test_minus);
  tcase_add_test(tc1_1, test_mul);
  tcase_add_test(tc1_1, test_div);
  tcase_add_test(tc1_1, test_sin);
  tcase_add_test(tc1_1, test_log);
  tcase_add_test(tc1_1, test_tan);
  tcase_add_test(tc1_1, test_compl1);
  tcase_add_test(tc1_1, test_compl2);
  tcase_add_test(tc1_1, test_compl3);
  tcase_add_test(tc1_1, test_err);
  tcase_add_test(tc1_1, graph);
  tcase_add_test(tc1_1, credit);
  tcase_add_test(tc1_1, differCredit);
  tcase_add_test(tc1_1, deposit);
  tcase_add_test(tc1_1, depositCap);

  srunner_run_all(sr, CK_ENV);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return (0);
}
