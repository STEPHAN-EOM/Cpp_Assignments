/**
 * @file assignment1.cc
 * @author Chanho Eom
 * @date 14 February 2023
 */

#include <iostream> 			// Needed for I/O
#include <cmath> 			// Needed for maths functions
#include <iomanip> 			// Output formatting


constexpr double MYPI {4 * std::atan(1.0)};
//Use the below instead if not using g++ and you get errors with line above
//constexpr double MYPI = M_PI;

/**
 * @class Gaussian
 * @brief A class to represent a normal distribution
 *
 * This class stores the parameters for an object which 
 * represents a Gaussian distribution.
 */
class Gaussian
{
    public:
	// Default Constructor
	Gaussian (): mu(0.0), sigma(1.0) {
        std::cout << "Constructing default with mean " << std::setprecision(1) << std::showpoint << mu << ", stdev " << std::setprecision(2) << std::showpoint << sigma << std::endl;
    }	
	
	// Overload Constructor
    	Gaussian (double mean, double stdev): mu(mean), sigma(stdev){
        std::cout << "Constructing with mean " << std::setprecision(1) << mu << ", stdev " << std::setprecision(1) << sigma << std::endl; 
    } 

	// Accessor Function for a private mu
	// return: mu
	double get_mu() const{
        return(mu);
    };

    // Accessor Function for a private sigma
    // return: sigma
	double get_sigma() const{
        return(sigma);
    };

    // Normalised function
    // input: x
    // output: z = (x - mu) / sigma
	double normalised(double x) const{
        return((x - mu)/sigma);
    };

	// Write remaining member function definitions outside of class body
	Gaussian(const Gaussian& rhs); 						// Copy constructor
	Gaussian & operator=(const Gaussian &rhs); 				// Copy assignment operator
	double pdf(double x) const; 						// return pdf at x
	double cdf(double x, double left = -8, double step = 1e-3) const; 	// return cdf at x using numerical approx
	double cdf_erfc(double x) const; 					// return cdf at x using std::erfc
	void print_parameters() const; 						// Print distribution parameters

	// You don't need to modify from here to the end of the class definition.
	double cdf_poly(double x) const; 				// Code provided below for Hart approximation
	~Gaussian() { 							// Destructor
	    std::cout << "Destroying object with mu = " << mu << " stdev = " << sigma << '\n';
	}

    private:
	double mu; 							///< Holds mean of Gaussian
	double sigma; 							///< Holds standard deviation of Gaussian
};


// Non member function declarations.
// These are just another way to get same functionality.
// Will discuss later in lectures.
void print_parameters(const Gaussian & dist);
double pdf(const Gaussian & dist, double x);
double cdf(const Gaussian & dist, double x, double start = -8, double step = 1e-3);
double cdf_poly(const Gaussian & dist, const double x);
double cdf_erfc(const Gaussian & dist, const double x);

// Put member function defintions below here

// Copy constructor
Gaussian::Gaussian(const Gaussian& rhs){
    std::cout << "Copy Constructor" << std::endl;
    mu = rhs.mu;
    sigma = rhs.sigma;
}

// Copy assignment
Gaussian& Gaussian::operator=(const Gaussian &rhs){
    std::cout << "Copy Assignment" << "\n";
    if (this == &rhs){
        std::cout << "Self Copy" << "\n";
        return *this;
}

    // Check for some cases which are unexpected
    if (mu != rhs.mu || sigma != rhs.sigma){
        std::cout << "Because of inequality of data from rhs and lhs, data modification occours" << '\n';
	mu = rhs.mu;
	sigma = rhs.sigma;
}
return *this;
}

// Print the mu and standard deviation of the Gaussian distribution
void Gaussian::print_parameters() const{
    std::cout << "Normal distribution with mean " << std::setprecision(1) << mu << " and standard deviation " << std::setprecision(1) << sigma << std::endl;
}

// Gaussian PDF
// input: x
// output: probability value of the guassian distribution at x, Pr(t = x)
double Gaussian::pdf(double x) const{
    double pdf = (1 /(sigma * sqrt(2 * MYPI))) * exp((-0.5) * pow((x - mu)/sigma, 2.0));
    return pdf;
} 					

// Gaussian CDF via std::erfc
// input: x
// output: Pr(t <= x)
double Gaussian::cdf_erfc(double x) const{
    double z = (x - mu) / sigma;
    double cdf_erfc = 0.5 * erfc((-1) * z / sqrt(2));
    return cdf_erfc;
}

