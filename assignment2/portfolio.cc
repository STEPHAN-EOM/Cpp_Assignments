/**
 * @file: portfolio.cc
 * @author: Chanho Eom
 * @date: 28 Feb 2023
 * */

#include <iostream>
#include <vector>

#include "portfolio.h"
#include "instruments.h"

/**
 * @function: compute portfolio payoff
 * @input: vector of "Trade", ST
 * @output: portfolio payoff for the given underlying asset price ST
 * */
double portfolio_payoff(const std::vector<Trade const*>& trades, double ST){
double payoff = 0;

for (auto &trade : trades) {
payoff += trade->payoff(ST);
}

return payoff;
}

/**
 * @function: compute portfolio profit
 * @input: vector of "Trade", ST
 * @output: portfolio profit for the given underlying asset price ST
 * */
double portfolio_profit(const std::vector<Trade const *>& trades, double ST){
double cost = 0;
double payoff = 0;

for (auto &trade : trades) {
cost += trade->cost;
payoff += trade->payoff(ST);
}

return payoff - cost;
}

