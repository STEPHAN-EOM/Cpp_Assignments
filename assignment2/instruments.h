/**
 * @author: Chanho Eom
 * @file: instruments.h
 * @date: 28 Feb 2023
 * */

#ifndef INSTRUMENTS_H_VK2TICXL
#define INSTRUMENTS_H_VK2TICXL
#include <vector>
#include <iostream>

class Trade
{
public:

Trade() : cost {0}{
std::cout << "Trade (base class) Constructor (Default)\n";
}

Trade (const double cost) : cost {cost} {
std::cout << "Trade (base class) Constructor (overloaded)\n";
}

// Define copy and move constructors as default
Trade(const Trade& existing_object) = default;
Trade(Trade&& existing_object) = default;

virtual ~Trade (){
std::cout << "Trade (base class) Destructor\n";
}

// Define assignment operators
Trade& operator = (const Trade& existing_object) = delete;
Trade& operator = (Trade&& existing_object) = delete;


// Declare payoff as a pure virtual constant member function
virtual double payoff(double ST) const = 0;


// Friend function to access to private memver of the class
friend double portfolio_profit(const std::vector<Trade const *>& trades, double ST);

// member function to access the private member variagle
double get_cost() const{
return cost;}

private:
	const double cost;	///< Holds the premium, or cost paid to enter the trade
};


// inline function to access to the private member variable
inline double get_cost(const Trade& trade) {
return trade.get_cost();
}


/**
 * @brief Class to represent a forward trade
 */
class Forward : public Trade{
public:
Forward() = delete;

Forward(double fp) : forward_price {fp} {
	std::cout << "Constructor for Forward with forward price" << forward_price << std::endl;
}

~Forward() {
	std::cout << "Destroying for Forward with forward price" << forward_price << std::endl;
}

virtual double payoff(double ST) const override{
return ST - forward_price;
}

private:
const double forward_price;
};


/**
 * @brief Class to represent a Call Option
 */
class Call : public Trade{
public:
Call() = delete;

Call(double cost, double CK) : Trade {cost}, strike {CK} {
	std::cout << "Creating Call with strike " << strike << ". Premium paid "<< cost << std::endl;
}

~Call() {
	std::cout << "Destroying Call with strike " << strike << std::endl;
}

double payoff(double ST) const override{
if (ST - strike > 0){
return ST - strike;
} else {
return 0;
}}

private:
const double strike;
};


/**
 * @brief Class to represent a Put Option
 */
class Put : public Trade{
public:
Put() = delete;

Put(double cost, double pk) : Trade {cost}, strike {pk} {
	std::cout << "Creating Put with strike " << strike << ". Premium paid " << cost << std::endl;
}

~Put() {
	std::cout << "Destroying Put with strike " << strike << std::endl;
}

double payoff(double ST) const override{
if (strike - ST > 0){
return strike - ST;
} else {
return 0;
}}

private:
const double strike;
};


#endif /* end of include guard: INSTRUMENTS_H_VK2TICXL */