// Gaussian CDF via a numerical integration.
// input: x, left, step
// oupput: Pr(t <= x)
// Note: I use a left sum
double Gaussian::cdf(double x, double left, double step) const{
    int n = (x - left) / step;      // the number of steps
    double sum = 0;                 // partial sum
    double t, ft;                   // x variable, function value

    for (int i = 0; i < n; ++i){
        t = left + (step * i);      // t(n) = left + step*n
        ft = (1 /(sigma * sqrt(2 * MYPI))) * exp((-0.5) * pow((t - mu)/sigma, 2.0));
        sum = sum + (ft * step);    // Area of a rectangle
    }
    return sum;
} 


/**
 * @brief Function to return a polynomial approximation to the cumulative distribution function for the normal distribution
 *
 * This member function uses the Hart approximation for the error function to compute a polynomial approximation
 * to the CDF of the standard normal distribution.
 *
 * @param x
 *
 * @return $\Phi(x)$ 
 */
double Gaussian::cdf_poly(const double x) const{
    const double norm {normalised(x)};
    constexpr double boundary {7.07106781186547};

    constexpr double N0 {220.206867912376};
    constexpr double N1 {221.213596169931};
    constexpr double N2 {112.079291497871};
    constexpr double N3 {33.912866078383};
    constexpr double N4 {6.37396220353165};
    constexpr double N5 {0.700383064443688};
    constexpr double N6 {3.52624965998911e-02};

    constexpr double M0 {440.413735824752};
    constexpr double M1 {793.826512519948};
    constexpr double M2 {637.333633378831};
    constexpr double M3 {296.564248779674};
    constexpr double M4 {86.7807322029461};
    constexpr double M5 {16.064177579207};
    constexpr double M6 {1.75566716318264};
    constexpr double M7 {8.83883476483184e-02};

    const double z {std::fabs(norm)};
    double c {0.0};

    if(z<=37.0)
    {
	const double e {std::exp(-z*z/2.0)};
	if(z<boundary)
	{
	    const double n {(((((N6*z + N5)*z + N4)*z + N3)*z + N2)*z + N1)*z + N0};
	    const double d {((((((M7*z + M6)*z + M5)*z + M4)*z + M3)*z + M2)*z + M1)*z + M0};
	    c = e*n/d;
	}
	else
	{
	    const double f {z + 1.0/(z + 2.0/(z + 3.0/(z + 4.0/(z + 13.0/20.0))))};
	    c = e/(std::sqrt(2*MYPI)*f);
	}
    }
    return norm<=0.0 ? c : 1-c;
}

// Put Non-Member Functions (free functions) here

// Print parameter of the normal distribution, N(mu, sigma^2)
void print_parameters(const Gaussian & dist){
    double mu = dist.get_mu();          // since mu is private
    double sigma = dist.get_sigma();    // since sigma is private

    std::cout << "Normal distribution with mean " << std::setprecision(1) << mu << " and standard deviation " << std::setprecision(1) << sigma << std::endl;
}

// Gaussian pdf
// input: Gaussian &dist, x
// output: Probability value of N(mu, sigma^2) at x. Pr(t = x)
double pdf(const Gaussian & dist, double x){
    double mu = dist.get_mu();          // since mu is private
    double sigma = dist.get_sigma();    // since sigma is private

    double pdf = (1 /(sigma * sqrt(2 * MYPI))) * exp((-0.5) * pow((x - mu)/sigma, 2.0));
    return pdf;
}

// Gaussian CDF via an numerical ingetration
// input: Gaussian &dist, x, start, step
// // output: Pr(t <= x)
// I use the left sum
double cdf(const Gaussian & dist, double x, double start, double step){
    double mu = dist.get_mu();
    double sigma = dist.get_sigma();

    int n = (x - start) / step;         // the number of steps
    double sum = 0;                     // partial sum
    double t, ft;                       // x variable, function value

    for (int i = 1; i <= n; ++i){
        t = start + (step * i);         // t(n) = start + step * n
        ft = (1 /(sigma * sqrt(2 * MYPI))) * exp((-0.5) * pow((t - mu)/sigma, 2.0));
        sum = sum + (ft * step);        // area of the rectangle
    }

    return sum;
}

