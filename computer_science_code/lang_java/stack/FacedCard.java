//extends card class for facedcards
public class FacedCard extends Card {

    final private String face;

    //constructor that will also hold the face value of a card
    public FacedCard(int number, String symbol, String face){
        super(number,symbol);
        this.face = face;
    }

    //gets the face of faced card
    @Override
    public String getFace() {
        return face;
    }
}
