Jonathan Lopez
2436878
jonlopez@chapman.edu
CPSC-231-03
MP3B ERS

        For this project, I extended the use of the Dealer, Deck and Card classes which were the foundation for my Egyptian Rat Screw game.
   I used the Player class to handle the representation of a player number, hand and assigned pattern for slapping the deck when applicable.
   I incorporated use of a switch case for the slap method, which served the purpose calling the appropriate Game pattern check based on
   the randomly assigned player pattern. The Game class utilizes the foundational deck, dealer, card, and player classes to manage the gameplay,
   begining with initializing players with an evenly distributed hand and pattern assigned randomly. My biggest challenges included
   properly checking for face cards being played and allowing the following player "chances" to play a face card, as well as the handling of slap
  scenarios. Im not sure if the issue is with the slap method in the player class or my control flow in the play method within my game class. I also 
  encountered null pointer after running my program, due to player not having any remaining cards in hand/list.  Currently
  my program deals cards evenly with the remainder cards added to the pile, then begins the round with player one. My main issue is inconsistencies 
  with player turns based on player patterns/face cards and adjusting the pile based on the player who wins each round. I run into instances where 
  the game plays until a winner and others where a player has an empty list and null pointer 
  exception occurs. 
References:
https://www.wikihow.com/Play-Egyptian-Rat-Screw
https://codegym.cc/groups/posts/queue-poll-method-in-java
https://www.geeksforgeeks.org/linked-list-in-java/   
https://stackoverflow.com/questions/6842473/how-can-i-select-random-element-from-the-list

