#include <fstream>
#include <iostream>
#include "moves.h"
#include <vector>

struct cube_t {
    bool eo[12];
    pos_t cross[4];
};

struct solution_t {
    std::string solution;
    int movecount;
};

const int eo_max_depth = 7;
const int cross_max_depth = 4;

int eocross_max_length;
int updating_eo_max_depth;
int updating_cross_max_depth;
solution_t best_cross_solution;

std::vector<solution_t> best_eocross_solutions;

cube_t apply_move(cube_t cube, move_t move) {
    cube_t result;
    for (int i = 0; i < 12; i++) {
        result.eo[move.map[i]] = cube.eo[i];
    }
    if (move.flip == flipF) {
        result.eo[UF] = !result.eo[UF];
        result.eo[FR] = !result.eo[FR];
        result.eo[DF] = !result.eo[DF];
        result.eo[FL] = !result.eo[FL];
    } else if (move.flip == flipB) {
        result.eo[UB] = !result.eo[UB];
        result.eo[BR] = !result.eo[BR];
        result.eo[DB] = !result.eo[DB];
        result.eo[BL] = !result.eo[BL];
    }
    for (int i = 0; i < 4; i++) {
        result.cross[i] = move.map[cube.cross[i]];
    }
    return result;
}

bool eo_solved(cube_t cube) {
    for (int i = 0; i < 12; i++) {
        if (!cube.eo[i])
            return false;
    }
    return true;
}

bool cross_solved(cube_t cube) {
    return cube.cross[0] == DF
        && cube.cross[1] == DR
        && cube.cross[2] == DB
        && cube.cross[3] == DL;
}

void solve_cross(cube_t cube, std::string solution = "", char prev_move = ' ', int depth = 0) {
    if (cross_solved(cube)) {
        if (depth <= updating_cross_max_depth) {
            updating_cross_max_depth = depth;
            best_cross_solution.solution = solution;
            best_cross_solution.movecount = depth;
        }
        return;
    }
    if (depth >= updating_cross_max_depth) {
        return;
    }
    for (int i = 0; i < 14; i++) {
        if (cross_moveset[i].id[0] == prev_move) {
            continue;
        }
        solve_cross(
            apply_move(cube, cross_moveset[i]),
            solution + cross_moveset[i].id + " ",
            cross_moveset[i].id[0],
            depth + 1
        );
    }
}

void solve_eocross(cube_t cube, std::string solution = "", char prev_move = ' ', int depth = 0) {
    if (eo_solved(cube)) {
        if (depth <= updating_eo_max_depth) {
            updating_eo_max_depth = depth;
            best_cross_solution.movecount = -1;
            solve_cross(cube);
            solution_t eocross_solution;
            eocross_solution.solution = solution + "/ " + best_cross_solution.solution;
            eocross_solution.movecount = depth + best_cross_solution.movecount;
            if (best_cross_solution.movecount >= 0 && eocross_solution.movecount <= eocross_max_length) {
                if (eocross_solution.movecount < eocross_max_length) {
                    best_eocross_solutions.clear();
                }
                eocross_max_length = eocross_solution.movecount;
                best_eocross_solutions.push_back(eocross_solution);
            }
            updating_cross_max_depth = cross_max_depth;
        }
        return;
    }
    if (depth >= updating_eo_max_depth) {
        return;
    }
    if (!cube.eo[UF] && !cube.eo[FR] && !cube.eo[DF] && !cube.eo[FL]) {
        solve_eocross(apply_move(cube, F), solution + "F ", 'F', depth + 1);
        solve_eocross(apply_move(cube, F3), solution + "F' ", 'F', depth + 1);
        return;
    }
    if (!cube.eo[UB] && !cube.eo[BR] && !cube.eo[DB] && !cube.eo[BL]) {
        solve_eocross(apply_move(cube, B), solution + "B ", 'B', depth + 1);
        solve_eocross(apply_move(cube, B3), solution + "B' ", 'B', depth + 1);
        return;
    }
    for (int i = 0; i < 18; i++) {
        if (moveset[i].id[0] == prev_move
        ||  (moveset[i].flip == flipB && cube.eo[UB] && cube.eo[BR] && cube.eo[DB] && cube.eo[BL])
        ||  (moveset[i].flip == flipF && cube.eo[UF] && cube.eo[FR] && cube.eo[DF] && cube.eo[FL])) {
            continue;
        }
        solve_eocross(
            apply_move(cube, moveset[i]),
            solution + moveset[i].id + " ",
            moveset[i].id[0],
            depth + 1
        );
    }
}

cube_t scramble_cube(std::string scramble, move_t scramble_moveset[18]) {
    cube_t cube;
    for (int i = 0; i < 12; i++) {
        cube.eo[i] = true;
    }
    cube.cross[0] = DF;
    cube.cross[1] = DR;
    cube.cross[2] = DB;
    cube.cross[3] = DL;
    std::string scramble_move;
    for (int i = 0; i < scramble.length(); i++) {
        if (scramble[i] == ' ') {
            for (int m = 0; m < 18; m++) {
                if (moveset[m].id == scramble_move) {
                    cube = apply_move(cube, scramble_moveset[m]);
                    break;
                }
            }
            scramble_move = "";
        } else {
            scramble_move += scramble[i];
        }
    }
    for (int m = 0; m < 18; m++) {
        if (moveset[m].id == scramble_move) {
            cube = apply_move(cube, scramble_moveset[m]);
            break;
        }
    }
    return cube;
}

void solve_eocross_scramble(std::string scramble, move_t scramble_moveset[18], std::string moveset_id) {
    eocross_max_length = eo_max_depth + cross_max_depth;
    updating_eo_max_depth = eo_max_depth;
    updating_cross_max_depth = cross_max_depth;
    solve_eocross(scramble_cube(scramble, scramble_moveset));
    std::cout << std::endl;
    for (int i = 0; i < best_eocross_solutions.size(); i++) {
        std::cout << best_eocross_solutions[i].movecount << " HTM "
                  << moveset_id << " " << best_eocross_solutions[i].solution << std::endl;
    }
}

int main(int argc, char ** argv) {
    std::string scramble;
    if (argc == 1) {
        std::cout << "Enter scramble: ";
        std::getline(std::cin, scramble);
    } else {
        scramble = argv[1];
    }
    solve_eocross_scramble(scramble, moveset, "");
    solve_eocross_scramble(scramble, z_moveset, "z");
    solve_eocross_scramble(scramble, z2_moveset, "z2");
    solve_eocross_scramble(scramble, z3_moveset, "z'");
    solve_eocross_scramble(scramble, y_moveset, "y");
    solve_eocross_scramble(scramble, yz_moveset, "y z");
    solve_eocross_scramble(scramble, yz2_moveset, "y z2");
    solve_eocross_scramble(scramble, yz3_moveset, "y z'");
    solve_eocross_scramble(scramble, x3_moveset, "x'");
    solve_eocross_scramble(scramble, x3z_moveset, "x' z");
    solve_eocross_scramble(scramble, x3z2_moveset, "x' z2");
    solve_eocross_scramble(scramble, x3z3_moveset, "x' z'");
    return 0;
}
