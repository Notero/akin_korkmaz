import  java.util.*;

public class RandomStackof8 {

    final static String[] symbols = {"Clubs","Diamonds","Hearts","Spades"};
    final static String[] facedCards = {"Jack", "King", "Queen"};
    final static Card[][] deck = new Card[14][4];
    static Stack<Card> cardStack = new Stack<>();
    static Random rand = new Random();


    public static void main(String[] args) {

        fillDeck();


        fillStack();

        for(int e = 8; e > 0; e--){
            Card popped = cardStack.pop();

            if (popped instanceof FacedCard){
                if(Objects.equals(popped.getSymbol(), "")){
                    System.out.println(popped.getFace());
                }else{
                    System.out.println(popped.getFace() + " of " + popped.getSymbol());
                }
            }else if(popped != null){
                System.out.println(popped.getNumber() + " of " +popped.getSymbol());
            }

        }
    }

    //fills the deck 2D array with 54 cards including 2 Jokers
    public static void fillDeck(){
        for(int x = 0; x < 14; x++)
        {
            for(int y = 0; y < 4; y++)
            {
                //inserts the aces into the deck
                if(x == 0)
                {
                    deck[x][y] = new FacedCard(x + 1,symbols[y],"Ace");
                }
                //inserts the numbers 2-10 into the deck
                else if(x < 10)
                {
                    deck[x][y] = new Card(x + 1, symbols[y]);
                }
                //inserts faced cards = jack-king-queen into the deck
                else if(x < 13)
                {
                    deck[x][y] = new FacedCard(x+1,symbols[y],facedCards[x - 10]);
                }
                //insets the Jokers into the deck
                else if(y < 2)
                {
                    deck[x][y] = new FacedCard(x + 1,"","Joker");
                }
            }

        }
    }
    //this function fills the stack randomly from the created deck
    public static void fillStack(){
        for(int z = 8; z > 0; z--)
        {
            //gets 2 randomnumber to select from the 2d array
            int randomNumberX = rand.nextInt(14);
            int randomNumberY = rand.nextInt(4);

            //checks to see if the deck is empty at that location
            if(deck[randomNumberX][randomNumberY] != null)
            {
                //if not pushes 1 card into the stack every itteration
                cardStack.push(deck[randomNumberX][randomNumberY]);
                //and replaces null with the card in that position to ensure there is no duplicates
                deck[randomNumberX][randomNumberY] = null;
            }else{
                z++;
            }
        }
    }
}
