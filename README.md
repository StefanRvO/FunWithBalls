--Fun with Balls--

The code is Licensed under the Beerware license by Stefan Ravn van Overeem.

The Font - FreeSans.ttf - Is licensed under the GPLv3 by the FSF. https://www.gnu.org/software/freefont/license.html



--Compilation--

#Linux#

To compile under Linux you need the allegro libraries on ubuntu install these with:
apt-get install liballegro5.0 liballegro5-dev liballegro-ttf5.0 liballegro-ttf5-dev

You have to link against allegro when compiling.
g++ *.cpp -o FunWithBalls -Ofast -std=c++11 -lallegro -lallegro_primitives -lallegro_ttf -lallegro_font

or with clang:

clang++ *.cpp -o FunWithBalls -Ofast -std=c++11 -lallegro -lallegro_primitives -lallegro_ttf -lallegro_font

When running FreeSans.ttf should be in the same directory as the executable.

#Windows#
To compile on windows (sick) you have to do some wizardy.

Download allegro https://www.allegro.cc/files/
when you compile, link against include/liballegro-5.0.10-monolith-mt.a (don't ask how to do this)
Distribute with bin/liballegro-5.0.10-monolith-mt.a and FreeSans.ttf



--Controls--

Open Settings by pressing "s".

The settings are:

#Gravity#
Attraction between balls. Balls with higher radius have an highed gravity. 
You can also choose a negative gravity. This results in repulsion.

#Bounce on Edges#
Toggles between wheter the balls bounces off the edges or goes through.

#Collision#
Toggles Collsions between balls on and off.

#Viscosity#
Choose the viscosity of the medium the balls travel in.
This results in a resistance which slows the balls down.
A bigger ball slows faster than a small.
You can choose a negative viscosity.

#Spawnrate#
Choose how often a new ball is spawned

#Decay#
This shrinks the balls gradualy. 
You can choose a negative decay-rate, which causes the balls to grow.

#UnSpawnsize#
Balls smaller than this size will be destroyed

#CollisionMerge#
Balls merge on collision. This is still buggy.

