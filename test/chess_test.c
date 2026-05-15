#include <chess.h>
#include <ctest.h>

/* ─── turn_suite (2 теста) ──────────────────────────────── */

CTEST(turn_suite, turn_switches_after_move) {
  GameState g;
  init_game(&g);
  ASSERT_EQUAL(0, g.turn);
  make_move(&g, 6, 4, 4, 4);
  ASSERT_EQUAL(1, g.turn);
}

CTEST(turn_suite, cannot_move_opponents_piece) {
  GameState g;
  init_game(&g);
  /* Белые пытаются ходить чёрной пешкой */
  ASSERT_FALSE(make_move(&g, 1, 4, 2, 4));
}
