import java.util.*;


public class CourseCombinations {

    public static class uniquePairs{
        String p1;
        String p2;

        public uniquePairs(String p1, String p2) {
            this.p1 = p1;
            this.p2 = p2;
        }
    }

    public static String[] tokenizer(String str){
        return str.split("\\s+");
    }

    public static void main(String[] args) {

        Scanner scanner = new Scanner(System.in);
        HashMap<String, List<String>> map = new HashMap<>();
        List<uniquePairs> pairs = new LinkedList<>();

        int n = Integer.parseInt(scanner.nextLine());

        for (int i = 0; i < n; i++){
            String[] tokens = tokenizer(scanner.nextLine());
            int tokenAmount = tokens.length;

            for(int j = 1; j < tokenAmount; j++){
                map.computeIfAbsent(tokens[j], k -> new ArrayList<>()).add(tokens[0]);
            }
        }

        for (String key : map.keySet()){
            calcPairs(map.get(key), pairs);
        }

        System.out.println(pairs.size());

        scanner.close();
    }

    //calculates the number of pairs in a list
    public static void calcPairs(List<String> list, List<uniquePairs> pairs) {
        int n = list.size();

        for(int i = 0; i < n; i++){
            for(int j = i + 1; j < n; j++){
                String a = list.get(i);
                String b = list.get(j);
                if (!doesItExist(pairs, a, b)) {
                    pairs.add(new uniquePairs(a, b));
                }
            }
        }
    }

    public static boolean doesItExist(List<uniquePairs> pairs, String a, String b) {
        if (a.equals(b)) return true; // skip self-pairs
        for (uniquePairs p : pairs) {
            if ( (a.equals(p.p1) && b.equals(p.p2)) ||
                    (a.equals(p.p2) && b.equals(p.p1)) ) {
                return true;
            }
        }
        return false;
    }

}
