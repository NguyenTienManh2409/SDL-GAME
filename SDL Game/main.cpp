#include "init_game.h"

int main(int argc, char* argv[]) {
    init_game game;
    game.init("NguyenTienManh_21020777");
    game.menu("Start");
    while (game.get_running()) {
        game.handle_event();
        game.handle_game();
    }
    game.clean();
    return 0;
}