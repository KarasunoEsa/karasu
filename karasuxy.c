void karasuxy(int x,int y) {
    HANDLE hCOut;
    COORD Coord;
    hCOut = GetStdHandle(STD_OUTPUT_HANDLE);
    Coord.X = (SHORT)x;
    Coord.Y = (SHORT)y;
    SetConsoleCursorPosition(hCOut, Coord);
}
