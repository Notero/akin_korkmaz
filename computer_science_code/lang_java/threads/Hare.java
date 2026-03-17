public class Hare implements Runnable{

    private boolean end = false;
    private int lap = 0;

    public Hare(){
        System.out.println("Hare is ready at the start line");
    }

    @Override
    public void run(){

        System.out.println("Hare started the race");
        do{
            lap++;
            synchronized (this) {
                try {
                    this.wait(500);
                } catch (InterruptedException e) {
                    break;
                }
            }
            System.out.println("Hare laps = " + lap);
            if(lap == 9){
                System.out.println("Rabbit tries to fall a sleep under a tree");
                System.out.println("but cant get comfy so gets back up");
                synchronized (this) {
                    try {
                        this.wait();
                    } catch (InterruptedException e) {
                        break;
                    }
                }
            }
            if(lap == 10){
                System.out.println("Hare Wins the Race!!");
                end = true;
            }
        }while(!end);


    }
}
