import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;


public class IOfile {

    public static String fileName = "example.txt";
    public static String directory = "C:\\Users\\Akin Korkmaz\\IdeaProjects\\Input Output Streams\\src";
    public static String filePath = directory + "\\" + fileName;
    public static File example = new File(filePath);
    public static String[] names = {"Josephine ", "Robert " , "Aladdin ", "Fred ", "George "};

    public static void main(String[] args) {

        // this try catch block creates a file if the file doesn't exist
        // and puts the names String array into the text file
        try{
            if(!example.exists()){
                //creates the file if it doesn't exist
                FileOutputStream fos = new FileOutputStream(example);

                //writes the data byte by byte
                for (String name : names) {
                    byte[] x = name.getBytes();
                    fos.write(x);
                }

                //close Output stream
                fos.close();
            }
        }catch (IOException e){
            e.getStackTrace();
        }

        //this try catch block reads from the example.txt and prints out the contents if the file exists
        try{
            if(example.exists()){
                //if file exists creates a reader
                FileInputStream fis = new FileInputStream(example);

                //reads from the file byte by byte
                int x = fis.read();
                while (x != -1){
                    System.out.print((char)x);
                    x = fis.read();
                }
                //closes reader
                fis.close();
            }
        }catch(IOException e){
            e.getStackTrace();
        }
    }
}
