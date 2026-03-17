

public class Tortoise extends Thread{

    private boolean end = false;
    private int lap = 0;

    public Tortoise(){
        System.out.println("Tortoise is ready at the start line");
    }
    @Override
    public void run(){
        System.out.println("Tortoise started the race");
        do{
            lap++;
            synchronized (this) {
                try {
                    this.wait(1299);
                } catch (InterruptedException e) {
                    break;
                }
            }
            System.out.println("Tortoise laps = " + lap);
            if(lap == 10){
                System.out.println("Tortoise Wins the Race!!");
                end = true;
            }
        }while(!end);


    }

}
