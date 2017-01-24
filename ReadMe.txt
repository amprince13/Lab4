Names: Austin Prince, Daniel Finn, Ramona Durham
ID#s:  451187, 434967, 431331

Lab 4: Seven Card Stud

Design Notes:

The app is designed as specified in the lab write-up. Please note that during the 'before_turn' method, we elected to have users enter their desired discard indexes as a space-separated string, rather than continuously re-prompting. This allowed for a
much cleaner interface with the program. When an invalid index is passed, an error is printed and the remaining cards entered are discarded.

Note that our saved-player files simply print Name, Wins, Losses on lines 1,2,3 of the 
output file, respectively.


Errors and Warnings:

No errors and warnings during build in Visual Studio.

Exit Codes:
	1 - Error Opening File (Deck)
	7 - Invalid Hand Index	(Does not solely cause main app exit)
	8 - Instance Not Available
	9 - Game Already Started
	10 - Unknown Game
	11 - No Game In Progress
	12 - Player already playing (does not solely cause main app exit)
	13 - Invalid arguments

Testing:
First Test: I inputted Lab4.exe FiveCardStud Austin Ramona Dan. The program outputted an error code 10, which specifies an invalid game. 
Second Test: I played a Seven Card Stud Game followed by a Five Card Draw game. In this case I ran through the Seven Card Stud game after inputting Lab4.exe SevenCardStud Austin Dan Ramona on the command line.
In this case all the functionalities worked correctly. For example the program would not let you call if the bet was 3 and you had only bet 2 so far. At the end of the game if you removed players and there was only one player left the current game ended. In addition to this you 
can exit the game manually given the prompt "Would you like to play again" The program then asks you if you would like to play a different game. At this point when FiveCardDraw is entered the program asks if you would like to add players. If players are added that were already 
defined in a previous game it reads in the player information as defined in the player struct. 
Third Test: I tried to run a test where I inputted the wrong number of command line arguments. I only inputted the game name and didnt name any players. The program printed out the usage function as well as the GAME_NAME PLAYERS which was the correct ouput.
