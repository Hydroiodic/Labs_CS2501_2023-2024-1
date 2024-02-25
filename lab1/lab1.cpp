#include "common.h"
#include <cstddef>
#include <minisat/core/SolverTypes.h>
#include <minisat/mtl/Vec.h>
#include <vector>

using namespace Minisat;

bool lab1(int states[], int n, int button[][2], int m, bool answer[])
{
    Solver solver;
    Var variables[1000];
    int i, j;
    for (i = 0; i < m; ++i)
        variables[i] = solver.newVar();

    // your solution start from here.

    // to classify by stones instead of swithes
    std::vector<int> Vec[1000];
    for (i = 0; i < m; ++i) {
        for (int j : { 0, 1 }) {
            if (!button[i][j]) break;
            Vec[button[i][j] - 1].push_back(i);
        }
    }

    // some basic function
    auto get_num_of_ones = [](unsigned int x) -> size_t {
        size_t num = 0;
        while (x) {
            num += x & 1;
            x >>= 1;
        }
        return num;
    };
    auto is_odd = [](int x) -> bool {
        return x % 2;
    };

    // add clauses for the solver

    // the uncommented method below considers more situations
    // use a vector to store the expression to input the solver
    vec<Lit> _vec;
    for (i = 0; i < n; ++i) {
        // get the number of switches on this stone
        int length = Vec[i].size();

        // iterate binary number from 0b0 to 0b111...(with the same counts of one to the value length)
        for (int it = 0; it < 1 << length; ++it) {
            // to judge whether the condition of switches agrees to the problem
            int num_of_ones = get_num_of_ones(it);
            // use the incorrect group of variables, which results in F for the problem
            if (states[i] && is_odd(num_of_ones)) {
                // add variables to the vector
                for (int pos = 0; pos < length; ++pos) {
                    if (it & (1 << pos)) _vec.push(~mkLit(variables[Vec[i][pos]]));
                    else _vec.push(mkLit(variables[Vec[i][pos]]));
                }
                // add the clause and clear the vector
                solver.addClause(_vec);
                _vec.clear();
            }
            else if (!states[i] && !is_odd(num_of_ones)) {
                for (int pos = 0; pos < length; ++pos) {
                    if (it & (1 << pos)) _vec.push(~mkLit(variables[Vec[i][pos]]));
                    else _vec.push(mkLit(variables[Vec[i][pos]]));
                }
                solver.addClause(_vec);
                _vec.clear(true);
            }
            // if the group of variables is correct, continue to loop
            else continue;
        }

        // the commented part below only supports the condition provided by the problem
        /********************************************************************************** /
        switch (Vec[i].size()) {
        case 1:
            if (states[i]) solver.addClause(~mkLit(variables[Vec[i][0]]));
            else solver.addClause(mkLit(variables[Vec[i][0]]));
            break;

        case 2:
            if (states[i]) {
                solver.addClause(~mkLit(variables[Vec[i][0]]), mkLit(variables[Vec[i][1]]));
                solver.addClause(mkLit(variables[Vec[i][0]]), ~mkLit(variables[Vec[i][1]]));
            }
            else {
                solver.addClause(~mkLit(variables[Vec[i][0]]), ~mkLit(variables[Vec[i][1]]));
                solver.addClause(mkLit(variables[Vec[i][0]]), mkLit(variables[Vec[i][1]]));
            }
            break;

        default:
            throw("The input data is wrong!");
        }
        / **********************************************************************************/
    }

    // your solution end here.
    // solve SAT problem
    auto sat = solver.solve();
    if (sat)
    {
        for (i = 0; i < m; ++i)
            answer[i] = (solver.modelValue(variables[i]) == l_True);
        return true;
    }
    return false;
}
