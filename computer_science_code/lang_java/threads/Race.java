public class Race {
    public static void main(String[] args){

        boolean end = false;
        Tortoise turtle = new Tortoise();
        Hare hare = new Hare();
        Thread rabbit = new Thread(hare);
        rabbit.start();
        turtle.start();
        do{
            if(!rabbit.isAlive()){
                turtle.interrupt();
                end = true;
            }
            if(!turtle.isAlive()){
                rabbit.interrupt();
                end = true;
            }
            if(rabbit.getState() == Thread.State.WAITING) {
                synchronized (hare) {
                    hare.notify();
                }
            }
        }while(!end);

    }
}
