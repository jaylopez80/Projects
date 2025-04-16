public class Card{

    private int rank; // variables for rank and suit
    private int suit;

    public static final int HEARTS = 0; //Constants for suits
    public static final int SPADES = 1;
    public static final int CLUBS = 2;
    public static final int DIAMONDS = 3;

    public static final int JACK = 11; //Constants for rank
    public static final int QUEEN = 12;
    public static final int KING = 13;
    public static final int ACE = 14;

    public Card(){ //Default contructor for Ace of spades
        this(ACE, SPADES);
    }

    public Card(int rank, int suit){ // overloaded constructor 
        this.rank = rank;
        this.suit = suit;
    }

    public Card (Card copyCard){ //Copy constructor
        this.rank = copyCard.rank;
        this.suit = copyCard.suit;
    }

    public String toString() { 
        String rankStr;     // holds string for rank

        switch (rank){   //determine string text for given face rank or 2-11 rank 
            case JACK:
                rankStr = "Jack";
                break;
            case QUEEN:
                rankStr = "Queen";
                break;
            case KING:
                rankStr = "King";
                break;
            case ACE:
                rankStr = "Ace";
                break;
            default:
                rankStr = String.valueOf(rank); //rank 2-11

        }
        String suitStr; // text determination for suits

        switch (suit){
            case HEARTS:
                suitStr = "Hearts";
                break;
            case SPADES:
                suitStr = "Spades";
                break;
            case DIAMONDS:
                suitStr = "Diamonds";
                break;
            case CLUBS:
                suitStr = "Clubs";
                break;
            default:
                suitStr = "Unknown";

        }

        return rankStr + " " +"of" + " " + suitStr;  // return string of rank and suit of a card
    }

    public boolean equals(Card copyCard){  // compare two cards based on rank
        return this.rank == copyCard.rank;
    }

    public void setRank(int rank){ //mutators and accessors for rank/suit
        this.rank = rank;

    }
    public void setSuit(int suit){ 
        this.suit = suit;
    }

    public int getRank() {
        return rank;
    }
    public int getSuit(){
        return suit;
    }

}