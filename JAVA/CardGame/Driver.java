import java.util.LinkedList;

public class Driver{

    public static void main(String[] args){

        // Dealer dealer = new Dealer();  //create dealer object

        // System.out.println("Dealer's Deck: ");
        // System.out.println(dealer);    //print out whole deck

        // LinkedList<Card> dealtCards = dealer.deals(5); //test deal 5 cards

        // System.out.println("\nDealt Cards: "); //Print out dealt cards
        // for(Card card : dealtCards){
        //     System.out.println(card);
        // }
        // System.out.println("Dealer's Deck: ");
        // System.out.println(dealer);    

        Game game = new Game(3); // intialize game with 3 players
        int winner = game.play();
        System.out.println("Player " + " "+ winner + "wins!");
    }
}