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

![Screenshot of the terminal in Example mode](https://github.com/ediloaz/BST-Dynamic-vs-BST-Greedy/blob/master/settings/input-example.png)



### Experiment mode

Generates and solves N random cases, collects statistical data. The execution of the program generates a latex document where it specifies the amount of data that will be used, the time tables of both algorithms, as well as an additional one which shows the percentage of optimal responses produced by the Greedy algorithm.

The input must will be:
```
./program -E=N
```
Where the "N" parameter is the number of **N\*10 random cases** that you want.


![Screenshot of the terminal in Experiment mode](https://github.com/ediloaz/BST-Dynamic-vs-BST-Greedy/blob/master/settings/input-experiment.png)


## Output

A .tex file (and others files required) will create and convert to pdf with *pdflatex command*  and will open with *evince command*. All these files are saved in **output** folder. And each mode create a different document structure.


### Example mode

![Screenshot of an example of Example mode](https://github.com/ediloaz/BST-Dynamic-vs-BST-Greedy/blob/master/settings/Example-1.jpg)

![Screenshot of an example of Example mode](https://github.com/ediloaz/BST-Dynamic-vs-BST-Greedy/blob/master/settings/Example-2.jpg)



### Experiment mode

![Screenshot of the Experiment mode](https://github.com/ediloaz/BST-Dynamic-vs-BST-Greedy/blob/master/settings/Experiment-1.jpg)




## Prerequisites

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


## Authors

* **Edisson López** - *Main developer* - [ediloaz](https://github.com/ediloaz)

See also the list of [repositories](https://github.com/ediloaz?tab=repositories) who I participated/created.

