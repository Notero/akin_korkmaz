
import java.util.*;


public class word_frequency_string {

    // Tokenizer function to split paragraph into words
    // Tokenizer: keep letters, downcase, split on whitespace
    public static String[] tokenize(String paragraph) {
        String cleaned = paragraph.toLowerCase().replaceAll("[^a-z]+", " ").trim();
        if (cleaned.isEmpty()) return new String[0];
        return cleaned.split("\\s+");
    }

    // Function to count word frequencies
    public static void countWords(String[] words, HashMap<String, Integer> map) {
        for (String word : words) {
            map.put(word, map.getOrDefault(word, 0) + 1);
        }
    }

    // Function to print word frequencies
    public static void printFrequencies(HashMap<String, Integer> map) {
        for (String word : map.keySet()) {
            System.out.println(word + " " + map.get(word));
        }
    }

    // Function to answer questions about the map
    public static void answerQuestions(HashMap<String, Integer> map) {
        map.put("word",1);
        map.get("word");
        map.remove("word");
        int len = map.size();
        boolean mape = map.isEmpty();
    }

    public static void main(String[] args) {
        String paragraph1 = "Java is a versatile language. Java is used in web development, mobile apps, and enterprise systems. Many developers love Java for its portability and performance.";
        String paragraph2 = "HashTables are powerful. They allow fast access to data. Java HashMap is a popular implementation. Developers use HashTables to store and retrieve information efficiently.";

        HashMap<String, Integer> wordFreq = new HashMap<>();

        // Process paragraph 1
        String[] words1 = tokenize(paragraph1);
        countWords(words1, wordFreq);
        printFrequencies(wordFreq);
        answerQuestions(wordFreq);

        // Clear map and process paragraph 2
        wordFreq.clear();
        String[] words2 = tokenize(paragraph2);
        countWords(words2, wordFreq);
        printFrequencies(wordFreq);
        answerQuestions(wordFreq);
    }
}
