#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <cstdlib>
using namespace std;

int wpnDmg(string wpnNm, int str)
{
	unsigned seed = time(0);
	srand(seed);
	int dmg = 0;

	if (wpnNm == "Bronze Sword")
		dmg = (rand() % 6) + str;
	else if (wpnNm == "Iron Sword")
		dmg = (rand() % 11) + str;
	else if (wpnNm == "Magic Sword")
		dmg = (rand() % 21) + str;
	else
		dmg = (rand() % 4) + str;

	return dmg;
}

int crtrDmg(string crtrNm)
{
	unsigned jakr = time(0);
	srand(jakr);
	int dmg = 0;

	if (crtrNm == "gbln")
		dmg = (rand()*rand()) % 3;
	else if (crtrNm == "orc")
		dmg = (rand()*rand()) % 6;
	else if (crtrNm == "knt")
		dmg = rand() % 9;
	else if (crtrNm == "wzrd")
		dmg = rand() % 6 + 5;
	else if (crtrNm == "bhmth")
		dmg = rand()*rand() % 9 + 4;
	else if (crtrNm == "ncr")
		dmg = rand()*rand() % 10 + 5;
	else if (crtrNm == "drgn")
		dmg = rand()*rand() % 10 + 9;

	return dmg;
}

int main()
{
	int gblnHlth = 10, plrHlth, plrHlthMax = 10, dmg = 0, str = 0, orcHlth = 20, kntHlth = 30,
		wzrdHlth = 45, bhmthHlth = 60, ncrHlth = 75, drgnHlth = 100, rest = 0;
	plrHlth = plrHlthMax;
	bool run = false;
	string input, crtrNm, wpnNm = "Fist";

	cout << "Welcome to this Amazing Adventure! You have come upon a tower of legend, with seven "
		 << "levels.\nIn order to get to the top, you must defeat all the monsters on each "
		 << "level.\n(enter any Key to continue)";
	getline(cin, input);
	cout << "You have three main Attributes: (enter any Key to continue)\n";
	getline(cin,input);
	cout << "Your Strength.\n";
	getline(cin,input);
	cout << "Your Health.\n";
	getline(cin,input);
	cout << "And your Weapon.\n";
	getline(cin,input);
	cout << "You must use these things to defeat your Foes and claim Victory.\n"
		 << "Enter any key to begin.";
	getline(cin,input);


	while ((drgnHlth > 0) && (plrHlth > 0))
	{
		run = 0;
		cout <<"You may fight, rest, or view your stats.\n\nChoose:\n0: Fight\n1: Rest\n2: View Stats\n";
		cin >> rest;

		if (rest == 1)
		{
			cout << "You rest, and recover your Health to Maximum.\n";
			plrHlth = plrHlthMax;
			rest = 0;
		}
		else if (rest == 2)
		{
			cout << "Your Weapon is the " << wpnNm << ".\nYou have " << plrHlthMax
				<< " Maximum Health and " << str << " Strength.\n";
			rest = 0;
		}
		else if (rest == 0)
		{

			if (gblnHlth > 0)
				gblnHlth = 10;

			while ((gblnHlth > 0) && (plrHlth > 0) && (run == false))
			{
				cout << "The Goblin:\n";
				cout << "You have " << plrHlth << " Health.\nYour Foe has "
						<< gblnHlth << " Health.\n";
				cout << "Do you Fight or Run?\n0: Fight\n1: Run\n";
				cin >> run;

				if (run == 0)
				{
					dmg = wpnDmg(wpnNm, str);
					gblnHlth = gblnHlth - dmg;
					cout << "You deal " << dmg << " Damage and the Goblin ";
					dmg = crtrDmg("gbln");
					plrHlth = plrHlth - dmg;
					cout << "deals " << dmg << " Damage.\n";
				}
				else if (run == 1)
					cout << "You flee for your Life!\n";
				else
					cout <<"That is not a valid option!\n";

			if ((gblnHlth <= 0) && (plrHlth > 0))
			{
				cout << "Congratulations! You have Defeated the Goblin!\n"
						<< "You gain 1 Strength and 5 Health!\n";
				str ++;
				plrHlthMax += 5;
				cout << "Your Strength is now " << str << " and your Health is "
						<< plrHlthMax << ".\n";
				cout << "You have also taken the Goblin's Bronze Sword!\n(enter any Key to continue)\n\n";
				wpnNm = "Bronze Sword";
				getline(cin,input);
			}

			if (plrHlth <= 0)
				cout << "Oh no, you have DIED!\nxx\n__";
			}



			if (orcHlth > 0)
				orcHlth = 20;

			while ((gblnHlth <= 0) && (plrHlth > 0) && (orcHlth > 0) && (run == false))
			{
				cout << "The Orc:\n";
				cout << "You have " << plrHlth << " Health.\nYour foe has "
					 << orcHlth << " Health.\n";
				cout << "Do you fight or run?\n0: Fight\n1: Run\n";
				cin >> run;

				if (run == 0)
				{
					dmg = wpnDmg(wpnNm, str);
					orcHlth = orcHlth - dmg;
					cout << "You deal " << dmg << " Damage and the Orc ";
					dmg = crtrDmg("orc");
					plrHlth = plrHlth - dmg;
					cout << "deals " << dmg << " Damage.\n";
				}

				else if (run == 1)
					cout << "You flee for your Life!\n";
				else
					cout <<"That is not a valid option!\n";

			if ((orcHlth <= 0) && (plrHlth > 0))
			{
				cout << "Congratulations! You have defeated the Orc!\n"
					 << "You gain 2 Strength and 10 Health!\n";
				str += 2;
				plrHlthMax += 10;
				cout << "Your Strength is now " << str << " and your Maximum Health is "
					 << plrHlthMax << ".\n(enter any Key to continue)\n\nh";
				getline(cin,input);
			}

			if (plrHlth <= 0)
				cout << "Oh no, you have DIED!\nxx\n__";
			}



			if (kntHlth > 0)
				kntHlth = 30;

			while ((orcHlth <= 0) && (plrHlth > 0) && (kntHlth > 0) && (run == false))
			{
				cout << "The Black Night:\n";
				cout << "You have " << plrHlth << " Health.\nYour foe has "
					 << kntHlth << " Health.\n";
				cout << "Do you fight or run?\n0: Fight\n1: Run\n";
				cin >> run;

				if (run == 0)
				{
					dmg = wpnDmg(wpnNm, str);
					kntHlth = kntHlth - dmg;
					cout << "You deal " << dmg << " Damage and the Black Night ";
					dmg = crtrDmg("knt");
					plrHlth = plrHlth - dmg;
					cout << "deals " << dmg << " Damage.\n";
				}

				else if (run == 1)
					cout << "You flee for your Life!\n";
				else
					cout <<"That is not a valid option!\n";

			if ((kntHlth <= 0) && (plrHlth > 0))
			{
				cout << "Congratulations! You have defeated the Black Night!\n"
					 << "You gain 1 Strength and 10 Health!\n";
				str ++;
				plrHlthMax += 10;
				cout << "Your Strength is now " << str << " and your Maximum Health is "
					 << plrHlthMax << ".\n";
				cout << "You have also taken the Black Night's Iron Sword!\n(enter any Key to continue)\n\n";
				getline(cin,input);
				wpnNm = "Iron Sword";

			}

			if (plrHlth <= 0)
				cout << "Oh no, you have DIED!\nxx\n__";
			}



			if (wzrdHlth > 0)
				wzrdHlth = 45;

			while ((kntHlth <= 0) && (plrHlth > 0) && (wzrdHlth > 0) && (run == false))
			{
				cout << "The Blue Wizard:\n";
				cout << "You have " << plrHlth << " Health.\nYour foe has "
					 << wzrdHlth << " Health.\n";
				cout << "Do you fight or run?\n0: Fight\n1: Run\n";
				cin >> run;

				if (run == 0)
				{
					dmg = wpnDmg(wpnNm, str);
					wzrdHlth = wzrdHlth - dmg;
					cout << "You deal " << dmg << " Damage and the Blue Wizard ";
					dmg = crtrDmg("wzrd");
					plrHlth = plrHlth - dmg;
					cout << "deals " << dmg << " Damage.\n";
				}

				else if (run == 1)
					cout << "You flee for your Life!\n";
				else
					cout <<"That is not a valid option!\n";

			if ((wzrdHlth <= 0) && (plrHlth > 0))
			{
				cout << "Congratulations! You have defeated the Blue Wizard!\n"
					 << "You gain 2 Strength and 15 Health!\n";
				str += 2;
				plrHlthMax += 15;
				cout << "Your Strength is now " << str << " and your Maximum Health is "
					 << plrHlthMax << ".\n(enter any Key to continue)\n\n";
				getline(cin,input);
			}

			if (plrHlth <= 0)
				cout << "Oh no, you have DIED!\nxx\n__";
			}



			if (bhmthHlth > 0)
				bhmthHlth = 60;

			while ((wzrdHlth <= 0) && (plrHlth > 0) && (bhmthHlth > 0) && (run == false))
			{
				cout << "The Monstrous Behemoth:\n";
				cout << "You have " << plrHlth << " Health.\nYour foe has "
					 << bhmthHlth << " Health.\n";
				cout << "Do you fight or run?\n0: Fight\n1: Run\n";
				cin >> run;

				if (run == 0)
				{
					dmg = wpnDmg(wpnNm, str);
					bhmthHlth = bhmthHlth - dmg;
					cout << "You deal " << dmg << " Damage and the Behemoth ";
					dmg = crtrDmg("bhmth");
					plrHlth = plrHlth - dmg;
					cout << "deals " << dmg << " Damage.\n";
				}

				else if (run == 1)
					cout << "You flee for your Life!\n";
				else
					cout <<"That is not a valid option!\n";

			if ((bhmthHlth <= 0) && (plrHlth > 0))
			{
				cout << "Congratulations! You have defeated the Monstrous Behemoth!\n"
					 << "You gain 3 Strength and 10 Health!\n";
				str += 3;
				plrHlthMax += 10;
				cout << "Your Strength is now " << str << " and your Maximum Health is "
					 << plrHlthMax << ".\n(enter any Key to continue)\n\n";
				getline(cin,input);
			}

			if (plrHlth <= 0)
				cout << "Oh no, you have DIED!\nxx\n__";
			}



			if (ncrHlth > 0)
				ncrHlth = 75;

			while ((bhmthHlth <= 0) && (plrHlth > 0) && (ncrHlth > 0) && (run == false))
			{
				cout << "The Awful Necromancer:\n";
				cout << "You have " << plrHlth << " Health.\nYour foe has "
					 << ncrHlth << " Health.\n";
				cout << "Do you fight or run?\n0: Fight\n1: Run\n";
				cin >> run;

				if (run == 0)
				{
					dmg = wpnDmg(wpnNm, str);
					ncrHlth = ncrHlth - dmg;
					cout << "You deal " << dmg << " Damage and the Necromancer ";
					dmg = crtrDmg("ncr");
					plrHlth = plrHlth - dmg;
					cout << "deals " << dmg << " Damage.\n";
				}

				else if (run == 1)
					cout << "You flee for your Life!\n";
				else
					cout << "That is not a valid option!\n";

			if ((ncrHlth <=0) && (plrHlth > 0))
			{
				cout << "Congratulations! You have defeated the Awful Necromancer!\n"
					 << "You gain 2 Strength and 10 Health!\n";
				str += 2;
				plrHlthMax += 10;
				cout << "Your Strength is now " << str << " and your Maximum Health is "
					 << plrHlthMax << ".\n";
				cout << "You have also taken the Necromancer's Magic Sword!\n(enter any Key to continue)\n\n";
				wpnNm = "Magic Sword";
				getline(cin,input);
			}

			if (plrHlth <= 0)
				cout << "Oh no, you have DIED!\nxx\n__";
			}



			if (drgnHlth > 0)
				drgnHlth = 100;

			while ((ncrHlth <= 0) && (plrHlth > 0) && (drgnHlth > 0) && (run == false))
			{
				cout << "Your Final Foe - The Dragon!\n";
				cout << "You have " << plrHlth << " Health.\nYour foe has "
					 << drgnHlth << " Health.\n";
				cout << "Do you fight or run?\n0: Fight\n1: Run\n";
				cin >> run;

				if (run == 0)
				{
					dmg = wpnDmg(wpnNm, str);
					drgnHlth = drgnHlth - dmg;
					cout << "You deal " << dmg << " Damage and the Dragon ";
					dmg = crtrDmg("drgn");
					plrHlth = plrHlth - dmg;
					cout << "deals " << dmg << " Damage.\n";
				}

				else if (run == 1)
					cout << "You flee for your Life!\n";
				else
					cout <<"That is not a valid option!\n";
			if (plrHlth <= 0)
				cout << "Oh no, you have DIED!\nxx\n__";
			}

			if ((drgnHlth <=0) && (plrHlth > 0))
			{
				cout << "Congratulations! You have slain the Dragon and claimed Victory over"
					 << " the Tower!\nThe Game is over; You have Won!!! :D";
			}


		}

		else
		{
			cout << "That is not a valid option!\n";
		}
	}

	return 0;
}
