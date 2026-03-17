import java.io.File;
import java.io.FileNotFoundException;
import java.util.*;

public class CampusNetworkPlanner3 {

    private final int numConnections;
    private final String fileName;

    public String[][] connections;

    public CampusNetworkPlanner3(int numConnections, String fileName) {
        this.numConnections = numConnections;
        this.fileName = fileName;
    }

    public String buildNetwork() {
        // read exactly numConnections non-empty lines
        connections = new String[numConnections][3];
        int read = 0;
        try (Scanner sc = new Scanner(new File(fileName))) {
            while (read < numConnections && sc.hasNextLine()) {
                String line = sc.nextLine().trim();
                if (line.isEmpty()) continue;
                String[] t = line.split("\\s+");
                if (t.length < 3) continue; // skip malformed line
                connections[read][0] = t[0];
                connections[read][1] = t[1];
                connections[read][2] = t[2];
                read++;
            }
        } catch (FileNotFoundException e) {
            String msg = "Selected Connections:\n\nTotal Cost: $0";
            System.out.println(msg);
            return msg;
        }

        // map campus -> id
        Map<String, Integer> id = new HashMap<>();
        int nextId = 0;
        for (int i = 0; i < read; i++) {
            String a = connections[i][0], b = connections[i][1];
            if (!id.containsKey(a)) id.put(a, nextId++);
            if (!id.containsKey(b)) id.put(b, nextId++);
        }
        int V = nextId;

        // edge list
        class Edge {
            String a, b;
            int u, v, w;
            Edge(String a, String b, int w) {
                this.a = a; this.b = b; this.w = w;
                this.u = id.get(a); this.v = id.get(b);
            }
        }
        List<Edge> edges = new ArrayList<>(read);
        for (int i = 0; i < read; i++) {
            edges.add(new Edge(
                    connections[i][0],
                    connections[i][1],
                    Integer.parseInt(connections[i][2])
            ));
        }

        // Kruskal: sort by cost
        edges.sort(Comparator.comparingInt(e -> e.w));

        // union-find
        int[] parent = new int[V];
        int[] rank = new int[V];
        for (int i = 0; i < V; i++) { parent[i] = i; rank[i] = 0; }

        List<Edge> chosen = new ArrayList<>();
        int total = 0;

        for (Edge e : edges) {
            int ru = find(parent, e.u);
            int rv = find(parent, e.v);
            if (ru != rv) {
                union(parent, rank, ru, rv);
                chosen.add(e);
                total += e.w;
                if (chosen.size() == V - 1) break;
            }
        }

        // sort by lex A-Z
        chosen.sort((x, y) -> {
            String xa = x.a, xb = x.b;
            if (xa.compareTo(xb) > 0) { String t = xa; xa = xb; xb = t; }
            String ya = y.a, yb = y.b;
            if (ya.compareTo(yb) > 0) { String t = ya; ya = yb; yb = t; }
            int c = xa.compareTo(ya);
            return c != 0 ? c : xb.compareTo(yb);
        });

        //format
        StringBuilder sb = new StringBuilder();
        for (Edge e : chosen) {
            String A = e.a, B = e.b;
            if (A.compareTo(B) > 0) { String t = A; A = B; B = t; }
            sb.append(A).append("---").append(B).append(" $").append(e.w).append("\n");
        }
        sb.append("\nTotal Cost: $").append(total);

        String out = sb.toString();
        return out;
    }

    private int find(int[] parent, int x) {
        if (parent[x] != x) parent[x] = find(parent, parent[x]);
        return parent[x];
    }

    private void union(int[] parent, int[] rank, int x, int y) {
        int rx = find(parent, x), ry = find(parent, y);
        if (rx == ry) return;
        if (rank[rx] < rank[ry]) parent[rx] = ry;
        else if (rank[rx] > rank[ry]) parent[ry] = rx;
        else { parent[ry] = rx; rank[rx]++; }
    }
}
