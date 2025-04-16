import java.util.LinkedList;
import java.util.Random;

public class Game{
    private LinkedList<Player> players;
    private LinkedList<Card> pile;
    private Dealer dealer;
    private String[] patterns;



public Game () { // default contructor for game with 2 players
    this(2);
}

public Game (int numPlayers){  //overloaded constructor with specified number of players
    players = new LinkedList<> ();
    pile = new LinkedList<> ();
    dealer = new Dealer();  // Dealer object 
    patterns = new String [] {"doubles", "topBottom", "sandwhich"};

    initializePlayers(numPlayers);
    intializePile();

}

private void initializePlayers(int numPlayers){ // assigns pattern randomly but doesny ensure uniquenes assigned once 
    for (int i = 1; i <= numPlayers; i++ ){
        LinkedList<Card> hand = dealer.deals(52 / numPlayers); // distrubte evenly to number of players
        String randomPattern = patterns[ (int) (Math.random() * patterns.length)];
        players.add(new Player (i, hand, randomPattern)); //random index selected from patterns and assigns player number/ hand/ pattern
    
    }
}

private void intializePile(){
    pile = new LinkedList<>(); //initialize LinkedList for pile of cards in game
    for (Player player : players){
        pile.add(player.playCard()); // iterate over each player in players list and then playCard returns top card to be addded to pile
    }
}

public int play() {  //plays game until only one player remains
        int round = 1;

        System.out.println("Players: " + players);

        while (players.size() > 1) {
            System.out.println("Round: " + round);
            System.out.println("Pile of cards: " + pile);
    
            /*BEGIN CODE FROM SOURCE: https://codegym.cc/groups/posts/queue-poll-method-in-java */
            Player currentPlayer = players.poll(); // removes player at front of queue
            /*END CODE FROM SOURCE: https://codegym.cc/groups/posts/queue-poll-method-in-java */
            
            if(!currentPlayer.getHand().isEmpty()){ //check if player has cards to play
                System.out.println("Player " + currentPlayer.getPlayerNum() + "'s turn: ");

                Card playedCard = currentPlayer.playCard();
        

                if(playedCard != null){
                    System.out.println("Player " + currentPlayer.getPlayerNum() + "played: " + "" + playedCard);
                    pile.add(playedCard);}
                    

                     //checks for face card ranging from jack to ace
                    if ( playedCard.getRank() >= Card.JACK && playedCard.getRank() <= Card.ACE ) {
                        int chances = playedCard.getRank() - Card.JACK + 1; // calculate player chances based on face card played - jack/11
                        

                         for (int i = 0; i < chances; i++){ // Next player is allotted # of chances to play a face card
                            Player nextPlayer = nextPlayer();

                            if (nextPlayer == null){
                                break; //break if no more players
                            }
                            Card nextCard = nextPlayer.playCard();
                            pile.add(nextCard);

                            System.out.println("Player " + nextPlayer.getPlayerNum() + "played: " + nextCard);

                            if (nextCard.getRank() >= Card.JACK && nextCard.getRank() <= Card.ACE){ // check if the next card is also face card
                            
                             break;
                            }
                         }  //!faceCardPlayed
                        // if (pile.size() == chances + 1){ // current player takes pile if no face card is played
                        //     currentPlayer.getHand().addAll(pile);
                        //     pile.clear(); //clears pile after player wins round
                        //     players.add(currentPlayer);
                        if (!players.isEmpty()){ //&& players.getLast().slaps(pile)){ // checks for slapping player 
                           Player lastPlayer = players.getLast();
                           if (lastPlayer.slaps(pile)){
                            System.out.println("Player " + lastPlayer.getPlayerNum() + " slapped the pile!");
                            lastPlayer.getHand().addAll(pile);
                            pile.clear();
                        }
                        else{
                            currentPlayer.getHand().addAll(pile);
                            pile.clear();
                            players.add(currentPlayer);
                        }
                    }   
                 }
                else {
                    for (Player player : players){ //check for slaps
                        if (!player.equals(currentPlayer) && player.slaps(pile)){
                            System.out.println("Player "+ player.getPlayerNum() + " slapped the pile!");
                            player.getHand().addAll(pile); // player takes pile after slap and becomes currentplayer for begining new turn
                            pile.clear();
                            players.add(currentPlayer); // add current player to player list again
                            System.out.println("Player " + currentPlayer.getPlayerNum() + " takes the pile.");
                            break;
                        }
                    }
                    players.add(currentPlayer); // add current player to end of list
                    round++;
                }
               }
          
                 else{
                    System.out.println("Player " + currentPlayer.getPlayerNum() + " has no cards to play and is excluded from the game. ");
                }
        }
        // System.out.println("Player " + " "+ players.getFirst().getPlayerNum() + "wins!");
        return players.getFirst().getPlayerNum(); //returns winning player number
}


private Player nextPlayer() { // gets next player in rotation after current player
    
    if(players.isEmpty()){
        return null;
    }
    /*BEGIN CODE FROM SOURCE: https://codegym.cc/groups/posts/queue-poll-method-in-java */
    Player currentPlayer = players.poll(); // return players.poll(); //poll removes and returns the first element of the list
     /*END CODE FROM SOURCE: https://codegym.cc/groups/posts/queue-poll-method-in-java */
    players.addLast(currentPlayer); // add current player to end of list
    return players.getFirst();
}

public static boolean topBottom(LinkedList<Card> pile){ // method for topBottom pattern check
    if (pile.size() >= 2) {
        Card topCard = pile.getFirst();
        Card bottomCard = pile.getLast();
        return topCard.getRank() == bottomCard.getRank(); // checks if the top and bottom cards have same rank
    }
    return false; 
}

public static boolean doubles(LinkedList<Card> pile){ // method for doubles pattern check
    if (pile.size() >= 2) {
        Card lastCard = pile.getLast(); 
        Card secondToLastCard = pile.get(pile.size() - 2);
        return lastCard.getRank() == secondToLastCard.getRank(); // check if the last two cards in the pile have the same rank
    }
    return false; 
}
public static boolean sandwhich(LinkedList<Card> pile){
    // checks if the top and bottom cards in pile sandwich a card 
    if (pile.size() >= 3) {
        Card topCard = pile.getFirst();
        Card bottomCard = pile.getLast();
        Card middleCard = pile.get(pile.size() - 2);

        return topCard.getRank() == middleCard.getRank() || bottomCard.getRank() == middleCard.getRank();
    }
    return false; 
}
// accessor methods
public LinkedList<Player> getPlayers(){
    return players;
}
public LinkedList<Card> getPile(){
    return pile;
}
public Dealer  getDealer(){
    return dealer;
}

}