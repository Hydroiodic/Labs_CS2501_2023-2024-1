# Overview

<img class="overview-theme-img" src="./SpongeBob%20smiling.jpg" width="50%" />

## Description

This is a bonus lab for the course CS2501 - Discrete Mathematics (for Computer Science). The goal is to optimize the performance of a CDCL (Conflict-driven Clause learning) SAT solver. The CDCL approach has been applied to most modern SAT solvers to help solve large-scale SAT problems, whose basic idea is to iteratively

*   **decide** a truth value to an unassigned variable,
*   perform unit propagation,
*   when a **conflict** (a falsified clause) is obtained, **analyze** the reason for the conflict and **learn** a new clause that forbids this and possibly multiple similar conflict situations from occurring in the future, and
*   **backjump**, possibly over several irrelevant decisions, based on the conflict analysis.

You can find detailed information about the CDCL approach in [a note from Tommi Junttila](https://users.aalto.fi/~tjunttil/2020-DP-AUT/notes-sat/cdcl.html). The solver provided in this lab follows the CDCL approach, introducing much more sophisticated techniques to improve the performance of the solver, and is modularized to allow for easy extension.

### Setup

The lab is based on a SAT solver written in C++. It is suggested to complete the lab in a Linux environment. You can download the source code from [Canvas](https://oc.sjtu.edu.cn/courses/47984/files/5636731/download?download_frd=1). The source code is organized as follows:

*   `src/`: The source code of the solver
*   `test/`: The test cases
*   `build/`: The build products (executable and object files)
*   `scripts/`: Utility scripts

You need to install the following dependencies to run the solver:

*   g++
*   make

After installing all the dependencies, you can run the solver by executing the following commands in the root directory of the lab:

<pre>        $ ./configure && make</pre>

For detailed instructions of building, please refer to the file `README.md` in the root directory of the project.

### Part 1 - Basic Optimization

The code given by the TA is a problematic version of a CDCL SAT solver. If you run the test packaged with the code, you will find that the solver cannot solve all the test cases because of its huge memory usage. Your task is to find the reason of the problem and fix it.

You can check if you have fixed the problem by running the test cases. Note that you have to run `./configure` first to configure the compilation flags.

<pre>        $ make part1_test </pre>

If you run the test without fixing the problem, you should see the following output:

<pre>        # 20 <span style="color:#4e74d0;">...test/cnf/run.sh:</span> <span style="color:#3b763c;">CNF testing results: <b>114 ok</b></span>, <b>28 failed</b></pre>

If you fix the problem correctly, you should see the following output:

<pre>        # 20 <span style="color:#4e74d0;">...test/cnf/run.sh:</span> <span style="color:#3b763c;">CNF testing results: <b>141 ok</b></span>, 0 failed</pre>

**Hint**: The problem results from the process of **backtracking**. You can find the code for backtracking in the file `src/backtrack.cpp` and `src/analyze.cpp`. The proposers of chronological backtracking described the backjumping process in the paper ["Chronological Backtracking"](https://link.springer.com/chapter/10.1007/978-3-319-94144-8_7). You can try to change the target level of backjumping to see if the problem is fixed.

### Part 2 - Optimization contest

After fixing the problem, you can try to optimize the solver. There is still some room for improvement for the solver has not implemented the CDCL approach correctly. You can try to improve the solver by improving following techniques:

*   **Finding the UIP cut**
*   **Preprocessing**
*   **Clause vivifying** (In the file `src/vivify.cpp`)
*   **Unit propagation**

You can check your solver's performance by submitting your solver to this website. After you joined a team, you can submit your solver in page [teams](http://202.120.40.82:11236/team). The website will check if the solver finishes the first part of the bonus lab, and let the solver solve some SAT problems in 1200s, each of which contains millions of clauses and hundreds of literals.

All teams' best scores will be shown in the [scoreboard](http://202.120.40.82:11236/scoreboard). The results are ranked by the number of solved problems. If two teams have the same number of solved problems, the team with higher scores will be ranked higher. The score of a solver is measured by the difficulty of the problems it solves and the time it takes to solve them. The teams with the best score will be awarded with a bonus.

### Submission

Before submitting, you have to register an account. Note that you have to **USE YOUR STUDENT ID AS USERNAME**. Otherwise, your results cannot be recognized. This lab is a team lab. Each team can have up to 3 members. You can create, join or quit a team in page [teams](http://202.120.40.82:11236/team). Once your team is created, you can submit your solver in that page. Note that after a team of 3 members is formed, no more members can join the team and you cannot quit the team.

After your team completes the code, run `make handin` at the root directory to build the handin package. Then, submit the handin package `handin.zip` in page [teams](http://202.120.40.82:11236/team).

If your team finishes Part 1, each team member will receive a bonus of 2 points. If your team ranks top 30% of all the teams that solved >= 3 cases in Part 2, members will receive an additional 3 points as a bonus.

The deadline of this lab is **<time datetime="2022-12-25T23:59:59+08:00">2022-12-25 23:59:59 CST</time>**. No late submission will be accepted.

### Support

You can get support from the discussion topic in [Canvas](https://oc.sjtu.edu.cn/courses/47984/discussion_topics). You can also contact TA Shen Zhuohao by emailing `ao7777[at]sjtu[dot]edu[dot]cn`.
