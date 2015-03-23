namespace jnthn{
  namespace sudoku{

    class puzzle{
      int lengths[81];
      int * data;
      
      int coord(int x, int y){
	return (x - 1) % 9 + ((y - 1) * 9);
      }

      public:

      puzzle( char * txt);

    }

    puzzle simplify(puzzle p);
  }
}
