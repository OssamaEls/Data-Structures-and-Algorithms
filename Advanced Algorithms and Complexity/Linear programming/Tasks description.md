## energy_values (Gaussian elimination)
You’re looking into a restaurant menu which shows for each dish the list of ingredients with amounts
and the estimated total energy value in calories. You would like to find out the energy values of
individual ingredients (then you will be able to estimate the total energy values of your favorite dishes).

## diet (linear inequalities -small set-)
You want to optimize your diet: that is, make sure that your diet satisfies all the recommendations
of nutrition experts, but you also get maximum pleasure from your food and drinks. For each dish
and drink you know all the nutrition facts, cost of one item, and an estimation of how much you like
it. Your budget is limited, of course. The recommendations are of the form “total amount of calories
consumed each day should be at least 1000” or “the amount of water you drink in liters should be at
least twice the amount of food you eat in kilograms”, and so on. You optimize the total pleasure which
is the sum of pleasure you get from consuming each particular dish or drink, and that is proportional
to the amount amount𝑖 of that dish or drink consumed.
The budget restriction and the nutrition recommendations can be converted into a system of linear
inequalities like 𝑚∑︀𝑖=1cost𝑖 · amount𝑖 ≤ Budget, amount𝑖 ≥ 1000 and amount𝑖 − 2 · amount𝑗 ≥ 0, where
amount𝑖 is the amount of 𝑖-th dish or drink consumed, cost𝑖 is the cost of one item of 𝑖-th dish or
drink, and 𝐵𝑢𝑑𝑔𝑒𝑡 is your total budget for the diet. Of course, you can only eat a non-negative amount
amount𝑖 of 𝑖-th item, so amount𝑖 ≥ 0. The goal to maximize total pleasure is reduced to the linear
objective 𝑚∑︀𝑖=1amount𝑖 · pleasure𝑖 → max where pleasure𝑖 is the pleasure you get after consuming one
unit of 𝑖-th dish or drink (some dishes like fish oil you don’t like at all, so pleasure𝑖 can be negative).
Combined, all this is a linear programming problem which you need to solve now.