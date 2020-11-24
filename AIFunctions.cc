//using board as an array

//print board - function to print board for testing

//delete_all_boards - function delete all boards - this needs to happen so that in our generate all legal board moves function, we can delete options (ie: sometimes we save the move of a single dice roll if that is the only legal move, but other times we want to delete the saved single roll moves because there are legal moves for both rolls

//board_equal_p - function to check if two boards are equal

//reverse_board - function reverse board --> this will reverse the values of the pieces on the board. this makes it so that we can have two computers play each other pretty easily.  essentially just lets you switch players.   (if array index 3 has value -1, it will be switched to 1

//copy array - function to copy array 

//roll - function for roll - we should make this return the number and the frequency -- that way when we get double 3's we can have it return (3, 4) and therefore know to generate possible moves where you can move 3 four times.

//functions for bearing off:
//no_checkers_in_range_p(board, start, end) 
//bearing_off_p(board)
//no_checkers_outside_of_roll_p(board, roll)
//no_checkers_on_board_p (board) 

//generate_boards_for_roll(board, roll) - this will generate all possible moves for a particular board and a given roll - this means a SINGLE roll, give all legal moves

//generate_moves (initial board, rolls) - this will generate all legal moves for multiple rolls and it will call the above generate_boards_for_roll function
