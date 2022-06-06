#include "FindMaxEx.h"
#include <iostream>
#include <optional>

struct Athlete
{
	std::string firstName;
	std::string lastName;
	std::string patronymic;
	short height{};
	short weight{};
};

std::vector<Athlete> GetAthletes()
{
	return {
		{ "Fedotov", "Andron", "Vasilievich", 190, 70 },
		{ "Argevanidze", "Leonid", "Makarovich", 185, 85 },
		{ "Yefimov", "Vissarion", "Romanovich", 192, 82 },
		{ "Naumov", "Anatoly", "Evgenievich", 182, 74 },
		{ "Zhuravlev", "Igor", "Zakirovich", 188, 84 },
	};
}

std::string GetAthleteFIO(const Athlete& athlete)
{
	return athlete.firstName + " " + athlete.lastName + " " + athlete.patronymic;
}

void PrintAthleteWithMaxHeight(const std::vector<Athlete>& athletes)
{
	Athlete athlete;
	if (FindMaxEx(athletes, athlete, [](const Athlete&athlete1, const Athlete&athlete2) {
			return athlete1.height < athlete2.height;
		}))
	{
		std::cout << "Athlete with maximum height: " << GetAthleteFIO(athlete) << std::endl;
	}
	else
	{
		std::cout << "It was not possible to find an athlete with the maximum height" << std::endl;
	}
}

void PrintAthleteWithMaxWeight(const std::vector<Athlete>& athletes)
{
	Athlete athlete;
	if (FindMaxEx(athletes, athlete, [](const Athlete&athlete1, const Athlete&athlete2) {
			return athlete1.weight < athlete2.weight;
		}))
	{
		std::cout << "Athlete with maximum weight: " << GetAthleteFIO(athlete) << std::endl;
	}
	else
	{
		std::cout << "It was not possible to find an athlete with the maximum weight" << std::endl;
	}
}

int main()
{
	try
	{
		auto athletes = GetAthletes();
		PrintAthleteWithMaxHeight(athletes);
		PrintAthleteWithMaxWeight(athletes);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	return 0;
}
