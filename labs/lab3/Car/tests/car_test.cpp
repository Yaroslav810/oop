#define CATCH_CONFIG_MAIN
#include "../../../../catch2/catch.hpp"
#include "../CCarController.h"

SCENARIO("A car can be controlled")
{
	GIVEN("Creation car")
	{
		CCar car;
		REQUIRE(!car.IsTurnedOn());
		REQUIRE(car.GetDirection() == CCar::Direction::NO_MOVEMENT);
		REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
		REQUIRE(car.GetSpeed() == 0);

		WHEN("The engine turns off")
		{
			REQUIRE(car.TurnOffEngine());
			THEN("The engine is off")
			{
				REQUIRE(!car.IsTurnedOn());
				REQUIRE(car.GetDirection() == CCar::Direction::NO_MOVEMENT);
				REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
				REQUIRE(car.GetSpeed() == 0);
			}

			WHEN("Changing gears")
			{
				REQUIRE(!car.SetGear(CCar::Gear::REVERSE));
				THEN("The gear remains neutral")
				{
					REQUIRE(!car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::NO_MOVEMENT);
					REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
					REQUIRE(car.GetSpeed() == 0);
				}

				REQUIRE(car.SetGear(CCar::Gear::NEUTRAL));
				THEN("The gear remains neutral")
				{
					REQUIRE(!car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::NO_MOVEMENT);
					REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
					REQUIRE(car.GetSpeed() == 0);
				}

				REQUIRE(!car.SetGear(CCar::Gear::FIRST));
				THEN("The gear remains neutral")
				{
					REQUIRE(!car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::NO_MOVEMENT);
					REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
					REQUIRE(car.GetSpeed() == 0);
				}
			}

			WHEN("Changing speeds")
			{
				REQUIRE(!car.SetSpeed(10));
				THEN("The speed remains zero")
				{
					REQUIRE(!car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::NO_MOVEMENT);
					REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
					REQUIRE(car.GetSpeed() == 0);
				}

				REQUIRE(!car.SetSpeed(0));
				THEN("The speed remains zero")
				{
					REQUIRE(!car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::NO_MOVEMENT);
					REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
					REQUIRE(car.GetSpeed() == 0);
				}
			}

			WHEN("Turning on the engine")
			{
				REQUIRE(car.TurnOnEngine());
				THEN("The engine turns on")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::NO_MOVEMENT);
					REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
					REQUIRE(car.GetSpeed() == 0);
				}
			}
		}

		WHEN("The engine turns on")
		{
			REQUIRE(car.TurnOnEngine());
			THEN("The engine is on")
			{
				REQUIRE(car.IsTurnedOn());
				REQUIRE(car.GetDirection() == CCar::Direction::NO_MOVEMENT);
				REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
				REQUIRE(car.GetSpeed() == 0);
			}

			WHEN("Setting the gears")
			{
				REQUIRE(car.SetGear(CCar::Gear::FIRST));
				THEN("The first gear is set")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::NO_MOVEMENT);
					REQUIRE(car.GetGear() == CCar::Gear::FIRST);
					REQUIRE(car.GetSpeed() == 0);
				}

				REQUIRE(car.SetGear(CCar::Gear::NEUTRAL));
				THEN("The neutral gear is set")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::NO_MOVEMENT);
					REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
					REQUIRE(car.GetSpeed() == 0);
				}

				REQUIRE(car.SetGear(CCar::Gear::REVERSE));
				THEN("The reverse gear is set")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::NO_MOVEMENT);
					REQUIRE(car.GetGear() == CCar::Gear::REVERSE);
					REQUIRE(car.GetSpeed() == 0);
				}

				REQUIRE(!car.SetGear(CCar::Gear::SECOND));
				THEN("The second gear is not set")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::NO_MOVEMENT);
					REQUIRE(car.GetGear() == CCar::Gear::REVERSE);
					REQUIRE(car.GetSpeed() == 0);
				}
			}

			WHEN("Reverse gear is installed")
			{
				REQUIRE(car.SetGear(CCar::Gear::REVERSE));
				THEN("The reverse gear is set")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::NO_MOVEMENT);
					REQUIRE(car.GetGear() == CCar::Gear::REVERSE);
					REQUIRE(car.GetSpeed() == 0);
				}

				THEN("It is impossible to turn off the engine")
				{
					REQUIRE(!car.TurnOffEngine());
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::NO_MOVEMENT);
					REQUIRE(car.GetGear() == CCar::Gear::REVERSE);
					REQUIRE(car.GetSpeed() == 0);
				}

				WHEN("Changing the speed")
				{
					REQUIRE(car.SetSpeed(10));
					THEN("Backward movement, speed 10")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::BACK);
						REQUIRE(car.GetGear() == CCar::Gear::REVERSE);
						REQUIRE(car.GetSpeed() == 10);
					}

					REQUIRE(car.SetSpeed(20));
					THEN("Backward movement, speed 20")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::BACK);
						REQUIRE(car.GetGear() == CCar::Gear::REVERSE);
						REQUIRE(car.GetSpeed() == 20);
					}

					REQUIRE(!car.SetSpeed(30));
					THEN("Backward movement, the speed has not changed")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::BACK);
						REQUIRE(car.GetGear() == CCar::Gear::REVERSE);
						REQUIRE(car.GetSpeed() == 20);
					}

					REQUIRE(car.SetSpeed(15));
					THEN("Backward movement, speed 20")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::BACK);
						REQUIRE(car.GetGear() == CCar::Gear::REVERSE);
						REQUIRE(car.GetSpeed() == 15);
					}

					REQUIRE(!car.SetGear(CCar::Gear::FIRST));
					THEN("The state has not changed")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::BACK);
						REQUIRE(car.GetGear() == CCar::Gear::REVERSE);
						REQUIRE(car.GetSpeed() == 15);
					}

					REQUIRE(car.SetGear(CCar::Gear::NEUTRAL));
					THEN("Neutral gear is set")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::BACK);
						REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
						REQUIRE(car.GetSpeed() == 15);
					}

					REQUIRE(!car.SetSpeed(20));
					THEN("The speed has not changed")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::BACK);
						REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
						REQUIRE(car.GetSpeed() == 15);
					}

					WHEN("Changing gears")
					{
						REQUIRE(!car.SetGear(CCar::Gear::REVERSE));
						THEN("The gear has not changed")
						{
							REQUIRE(car.IsTurnedOn());
							REQUIRE(car.GetDirection() == CCar::Direction::BACK);
							REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
							REQUIRE(car.GetSpeed() == 15);
						}

						REQUIRE(car.SetGear(CCar::Gear::NEUTRAL));
						THEN("The gear is neutral")
						{
							REQUIRE(car.IsTurnedOn());
							REQUIRE(car.GetDirection() == CCar::Direction::BACK);
							REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
							REQUIRE(car.GetSpeed() == 15);
						}

						REQUIRE(!car.SetGear(CCar::Gear::FIRST));
						THEN("The gear has not changed")
						{
							REQUIRE(car.IsTurnedOn());
							REQUIRE(car.GetDirection() == CCar::Direction::BACK);
							REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
							REQUIRE(car.GetSpeed() == 15);
						}
					}

					REQUIRE(car.SetSpeed(5));
					THEN("Speed 5")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::BACK);
						REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
						REQUIRE(car.GetSpeed() == 5);
					}
				}
			}

			WHEN("First gear is installed")
			{
				REQUIRE(car.SetGear(CCar::Gear::FIRST));
				THEN("The first gear is set")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::NO_MOVEMENT);
					REQUIRE(car.GetGear() == CCar::Gear::FIRST);
					REQUIRE(car.GetSpeed() == 0);
				}

				THEN("It is impossible to turn off the engine")
				{
					REQUIRE(!car.TurnOffEngine());
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::NO_MOVEMENT);
					REQUIRE(car.GetGear() == CCar::Gear::FIRST);
					REQUIRE(car.GetSpeed() == 0);
				}

				WHEN("Changing the speed")
				{
					REQUIRE(car.SetSpeed(10));
					THEN("Forward movement, speed 10")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
						REQUIRE(car.GetGear() == CCar::Gear::FIRST);
						REQUIRE(car.GetSpeed() == 10);
					}

					REQUIRE(car.SetSpeed(30));
					THEN("Forward movement, speed 30")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
						REQUIRE(car.GetGear() == CCar::Gear::FIRST);
						REQUIRE(car.GetSpeed() == 30);
					}

					REQUIRE(!car.SetSpeed(40));
					THEN("Forward movement, the speed has not changed")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
						REQUIRE(car.GetGear() == CCar::Gear::FIRST);
						REQUIRE(car.GetSpeed() == 30);
					}

					REQUIRE(car.SetSpeed(15));
					THEN("Forward movement, speed 15")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
						REQUIRE(car.GetGear() == CCar::Gear::FIRST);
						REQUIRE(car.GetSpeed() == 15);
					}

					REQUIRE(!car.SetGear(CCar::Gear::SECOND));
					THEN("The state has not changed")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
						REQUIRE(car.GetGear() == CCar::Gear::FIRST);
						REQUIRE(car.GetSpeed() == 15);
					}

					REQUIRE(car.SetGear(CCar::Gear::NEUTRAL));
					THEN("Neutral gear is set")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
						REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
						REQUIRE(car.GetSpeed() == 15);
					}

					REQUIRE(!car.SetSpeed(20));
					THEN("The speed has not changed")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
						REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
						REQUIRE(car.GetSpeed() == 15);
					}

					WHEN("Changing gears")
					{
						REQUIRE(!car.SetGear(CCar::Gear::REVERSE));
						THEN("The gear has not changed")
						{
							REQUIRE(car.IsTurnedOn());
							REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
							REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
							REQUIRE(car.GetSpeed() == 15);
						}

						REQUIRE(car.SetGear(CCar::Gear::NEUTRAL));
						THEN("The gear is neutral")
						{
							REQUIRE(car.IsTurnedOn());
							REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
							REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
							REQUIRE(car.GetSpeed() == 15);
						}

						REQUIRE(car.SetGear(CCar::Gear::FIRST));
						THEN("The gear has changed")
						{
							REQUIRE(car.IsTurnedOn());
							REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
							REQUIRE(car.GetGear() == CCar::Gear::FIRST);
							REQUIRE(car.GetSpeed() == 15);
						}
					}

					REQUIRE(car.SetSpeed(5));
					THEN("Speed 5")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
						REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
						REQUIRE(car.GetSpeed() == 5);
					}
				}
			}

			WHEN("Second gear is installed")
			{
				REQUIRE(car.SetGear(CCar::Gear::FIRST));
				REQUIRE(car.SetSpeed(20));
				REQUIRE(car.SetGear(CCar::Gear::SECOND));
				THEN("The second gear is set")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
					REQUIRE(car.GetGear() == CCar::Gear::SECOND);
					REQUIRE(car.GetSpeed() == 20);
				}

				REQUIRE(car.SetSpeed(40));
				THEN("Forward movement, speed 40")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
					REQUIRE(car.GetGear() == CCar::Gear::SECOND);
					REQUIRE(car.GetSpeed() == 40);
				}

				WHEN("Changing gears")
				{
					REQUIRE(!car.SetGear(CCar::Gear::REVERSE));
					THEN("The gear has not changed")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
						REQUIRE(car.GetGear() == CCar::Gear::SECOND);
						REQUIRE(car.GetSpeed() == 40);
					}

					REQUIRE(car.SetGear(CCar::Gear::NEUTRAL));
					THEN("The gear is neutral")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
						REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
						REQUIRE(car.GetSpeed() == 40);
					}

					REQUIRE(!car.SetGear(CCar::Gear::FIRST));
					THEN("The gear has not changed")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
						REQUIRE(car.GetGear() == CCar::Gear::NEUTRAL);
						REQUIRE(car.GetSpeed() == 40);
					}

					REQUIRE(car.SetGear(CCar::Gear::SECOND));
					THEN("The gear is second")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
						REQUIRE(car.GetGear() == CCar::Gear::SECOND);
						REQUIRE(car.GetSpeed() == 40);
					}

					REQUIRE(car.SetGear(CCar::Gear::THIRD));
					THEN("The gear is third")
					{
						REQUIRE(car.IsTurnedOn());
						REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
						REQUIRE(car.GetGear() == CCar::Gear::THIRD);
						REQUIRE(car.GetSpeed() == 40);
					}
				}

				REQUIRE(!car.SetSpeed(19));
				THEN("Forward movement, speed 40")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
					REQUIRE(car.GetGear() == CCar::Gear::SECOND);
					REQUIRE(car.GetSpeed() == 40);
				}

				REQUIRE(!car.SetSpeed(61));
				THEN("Forward movement, speed 40")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
					REQUIRE(car.GetGear() == CCar::Gear::SECOND);
					REQUIRE(car.GetSpeed() == 40);
				}
			}

			WHEN("Third gear is installed")
			{
				REQUIRE(car.SetGear(CCar::Gear::FIRST));
				REQUIRE(car.SetSpeed(20));
				REQUIRE(car.SetGear(CCar::Gear::SECOND));
				REQUIRE(car.SetSpeed(30));
				REQUIRE(car.SetGear(CCar::Gear::THIRD));
				THEN("The third gear is set")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
					REQUIRE(car.GetGear() == CCar::Gear::THIRD);
					REQUIRE(car.GetSpeed() == 30);
				}

				REQUIRE(!car.SetSpeed(29));
				THEN("Forward movement, speed 30")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
					REQUIRE(car.GetGear() == CCar::Gear::THIRD);
					REQUIRE(car.GetSpeed() == 30);
				}

				REQUIRE(!car.SetSpeed(61));
				THEN("Forward movement, speed 30")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
					REQUIRE(car.GetGear() == CCar::Gear::THIRD);
					REQUIRE(car.GetSpeed() == 30);
				}
			}

			WHEN("Fourth gear is installed")
			{
				REQUIRE(car.SetGear(CCar::Gear::FIRST));
				REQUIRE(car.SetSpeed(20));
				REQUIRE(car.SetGear(CCar::Gear::SECOND));
				REQUIRE(car.SetSpeed(30));
				REQUIRE(car.SetGear(CCar::Gear::THIRD));
				REQUIRE(car.SetSpeed(40));
				REQUIRE(car.SetGear(CCar::Gear::FOURTH));
				THEN("The fourth gear is set")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
					REQUIRE(car.GetGear() == CCar::Gear::FOURTH);
					REQUIRE(car.GetSpeed() == 40);
				}

				REQUIRE(!car.SetSpeed(39));
				THEN("Forward movement, speed 40")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
					REQUIRE(car.GetGear() == CCar::Gear::FOURTH);
					REQUIRE(car.GetSpeed() == 40);
				}

				REQUIRE(!car.SetSpeed(91));
				THEN("Forward movement, speed 40")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
					REQUIRE(car.GetGear() == CCar::Gear::FOURTH);
					REQUIRE(car.GetSpeed() == 40);
				}
			}

			WHEN("Fifth gear is installed")
			{
				REQUIRE(car.SetGear(CCar::Gear::FIRST));
				REQUIRE(car.SetSpeed(20));
				REQUIRE(car.SetGear(CCar::Gear::SECOND));
				REQUIRE(car.SetSpeed(30));
				REQUIRE(car.SetGear(CCar::Gear::THIRD));
				REQUIRE(car.SetSpeed(40));
				REQUIRE(car.SetGear(CCar::Gear::FOURTH));
				REQUIRE(car.SetSpeed(50));
				REQUIRE(car.SetGear(CCar::Gear::FIFTH));
				THEN("The fifth gear is set")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
					REQUIRE(car.GetGear() == CCar::Gear::FIFTH);
					REQUIRE(car.GetSpeed() == 50);
				}

				REQUIRE(!car.SetSpeed(49));
				THEN("Forward movement, speed 50")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
					REQUIRE(car.GetGear() == CCar::Gear::FIFTH);
					REQUIRE(car.GetSpeed() == 50);
				}

				REQUIRE(!car.SetSpeed(151));
				THEN("Forward movement, speed 50")
				{
					REQUIRE(car.IsTurnedOn());
					REQUIRE(car.GetDirection() == CCar::Direction::FORWARD);
					REQUIRE(car.GetGear() == CCar::Gear::FIFTH);
					REQUIRE(car.GetSpeed() == 50);
				}
			}
		}
	}
}
