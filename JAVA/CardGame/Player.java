import java.util.LinkedList;

public class Player {  // Player class
    private int playerNum;
    private LinkedList<Card> hand;
    private String pattern;


public Player(int playerNum, LinkedList<Card> hand, String pattern){ //overloaded constructor
    this.playerNum = playerNum;
    this.hand = hand;
    this.pattern = pattern;

 }

public Card playCard(){ // remove and return the top card from players hand
  
    if (hand.isEmpty()){
        return null; // when player hand is empty
    }
    return hand.removeFirst();
}


public boolean slaps(LinkedList<Card> pile){ //evaluate the players pattern 
    
    switch (pattern){
        case "doubles":  //check if player should slap pile of cards based on pattern
            return Game.doubles(pile);
        case "topBottom":
            return Game.topBottom(pile);
        case "sandwhich":
            return Game.sandwhich(pile);
        default:
            return false; // invalid pattern
   
        
    }
}


//accessor methods
public int getPlayerNum(){
    return playerNum;
 }

public LinkedList<Card> getHand(){
    return hand;
 }
public String getPattern(){
    return pattern;
 }

//for testing 
public String toString(){
    return "Player" + playerNum + "- Pattern: " + pattern + ", Hand: " + hand.toString();

 }
}