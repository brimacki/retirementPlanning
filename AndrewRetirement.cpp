#include<iostream>
#include<vector>
#include<cmath>

//There are three inputs Andrew can control rigorously: years employed, years retired, plan choice. He can also choose his investments, but that is not as "easy" or "obvious" of a choice.

//To do list:
//	1. Calculate value of these numbers by retirement (i.e. export these plans to an IRA.
//	2. Calculate a per year amount assuming 25 years of retirement.
//Working from 26-65; retired 25 years.

using namespace std;

int main(){
	//Find out how many years. We are assuming you work exactly an integer number of years.
	cout << "How many years will you work (enter an integer)?" << endl;
	int years;
	cin >> years;

	//Set salary.
	vector<int> salary(years);
	for(int i = 0; i < years; ++i){
		if(i < 2){
			salary.at(i) = 57276;
		}
		if(i >= 2 && i < 5){
			salary.at(i) = 75000;
		}
		if(i >= 5){
			salary.at(i) = 100000;
		}
		cout << "Your salary during year " << i + 1 << " is $" << salary.at(i) << endl;
	}

	//Determine defined benefit, option 1.
	vector<double> compounds(years);
	for(int i = 0; i < years; ++i){
		compounds.at(i) = years - i - 0.5;	//Compound at mid-year as an averaging.
		cout << "The number of compounding periods for year " << i + 1 << " is: " << compounds.at(i) << endl;
	}

	double interest = 0.04;

	vector<double> compoundMultiplier(years);
	for(int i = 0; i < years; ++i){
		compoundMultiplier.at(i) = pow(interest + 1, compounds.at(i));
		cout << "Compound multiplier for year " << i + 1 << " is: " << compoundMultiplier.at(i) << endl;
	}

	double employeeContribution = 0.08;
	double employerContribution = employeeContribution;

	vector<double> definedByYear(years);
	for(int i = 0; i < years; ++i){
		definedByYear.at(i) = (employeeContribution + employerContribution)*salary.at(i)*compoundMultiplier.at(i);
		cout << "The contribution to retirement in year " << i + 1 << " will be $" << definedByYear.at(i)/compoundMultiplier.at(i) << " and will be worth $" << definedByYear.at(i) << " at the end of employment." << endl;
	}

	double totalRetirement = 0.0;
	for(int i = 0; i < years; ++i){
		totalRetirement += definedByYear.at(i);
	}

	cout << "This is your total retirement when you leave the employ of Colorado: $" << totalRetirement << endl;

	//Determine defined benefit, option 2.
	totalRetirement = years*.025*(salary.at(salary.size() -1) + salary.at(salary.size() - 2) + salary.at(salary.size() -3))/3.0;
	cout << "Your three largest salaries are: $" << salary.at(salary.size() - 1) << ", $" << salary.at(salary.size() - 2) << ", $" << salary.at(salary.size() - 3) << endl;
	cout << "Your defined benefit based on three highest years is: $" << totalRetirement << endl;

	//Determine defined contribution.
	employerContribution = 0.1015;

	double contributionPercentage;
	if(years == 1){
		contributionPercentage = employeeContribution + 0.6*employerContribution;
	}
	if(years == 2){
		contributionPercentage = employeeContribution + 0.7*employerContribution;
	}
	if(years == 3){
		contributionPercentage = employeeContribution + 0.8*employerContribution;
	}
	if(years == 4){
		contributionPercentage = employeeContribution + 0.9*employerContribution;
	}
	if(years >= 5){
		contributionPercentage = employeeContribution + 1.0*employerContribution;
	}

	interest = 0.07;

	for(int i = 0; i < years; ++i){
		definedByYear.at(i) = contributionPercentage*salary.at(i)*compoundMultiplier.at(i);
		compoundMultiplier.at(i) = pow(interest + 1, compounds.at(i));
		cout << "The contribution to retirement in year " << i + 1 << " will be $" << definedByYear.at(i)/compoundMultiplier.at(i) << " and will be worth $" << definedByYear.at(i) << " at the end of employment." << endl;
	}

	totalRetirement = 0.0;
	for(int i = 0; i < years; ++i){
		totalRetirement += definedByYear.at(i);
	}

	cout << "This is your total retirement when you leave the employ of Colorado: $" << totalRetirement << endl;

	return 0;
}
