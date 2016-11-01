/* This program is meant to calculate the theoretical delta-v of a vessel
 * given the vessel's dry mass, propellant mass and engine exhaust velocity. */

#include<iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
#include<vector>
using std::vector;

//calculates the delta-v using an integral function with differential steps
double calc_delta_v(double _dry_mass, double _prop_mass, double _exh_vel);

int main()
{
	double dry_mass = 0;
	double prop_mass = 0;
	double exh_vel = 0;
	
	cout << "Wellcome to delta-v calculator\n\n";
	
	cout << "Enter the dry mass of your vessel: ";
	cin >> dry_mass;
	cout << "Enter the propellant mass of your vessel: ";
	cin >> prop_mass;
	cout << "Enter the exhaust velocity: ";
	cin >> exh_vel;
	
	double delta_v = calc_delta_v(dry_mass, prop_mass, exh_vel);
	cout << "*** RESULTS ***\n";
	cout << "isp: " << exh_vel / 9.80665d << endl;
	cout << "delta-v: " << delta_v << endl;
}

double calc_delta_v(double _dry_mass, double _prop_mass, double _exh_vel)
{
	double wet_mass = _dry_mass + _prop_mass;
	unsigned differential_steps = 1000000;
	double step_change = _prop_mass / differential_steps;
	
	//calculating the sum of momentary thrust values at differential steps
	double moment_thrust_sum = 0;
	for(unsigned i = 0; i < differential_steps; ++i) {
		moment_thrust_sum += ((1.0d / (_dry_mass + (step_change * i))) * _exh_vel);
	}
	
	double derived_delta_v = moment_thrust_sum * step_change;
	
	return derived_delta_v;
}
