extern struct CPU {
    FILE* IP;
    char IR[1000];
    int quanta;
    int offset;
} CPU;
int run();
