# 8_Philosophers
'Philosophers' is a simulation program that explores concurrent programming with threads, mutexes and semaphores. It is an implementation of a solution of a variation on the dining philosophers problem by Edsger Dijkstra.

## Description

The problem involves one or more philosophers sitting at a round table with a large bowl of spaghetti in the middle. The spaghetti can only be eaten with two forks, and there are only as many forks as there are
philosophers. Each philosopher successively eats, sleeps, and thinks. If a philosopher hasn't eaten in a certain timeframe, he will die of starvation. Philosophers cannot communicate with each other.

The goal of the program is to implement a simulation of this problem and its solution. The latter is obtained by creating an algorithm that keeps the philosophers alive as far as possible. The program takes several 
parameters such as the number of philosophers, time to die, time to eat, time to sleep and - optionally - the number of times each philosopher must eat. The program outputs a message each time a philosopher takes an
action.
