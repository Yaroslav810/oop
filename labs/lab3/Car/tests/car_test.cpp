#include "../../../../catch2/catch.hpp"
#include "../CCar.h"
#include "../CCarController.h"

SCENARIO("")
{
	GIVEN("")
	{
		CCar car;

		REQUIRE(car.IsTurnedOn() == false);
		REQUIRE(car.GetDirection() == Direction::NO_MOVEMENT);
		REQUIRE(car.GetGear() == 0);
		REQUIRE(car.GetSpeed() == 0);

		WHEN("")
		{
			car.TurnOnEngine();

			THEN("")
			{
				REQUIRE(car.IsTurnedOn() == true);
				REQUIRE(car.GetDirection() == Direction::NO_MOVEMENT);
				REQUIRE(car.GetGear() == 0);
				REQUIRE(car.GetSpeed() == 0);
			}
		}

		WHEN("")
		{
			// Todo: Добавить тесты при изменении скорости и передачи при выключенном двигателе
			car.TurnOffEngine();

			THEN("")
			{
				REQUIRE(car.IsTurnedOn() == false);
				REQUIRE(car.GetDirection() == Direction::NO_MOVEMENT);
				REQUIRE(car.GetGear() == 0);
				REQUIRE(car.GetSpeed() == 0);
			}
		}

		WHEN("")
		{
			car.SetGear(0);

			THEN("")
			{
				REQUIRE(car.IsTurnedOn() == false);
				REQUIRE(car.GetDirection() == Direction::NO_MOVEMENT);
				REQUIRE(car.GetGear() == 0);
				REQUIRE(car.GetSpeed() == 0);
			}
		}

		WHEN("")
		{
			car.SetGear(1);

			THEN("")
			{
				REQUIRE(car.IsTurnedOn() == false);
				REQUIRE(car.GetDirection() == Direction::NO_MOVEMENT);
				REQUIRE(car.GetGear() == 1);
				REQUIRE(car.GetSpeed() == 0);
			}
		}

		WHEN("")
		{
			car.SetGear(-1);

			THEN("")
			{
				REQUIRE(car.IsTurnedOn() == false);
				REQUIRE(car.GetDirection() == Direction::NO_MOVEMENT);
				REQUIRE(car.GetGear() == -1);
				REQUIRE(car.GetSpeed() == 0);
			}
		}

		WHEN("")
		{
			car.SetGear(2);

			THEN("")
			{
				REQUIRE(car.IsTurnedOn() == false);
				REQUIRE(car.GetDirection() == Direction::NO_MOVEMENT);
				REQUIRE(car.GetGear() == 0);
				REQUIRE(car.GetSpeed() == 0);
			}
		}
	}
}