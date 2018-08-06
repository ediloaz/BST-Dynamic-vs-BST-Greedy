# BST Dynamic vs BST Greedy

This program was created as part of an evaluation of a bachelor course in engineering. Resolves and find the optimal BST (Binary Search Tree) using two algorithms:
* Dynamic Algorithm ([about this](https://en.wikipedia.org/wiki/Dynamic_algorithm))
* Greedy Algorithm ([about this](https://en.wikipedia.org/wiki/Greedy_algorithm))

Both were programmed in C on Linux, the main purpose was not to find the tree, but to make a comparison between these two algorithms taking the time and the "correct solution" factors.

## Input

Is on the Linux terminal, not has a interface, the user can use two different ways:
* Example mode
* Experiment mode

### Example mode

Generate and solve a single random case with the two algorithms. The execution of the program generates a latex document where it specifies the initial problem, the response with the greedy algorithm, the response with the dynamic programming algorithm (both with their respective tables) and the conclusions reached in that execution.

The input must will be:
```
./program -X
```

![Screenshot of an example of Example mode](https://-empty.png)
Screenshot of an example of Example mode



### Experiment mode

Generates and solves N random cases, collects statistical data. The execution of the program generates a latex document where it specifies the amount of data that will be used, the time tables of both algorithms, as well as an additional one which shows the percentage of optimal responses produced by the Greedy algorithm.

The input must will be:
```
./program -E=N
```
Where the "N" parameter is the number of **N\*10 random cases** that you want.

![Screenshot of an example of Experiment mode](https://-empty.png)
Screenshot of an example of Experiment mode



![Screenshot of the interface with example data](https://raw.githubusercontent.com/ediloaz/Simplex-Algorithm/master/settings/screenshot-interface-example.png)
Screenshot of the interface with example data

## Output

In a latex document is showed the result of this. The information is the following:
* Cover (of the University)
* Short explain about the Algorithm Simplex
* Problem with math representation
* Initial table
* Intermediate tables
* Final table
* Solution
* Special cases

A .tex file is created and convert to pdf with *pdflatex command*  and is opened with *evince command*. All these files are saved in **Salida** folder.

![Screenshot of the intermediate tables in the Output](https://raw.githubusercontent.com/ediloaz/Simplex-Algorithm/master/settings/screenshot-output.png)
Screenshot of the intermediate tables in the Output

Also, detected and explained if the problem had the following special cases:
1. Not Limited Problem
2. Not Feasible Problem
3. Degenerated Problem
4. Problem with multiple solutions


### Prerequisites

It is necessary to have installed *latex* (including *pdflatex*), *pkg-config* and *evince* in your linux. You can install it with the following commands:
```
sudo apt-get install texlive-full
```
```
sudo apt-get install texmaker
```
```
sudo apt-get install evince
```
```
sudo apt install pkg-config
```

## Running

First is necessary compile the main file (*main.c*) with the command
```
 gcc -o program main.c
```

and then it can be opened
```
./program
```

## Built With

* [Sublime text](https://www.sublimetext.com/3)
* [NetBeans IDE 8.2](https://netbeans.org/community/releases/82/)
* [Glade](https://glade.gnome.org/)


## Authors

* **Edisson López** - *Main developer* - [ediloaz](https://github.com/ediloaz)

See also the list of [repositories](https://github.com/ediloaz?tab=repositories) who I participated/created.

