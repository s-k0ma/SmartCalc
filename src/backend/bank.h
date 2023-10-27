#ifndef BACKEND_BANK_H
#define BACKEND_BANK_H

#include <math.h>

#include "types.h"

void annuityCredit(double total_sum, int month, double rate, double *monthly,
                   double *overpayment, double *total);
DiffNode *differentialPayment(double credit, double rate, int period);
int daysInYear();
int daysInMonth(int step);
void standartDeposit(double rateVal, int periodVal, int capital,
                     DebetNode **debetNode);
double calculateTax(double *sum, double rate);

#endif