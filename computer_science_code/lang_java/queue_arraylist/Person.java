public class Person {
    final private String name;
    private int ticketNumber;

    //constructor for person
    public Person(String name, int ticketNumber){
        this.name = name;
        this.ticketNumber = ticketNumber;
    }
    //gets the ticket number of the person
    public int getTicketNumber() {
        return ticketNumber;
    }
    //gets the name of the person
    public String getName() {
        return name;
    }
    //gives a ticket number to a person after the person class has been created
    public void setTicketNumber(int ticketNumber){
        this.ticketNumber = ticketNumber;
    }
}
