public class Card {

    private final int number;
    private final String symbol;


    //card constructor
    public Card(int number, String symbol)
    {
        this.number = number;
        this.symbol = symbol;

    }
    //gets symbol
    public String getSymbol() {
        return symbol;
    }
    //gets number
    public int getNumber(){
        return number;
    }
    //function that will be inherited to FacedCards
    public String getFace(){
        return "";
    }

    //gives the whole card as a String
    @Override
    public String toString() {
        return "Card{" +
                "number=" + number +
                ", symbol='" + symbol + '\'' +
                '}';
    }
}
