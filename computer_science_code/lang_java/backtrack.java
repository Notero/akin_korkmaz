import java.util.ArrayList;
import java.util.Arrays;

public class EscapeRoomDecoder {

    public ArrayList<String> generatePasswords(String tiles) {

        ArrayList<String> listOfAllPasswords = new ArrayList<>();

        if(tiles == null || tiles.length() == 0){
            return listOfAllPasswords;
        }

        char[] chars = tiles.toCharArray();
        Arrays.sort(chars);

        boolean[] visited = new boolean[chars.length];
        StringBuilder factory = new StringBuilder();

        // Backtracking over permutations of ALL lengths (2..n)
        backtrack(chars, visited, factory, listOfAllPasswords);

        // Print summary + all passwords
        System.out.println("Total valid passwords: " + listOfAllPasswords.size());

        return listOfAllPasswords;
    }

    private void backtrack(char[] chars, boolean[] visited, StringBuilder sb, ArrayList<String> out) {
        if (sb.length() >= 2 && !isPalindrome(sb)) {
            out.add(sb.toString());
        }

        for (int i = 0; i < chars.length; i++) {
            //skip if visited
            if (visited[i]) continue;
            //recursion level filter
            if (i > 0 && chars[i] == chars[i - 1] && !visited[i - 1]) continue;

            // choose
            visited[i] = true;
            sb.append(chars[i]);

            // recurse
            backtrack(chars, visited, sb, out);

            // undo
            sb.deleteCharAt(sb.length() - 1);
            visited[i] = false;
        }
    }

    public Boolean isPalindrome(StringBuilder sb) {
        //get indexes
        int left = 0, right = sb.length() - 1;
        //compare each end logic
        while (left < right) {
            if (sb.charAt(left) != sb.charAt(right)) return false;
            left++;
            right--;
        }
        return true;
    }

}
