import java.util.LinkedList;

public class Dealer{

    private Deck m_deck;

    public Dealer() {  // default constructor initialized m_deck to new deck
        m_deck = new Deck();

    }

    public LinkedList<Card> deals (int n){

        LinkedList<Card> dealtCards = new LinkedList<>(); // Create empty list to store cards to be dealt

        for (int i = 0; i< n; i++){ // deal a random card from deck each iteration
            Card dealtCard = m_deck.deal();
            if(dealtCard != null){  //if not empty add card to dealtcards
                dealtCards.add(dealtCard);
            }
                else{  //if deck is empty exit and return dealt cards
                    break;
                }
        }
        return dealtCards;
    }

    public int size() {  // return number of cards in deck
        return m_deck.size();
    }
     public String toString(){  // return string of m_deck
        return m_deck.toString();
     }
}