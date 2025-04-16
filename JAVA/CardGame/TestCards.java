import java.util.LinkedList;

public class TestCards{

    public static void main(String[] args){

        Dealer dealer = new Dealer();  //create dealer object

        System.out.println("Dealer's Deck: ");
        System.out.println(dealer);    //print out whole deck

        LinkedList<Card> dealtCards = dealer.deals(5); //test deal 5 cards

        System.out.println("\nDealt Cards: "); //Print out dealt cards
        for(Card card : dealtCards){
            System.out.println(card);
        }
        System.out.println("Dealer's Deck: ");
        System.out.println(dealer);    
    }
}
