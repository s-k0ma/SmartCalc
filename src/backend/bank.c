#include "bank.h"

#include <time.h>

/**
 * @file credit.c
 * @brief functions for calculate credit percents
 */

/**
 * Calculate monthly payment, total payment and overpayment for annuitial credit
 *
 * @param total_sum sum of credit
 * @param term in month
 * @param rate rate
 * @param monthly result of mmonthly payment
 * @param overpayment result of overpayment
 * @param total result of total payment
 *
 * @return 1: OK
 * @return 0: error
 */
void annuityCredit(double total_sum, int month, double rate, double *monthly,
                   double *overpayment, double *total) {
  *monthly = round(total_sum * (rate / 1200) /
                   (1 - pow(1 + rate / 1200, -month)) * 100) /
             100;
  *total = *monthly * month;
  *overpayment = *total - total_sum;
}

/**
 * Рассчитывает дифференцированный платеж по кредиту
 *
 * @param credit сумма основного займа
 * @param rate процентная ставка
 * @param period срок кредита
 *
 * @return структуру для записи в таблицу
 */
DiffNode *differentialPayment(double credit, double rate, int period) {
  DiffNode *result = (DiffNode *)malloc(period * sizeof(DiffNode));
  double sd = credit / (double)period;
  ;
  double sp = 0;
  double dept = credit;

  for (int i = 0; i < period; i++) {
    sp = (dept * (rate / 100.0) * daysInMonth(i % 12 + 1)) / daysInYear();

    result[i].mainPay = sd;
    result[i].persentPay = sp;
    result[i].monthPay = sd + sp;
    dept -= sd;
    result[i].dept = dept;
  }

  return result;
}

/**
 * Рассчитывает дифференцированный платеж по кредиту
 *
 * @param credit сумма основного займа
 * @param rate процентная ставка
 * @param period срок кредита
 *
 * @return структуру для записи в таблицу
 */
int daysInMonth(int step) {
  time_t currentTime;
  struct tm *localTime;
  time(&currentTime);

  localTime = localtime(&currentTime);
  int currentMonth = localTime->tm_mon + 1 + step;
  int currentYear = localTime->tm_year + 1900;

  int daysInMonth = 0;
  switch (currentMonth) {
    case 4:
    case 6:
    case 9:
    case 11:
      daysInMonth = 30;
      break;
    case 2:
      daysInMonth = (currentYear % 4 == 0 &&
                     (currentYear % 100 != 0 || currentYear % 400 == 0))
                        ? 29
                        : 28;
      break;
    default:
      daysInMonth = 31;
      break;
  }
  return daysInMonth;
}

/**
 * Возвращает количество дней в году
 *
 * @param step  следующий год
 *
 * @return Возвращает количество дней в году
 */
int daysInYear() {
  time_t currentTime;
  struct tm *localTime;
  time(&currentTime);

  localTime = localtime(&currentTime);
  int currentYear = localTime->tm_year + 1900;

  return (currentYear % 4 == 0 &&
          (currentYear % 100 != 0 || currentYear % 400 == 0))
             ? 366
             : 365;
}

void standartDeposit(double rateVal, int periodVal, int capital,
                     DebetNode **debetNode) {
  double totalPercentCharged = 0;
  double totalPayment = 0;
  int totalDepositDays = 0;
  for (int i = 1; i <= periodVal; i++) {
    totalDepositDays += daysInMonth(i);
  }

  for (int i = 0; i < periodVal; i++) {
    (*debetNode)[i].percentCharged =
        (((*debetNode)[i].balance + (*debetNode)[i].balanceChange) *
         (rateVal / 12)) -
        (*debetNode)[i].balance;
    (*debetNode)[i].balance =
        i > 0 ? (*debetNode)[i - 1].balance + (*debetNode)[i].balanceChange
              : (*debetNode)[i].balance + (*debetNode)[i].balanceChange;
    (*debetNode)[i].payment =
        ((*debetNode)[i].balance * rateVal * (totalDepositDays / 365)) / 100;
    if (capital == 1) {
      (*debetNode)[i].balance += (*debetNode)[i].payment;
      (*debetNode)[i].payment = 0;
    }
    (*debetNode)[i].percentCharged =
        (((*debetNode)[i].balance * rateVal * (totalDepositDays / 365) / 100 /
          periodVal)) /
        (*debetNode)[i].balance * 100;
    totalPercentCharged += (*debetNode)[i].percentCharged;
    totalPayment += (*debetNode)[i].payment;
  }
  (*debetNode)[periodVal].payment = totalPayment;
  (*debetNode)[periodVal].balance =
      (*debetNode)[periodVal - 1].balance + totalPayment;
  (*debetNode)[periodVal].percentCharged = totalPercentCharged * 100;
}

/**
 * @brief calculate tax for current year
 *
 * @param sum total profit for year
 * @param rate rate of central bank
 *
 * @return total tax per current year
 */
double calculateTax(double *sum, double rate) {
  double border = 10000 * rate;
  double res = 0;
  if (*sum > border) {
    res = round((*sum - border) * 13) / 100;
  }
  *sum = 0;
  return res;
}