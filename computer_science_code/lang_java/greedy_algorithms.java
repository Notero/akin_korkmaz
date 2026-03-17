import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Collections;
import java.util.PriorityQueue;
import java.util.Scanner;

public class greedy_algorithms {


    int robotCount;
    int buildingCount;
    String robotFileName;
    String buildingFileName;

    int unservedBuildings;
    int successfulDeliveries;
    int[] robotArray;
    int[] buildingArray;

    public GreedyRobots(int robotCount, int buildingCount, String robotFileName, String buildingFileName) {
        this.robotCount = robotCount;
        this.buildingCount = buildingCount;
        this.robotFileName = robotFileName;
        this.buildingFileName = buildingFileName;
    }

    public void readFiles() throws FileNotFoundException {

        robotArray = new int[robotCount];
        buildingArray = new int[buildingCount];

        Scanner fileReader = new Scanner(new File(robotFileName));

        for (int i = 0; i < robotCount; i++) {
            robotArray[i] = fileReader.nextInt();
        }
        Arrays.sort(robotArray);
        fileReader.close();
        fileReader = new Scanner(new File(buildingFileName));

        for (int i = 0; i < buildingCount; i++) {
            buildingArray[i] = fileReader.nextInt();
        }
        Arrays.sort(buildingArray);
        fileReader.close();
    }
    public void assignDeliveries() throws FileNotFoundException {
        readFiles();

        PriorityQueue<Integer> robots = new PriorityQueue<>(robotCount, Collections.reverseOrder());
        for (int e : robotArray) robots.add(e);

        successfulDeliveries = 0;

        for (int i = buildingCount - 1; i >= 0; i--) {
            int need = buildingArray[i];
            if (robots.isEmpty()) break;

            int maxEnergy = robots.peek();
            
            if (maxEnergy < need) {
                continue;
            }

            robots.poll();
            int rem = maxEnergy - need;
            if (rem > 0) robots.add(rem);
            successfulDeliveries++;
        }


    }



    public void displayResults() {
        unservedBuildings = buildingCount - successfulDeliveries;
        System.out.println("Succesfull Deliveries: " + successfulDeliveries);
        System.out.println("Unserved Buildings: " + unservedBuildings);
    }


}
