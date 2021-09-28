## evacuation
A tornado is approaching the city, and we need to evacuate the people quickly. There are several
roads outgoing from the city to the nearest cities and other roads going further. The goal is to evacuate
everybody from the city to the capital, as it is the only other city which is able to accomodate that
many newcomers. We need to evacuate everybody as fast as possible, and your task is to find out
what is the maximum number of people that can be evacuated each hour given the capacities of all
the roads.

## airline_crews
The airline offers a bunch of flights and has a set of crews that can work on those flights. However,
the flights are starting in different cities and at different times, so only some of the crews are able to
work on a particular flight. You are given the pairs of flights and associated crews that can work on
those flights. You need to assign crews to as many flights as possible and output all the assignments.
### Solution idea: maximum matching in bipartite graph.

## stock_charts
You’re in the middle of writing your newspaper’s end-of-year economics summary, and you’ve decided
that you want to show a number of charts to demonstrate how different stocks have performed over the
course of the last year. You’ve already decided that you want to show the price of 𝑛 different stocks,
all at the same 𝑘 points of the year.
A simple chart of one stock’s price would draw lines between the points (0, 𝑝𝑟𝑖𝑐𝑒0), (1, 𝑝𝑟𝑖𝑐𝑒1), . . . , (𝑘 −
1, 𝑝𝑟𝑖𝑐𝑒𝑘−1), where 𝑝𝑟𝑖𝑐𝑒𝑖 is the price of the stock at the 𝑖-th point in time.
In order to save space, you have invented the concept of an overlaid chart. An overlaid chart is the
combination of one or more simple charts, and shows the prices of multiple stocks (simply drawing a
line for each one). In order to avoid confusion between the stocks shown in a chart, the lines in an
overlaid chart may not cross or touch.
Given a list of 𝑛 stocks’ prices at each of 𝑘 time points, determine the minimum number of overlaid
charts you need to show all of the stocks’ prices.
### Solution idea:
Determine what are the conditions under which two stocks can be put on the same chart. Then think when
more than 2 stocks can be put on the same chart.
Try to reduce the problem to the maximum matching in a bipartite graph problem, and to the first trick
on the way is to create a bipartite graph of stocks with two nodes for each stock.