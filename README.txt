*A Team Espresso production*
----------------------------
Agapiou Marinos
Kamaras Georgios

*compile: make
*clean: make clean
*run: ./highway {arg1} {arg2} {arg3} {arg4}
    for example:
      ./highway 10 3 10 90

The classes and data structures that we use in our implementation are the following:
- class attica (our highway)
- class segment
- class segmentList
- class entrance
- struct toll
- class tollList
- struct vehicle
- class vehicleList
We don't use C++'s STL. We have created our own data structures (like, our own lists)
specifically for this project's purposes.

The way of thinking, in which we base our model, is:
1st step: We have a highway
2nd step: consisted of a list of segments
3rd step: each one of those segments has an entrance
4th step: which is consisted of 1 list of tolls, a toll is either an employee one or an electronic one
5th step: each toll contains a list of vehicles

We didn't change any of the project's specifications and we didn't do anything unique,
because we didn't thought it was necessary.