// Gaussian CDF via std::erfc function
// input: Gaussian &dist, x
// // output: Pr(t <= x)
double cdf_erfc(const Gaussian & dist, const double x){
	double mu = dist.get_mu();
	double sigma = dist.get_sigma();

	double z = (x - mu)/sigma;
	double cdf = 0.5 * erfc((-1) * z / sqrt(2));

	return cdf;
}

// Gaussian poly
// input: Gaussian &dist, x
// note: use a member function which is cdf_poly
double cdf_poly(const Gaussian & dist, const double x){
	double poly = dist.cdf_poly(x);
	
	return poly;
}

// Main function for 5614 Assigment 1
// Note that a lot of the code below is simply formatting output.
// If it is confusing, email me and I will provide the same without the formatting
// You shouldn't need to add anything here. Your final code should run with this as-is.

int main()
{
    Gaussian A;  			// Create object of class Gaussian via default constructor
    Gaussian B {1, 2}; 			// Create object of class Gaussian via overloaded constructor

    // Create a list. Is actually ok to use auto here
    auto list = {-3.0, -2.0, -1.0, -0.5, 0.0, 0.5, 1.0, 2.0, 3.0};

    // Calculate and print cumulative density function values for A for a number of input values.
    // Most of these lines are for formatting output. We will cover this later.
    std::cout << std::fixed << '\n';
    A.print_parameters();
    std::cout << std::setw(60) << std::setfill('-') << '\n' << std::setfill(' ');
    std::cout <<  "  x           Phi(x)             Method \n";
    for (auto  i : list) {
	std::cout << std::setw(4) <<  std::setprecision(1) <<  i << "\t" << std::setprecision(14) <<  A.cdf(i)       << "  \tNum. Int.\n"
	    << std::setw(4) <<  std::setprecision(1) <<  i << "\t" << std::setprecision(14) <<  A.cdf_erfc(i)  << "  \tUsing std::erfc.\n"
	    << std::setw(4) <<  std::setprecision(1) <<  i << "\t" << std::setprecision(14) <<  A.cdf_poly(i)  << "  \tHart approx.\n";
    }
    std::cout << std::setw(60) << std::setfill('-') << '\n' << std::setfill(' ');
    std::cout << "\n\n";


    // Calculate and print cumulative density function values for B for a number of input values.
    B.print_parameters();
    std::cout << std::setw(60) << std::setfill('-') << '\n' << std::setfill(' ');
    for (auto  i : list) {
	std::cout << std::setw(4) <<  std::setprecision(1) <<  i << "\t"<< std::setprecision(14) <<  B.cdf(i, -10.0, 1e-6) << "  \tNum. Int.\n"
	    << std::setw(4) <<  std::setprecision(1) <<  i << "\t" << std::setprecision(14) <<  B.cdf_erfc(i)  << "  \tUsing std::erfc.\n"
	    << std::setw(4) <<  std::setprecision(1) <<  i << "\t"<< std::setprecision(14) <<  B.cdf_poly(i)         << "  \tHart approx.\n";
    }
    std::cout << std::setw(60) << std::setfill('-') << '\n' << std::setfill(' ');
    std::cout << "\n";

	
    //
    // The non-member functions are used below here.
    //

    std::cout << "\nUsing free functions\n" << std::endl;
    Gaussian D {2,5}; 			// Create another object of class Gaussian
    print_parameters(D); 		// Print the parameters of D using non-member function
    Gaussian C {D}; 			// Should call copy constructor
    print_parameters(C); 		// Print the parameters of C using non-member function
    std::cout << "\n\n";

    A = B; 				// Should call copy assignment operator you wrote

    // Print parameters of A, followed by an example CDF calculation using the free functions.
    print_parameters(A);
    std::cout << std::setprecision(12) << "PDF of A at x=1 is " << pdf(A, 1.0) << '\n';
    std::cout << std::setprecision(12) << "Num. Int.:\tCDF of A at x=3 is " << cdf(A, 3.0) << '\n';
    std::cout << std::setprecision(12) << "std::erfc:\tCDF of A at x=3 is " << cdf_erfc(A, 3.0) << '\n';
    std::cout << std::setprecision(12) << "Hart Approx:\tCDF of A at x=3 is " << cdf_poly(A, 3.0) << '\n';

    std::cout << "\n\n" << std::setprecision(1);
    return 0;
}
