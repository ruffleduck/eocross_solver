enum pos_t {UB, UR, UF, UL, FL, BL, FR, BR, DF, DR, DB, DL};
enum flip_t {noflip, flipF, flipB};

struct move_t {
    pos_t map[12];
    flip_t flip;
    std::string id;
    std::string z;
};

move_t U = {{UR,UF,UL,UB,FL,BL,FR,BR,DF,DR,DB,DL}, noflip, "U"};
move_t U2 = {{UF,UL,UB,UR,FL,BL,FR,BR,DF,DR,DB,DL}, noflip, "U2"};
move_t U3 = {{UL,UB,UR,UF,FL,BL,FR,BR,DF,DR,DB,DL}, noflip, "U'"};

move_t D = {{UB,UR,UF,UL,FL,BL,FR,BR,DR,DB,DL,DF}, noflip, "D"};
move_t D2 = {{UB,UR,UF,UL,FL,BL,FR,BR,DB,DL,DF,DR}, noflip, "D2"};
move_t D3 = {{UB,UR,UF,UL,FL,BL,FR,BR,DL,DF,DR,DB}, noflip, "D'"};

move_t R = {{UB,BR,UF,UL,FL,BL,UR,DR,DF,FR,DB,DL}, noflip, "R"};
move_t R2 = {{UB,DR,UF,UL,FL,BL,BR,FR,DF,UR,DB,DL}, noflip, "R2"};
move_t R3 = {{UB,FR,UF,UL,FL,BL,DR,UR,DF,BR,DB,DL}, noflip, "R'"};

move_t L = {{UB,UR,UF,FL,DL,UL,FR,BR,DF,DR,DB,BL}, noflip, "L"};
move_t L2 = {{UB,UR,UF,DL,BL,FL,FR,BR,DF,DR,DB,UL}, noflip, "L2"};
move_t L3 = {{UB,UR,UF,BL,UL,DL,FR,BR,DF,DR,DB,FL}, noflip, "L'"};

move_t F = {{UB,UR,FR,UL,UF,BL,DF,BR,FL,DR,DB,DL}, flipF, "F"};
move_t F2 = {{UB,UR,DF,UL,FR,BL,FL,BR,UF,DR,DB,DL}, noflip, "F2"};
move_t F3 = {{UB,UR,FL,UL,DF,BL,UF,BR,FR,DR,DB,DL}, flipF, "F'"};

move_t B = {{BL,UR,UF,UL,FL,DB,FR,UB,DF,DR,BR,DL}, flipB, "B"};
move_t B2 = {{DB,UR,UF,UL,FL,BR,FR,BL,DF,DR,UB,DL}, noflip, "B2"};
move_t B3 = {{BR,UR,UF,UL,FL,UB,FR,DB,DF,DR,BL,DL}, flipB, "B'"};

move_t moveset[18] = {U, U2, U3, D, D2, D3, R, R2, R3, L, L2, L3, F, F2, F3, B, B2, B3};
move_t cross_moveset[14] = {U, U2, U3, D, D2, D3, R, R2, R3, L, L2, L3, F2, B2};

move_t z_moveset[18] = {R, R2, R3, L, L2, L3, D, D2, D3, U, U2, U3, F, F2, F3, B, B2, B3};
move_t z2_moveset[18] = {D, D2, D3, U, U2, U3, L, L2, L3, R, R2, R3, F, F2, F3, B, B2, B3};
move_t z3_moveset[18] = {L, L2, L3, R, R2, R3, U, U2, U3, D, D2, D3, F, F2, F3, B, B2, B3};

move_t y_moveset[18] = {U, U2, U3, D, D2, D3, F, F2, F3, B, B2, B3, L, L2, L3, R, R2, R3};
move_t yz_moveset[18] = {R, R2, R3, L, L2, L3, F, F2, F3, B, B2, B3, U, U2, U3, D, D2, D3};
move_t yz2_moveset[18] = {D, D2, D3, U, U2, U3, F, F2, F3, B, B2, B3, R, R2, R3, L, L2, L3};
move_t yz3_moveset[18] = {L, L2, L3, R, R2, R3, F, F2, F3, B, B2, B3, D, D2, D3, U, U2, U3};

move_t x3_moveset[18] = {F, F2, F3, B, B2, B3, R, R2, R3, L, L2, L3, D, D2, D3, U, U2, U3};
move_t x3z_moveset[18] = {F, F2, F3, B, B2, B3, D, D2, D3, U, U2, U3, L, L2, L3, R, R2, R3};
move_t x3z2_moveset[18] = {F, F2, F3, B, B2, B3, L, L2, L3, R, R2, R3, U, U2, U3, D, D2, D3};
move_t x3z3_moveset[18] = {F, F2, F3, B, B2, B3, U, U2, U3, D, D2, D3, R, R2, R3, L, L2, L3};

