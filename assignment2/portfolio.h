/**
 * @file: portfolio.h
 * @author: Chanho Eom
 * @date: 28-Feb-2023
 * */

#ifndef STATS_H_5IWZAED1
#define STATS_H_5IWZAED1

#include <iostream>
#include <vector>

#include "portfolio.h"
#include "instruments.h"

double portfolio_payoff(const std::vector<Trade const *>& trades, const double ST);
double portfolio_profit(const std::vector<Trade const *>& trades, const double ST);

#endif /* end of include guard: STATS_H_5IWZAED1 */
