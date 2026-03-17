import java.util.*;

public class TicketQueue {

    final static String[] names = {"James","Akin","Jacquelin","Amy","Stephanie","Duru","Hans"};
    static Random rand = new Random();
    static Queue<Person> TiQueue = new LinkedList<>();
    static List<Integer> ticketList = new ArrayList<>();

    public static void main(String[] args) {


        for(int x = 0; x < 7; x++){
            //insets 7 person into the queue
            TiQueue.offer(new Person(names[x],0 ));


        }

        for(int z = 0; z < 7; z++){
            //creates 7 random tickets
            ticketList.add(rand.nextInt(500));
        }

        for(int y = 0; y < 7; y++){
            //removes the person head of the queue and assigns them a ticket randomly and prints who left the queue
            Person onWork = TiQueue.poll();
            assert onWork != null;
            onWork.setTicketNumber(ticketList.get(y));

            System.out.println(onWork.getName() + " just left the Queue with Ticket Number " + onWork.getTicketNumber());

        }

    }
}
