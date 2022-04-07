Battle Mechanics
 - You are presented with the opponent
 - you get to choose what move you want to make in order to attack the opponent. (Not sure of what we would want the choices to be)
 - weapons have damage ranges 2 - 5 (e.g. sometimes it might do 2 other times it might do 5)
That said, it all depends on chance of how much damage is done.

Attack Damage Formula:
attackDamage = baseDamage + weaponDamage(weaponClass.weaponName)
 - Where, baseDamage is declared based on the players race and kit.
 - Where, weaponDamage() is a function which takes a weapon as an input and then randomly outputs a value within the range of the weapons damage (which weapon damage range specifically was the input.

Armor:
Assign a number group to a given percentage of armour. The number group will be consecutive levels. I.E. levels 1-3 is 1% armour, 4-6 is 2% and so on. As the number of levels gets bigger it will start leveling off; 100-120 = 20%, 120-140 =21% and so on. This is just a rudimentary example, but you get the idea 

Defense mitigation formula:
attackMitigation = armorLevelBalancer([Any Player or Enemy’s armor stat can be an input])

damageTaken = attackDamage - attackMitigation([Any Player or Enemy’s armor stat can be an input])
