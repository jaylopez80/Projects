import java.util.LinkedList;
import java.util.Random;

public class Deck{

    private LinkedList<Card> m_cards; // LL to store cards 

    public Deck() { // Defaulat constructor to initialize a deck of 52 cards

        m_cards = new LinkedList<>();

        for (int suit = 0; suit <= 3; suit++) {    // hearts - diamonds
            for (int rank = 2; rank <= 14; rank ++){  // 2 - face value cards
                m_cards.add(new Card (rank, suit));
            }
        }
            
    }

    public Deck(Deck copyDeck) {  // Copy constructor creates a deck from another deck
        m_cards = new LinkedList<>();
        for(Card card : copyDeck.m_cards) {
            m_cards.add(new Card(card));
        }

    }

    public String toString(){  //Display each card in the deck
        return m_cards.toString();

    }

    public int size(){  // Gets the number of cards in deck
        return m_cards.size();
    }

    public Card deal() { // Deal a random card from the deck
        if (!m_cards.isEmpty()){
            /*BEGIN CODE FROM SOURCE: https://stackoverflow.com/questions/6842473/how-can-i-select-random-element-from-the-list */
            int randomCard = new Random().nextInt(m_cards.size()); // generate a random index to remove card 
            /*END OF CODE FROM SOURCE: https://stackoverflow.com/questions/6842473/how-can-i-select-random-element-from-the-list */
            return m_cards.remove(randomCard);

        }
             else{
                return null;  //else empty deck
             }
            }
}   
