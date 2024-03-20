IdleRPG is an idle fighting game written in C++ where two characters are chosen to fight each other until one loses all their health.

When a fight begins a player is chosen at random to start and then characters take turns hitting each other. If the character has an activated ability they build up charge when successfully hitting the other character and the ability is activated at the start of their turn when they have enough charge.

Characters have a variety of stats that can be modified such as:
Health - when equal to 0 the character dies
DamageAvg - the average damage that character will deal
DamageRange - the range of values the character can hit around the average
Armour - flat damage reduction
Accuracy - the chance their attack will hit
Evasion - the chance you will dodge an attack
Resilience - Multiplicative damage reduction

The goal of the project is to be able to clearly analyse and modify the win rates of different characters in order to become closer to true balance.
