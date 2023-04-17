import java.util.*;

public class MyGraph implements DynamicGraph {

    private boolean adjMatrix[][] = null;
    int numberOfVertices=0;
    private List<Vertex>[] graph = new ArrayList[1];

    @Override
    public Vertex newVertex(String label, double weight) {

        return new Vertex(label,weight);
    }

    @Override
    public boolean addVertex(Vertex newVertex) {

        if (numberOfVertices==0){

            graph[0] = new ArrayList<Vertex>();
            graph[0].add(newVertex);
            numberOfVertices++;

            return true;
        }

        else if (numberOfVertices==graph.length){

            List<Vertex> temp[] = new ArrayList[graph.length+1];
            for (int i=0;i<graph.length;i++){

                temp[i] = graph[i];
                if (graph[i].get(0).label== newVertex.label){

                    return false;
                }
            }
            graph = new ArrayList[temp.length];
            for (int i=0;i< temp.length;i++){

                graph[i] = temp[i];
            }
        }
        graph[numberOfVertices] = new ArrayList<Vertex>();
        graph[numberOfVertices].add(newVertex);
        numberOfVertices++;
        return true;
    }

    @Override
    public void addEdge(int vertexID1, int vertexID2, double weight) {

        if (vertexID1 >= graph.length || vertexID2 >= graph.length){

            System.out.println("Wrong Vertices");
        }

        else {
            if (graph[vertexID1].contains(graph[vertexID2].get(0))){
                System.out.println("This edge is already exist!");
            }

            else {
                graph[vertexID1].add(graph[vertexID2].get(0));
                graph[vertexID1].get(graph[vertexID1].size()-1).weight=weight;
                graph[vertexID2].add(graph[vertexID1].get(0));
                graph[vertexID2].get(graph[vertexID2].size()-1).weight=weight;
                System.out.println(("Edge Adding Successful"));
            }
        }
    }

    @Override
    public void removeEdge(int vertexID1, int vertexID2) {

        if (vertexID1 > graph.length || vertexID2 > graph.length){

            System.out.println("Wrong Vertices");
        }

        else {
            if (graph[vertexID2].contains(graph[vertexID1].get(0))){
                int tempValue = graph[vertexID1].indexOf(graph[vertexID2].get(0));
                int tempValue2 = graph[vertexID2].indexOf(graph[vertexID1].get(0));
                graph[vertexID1].remove(tempValue);
                graph[vertexID2].remove(tempValue2);

                System.out.println(("Removing Edge Successful"));

            }

            else {
                System.out.println(("Remove Failed because edge can not find"));
            }
        }
    }

    @Override
    public void removeVertex(int vertexID) {

        if (vertexID> graph.length){

            System.out.println("Wrong Vertices");
        }

        else {

            List<Vertex> temp[] = new ArrayList[graph.length-1];
            for (int i=0;i<temp.length;i++){

                if (i<vertexID)
                    temp[i] = graph[i];

                else
                    temp[i] = graph[i+1];

                if (i!=vertexID)
                    removeEdge(i,vertexID);

            }
                removeEdge(temp.length,vertexID); //for controlling last element
            numberOfVertices--;
            graph = new ArrayList[numberOfVertices];

            for (int i=0;i< temp.length;i++) {

                graph[i] = temp[i];
            }

            System.out.println("Deleting Vertex Successful!");
        }
    }

    @Override
    public void removeVertex(String label) {

        for (int i=0;i<graph.length;i++){

            if (graph[i].get(0).label==label){

                removeVertex(i);
            }
        }
    }

    /*Filter vertices*/
    @Override
    public MyGraph filterVertices(String key, String filter) {

        int count=0,count2=0;
        boolean flag=false;
        //List<Vertex>[] subGraph.graph[i]= new ArrayList[graph.length];
        MyGraph subGraph = new MyGraph();
        subGraph.graph= new ArrayList[graph.length];

        for (int i=0;i<graph.length;i++){ /*copy graph to subgraph.graph*/

            subGraph.graph[i] = new ArrayList<>(graph[i].size());
            for (int j=0;j<graph[i].size();j++)

                subGraph.graph[i].add(graph[i].get(j));

            if (graph[i].get(0).key== key && graph[i].get(0).value==filter){

                count=i;
            }

        }
        subGraph.numberOfVertices=numberOfVertices;
        for (int i=0;i<count;i++){

        subGraph.removeVertex(i); /*remove vertexes there is not exis in sub graph this operation deletes edges too.*/
        }


        return subGraph;
    }

    /*Allocate matrix*/
    @Override
    public void exportMatrix() {

        if (graph.length<2){

            System.out.println("Graph is too small!");
        }

        else {
            adjMatrix = new boolean[graph.length][graph.length];
            for (int i = 0; i < graph.length; i++) {

                for (int j = 0; j < graph[i].size(); j++) {

                    if (graph[i].contains(graph[j].get(0))) {

                        adjMatrix[i][j] = true;
                        adjMatrix[j][i] = true;
                    } else {

                        adjMatrix[i][j] = false;
                        adjMatrix[j][i] = false;
                    }

                }
            }
        }

    }

    /** TUrn matrix to string*/
    public String toString() {
        StringBuilder matrixString = new StringBuilder();
        for (int i = 0; i < numberOfVertices; i++) {
            matrixString.append(i + ": ");
            for (boolean j : adjMatrix[i]) {
                matrixString.append((j ? 1 : 0) + " ");
            }
            matrixString.append("\n");
        }
        return matrixString.toString();
    }

    @Override
    public void printGraph() {

        for (int i=0;i<graph.length;i++) {

            for (int j=0;j< graph[i].size();j++) {
                System.out.print(graph[i].get(j).label);
                if (j+1!=graph[i].size())
                    System.out.print("->");
            }
            System.out.println();
        }
    }

    @Override
    public int getNumV() {
        return 0;
    }

    @Override
    public boolean isDirected() {
        return false;
    }

    @Override
    public void insert(Edge edge) {

    }

    @Override
    public boolean isEdge(int source, int dest) {
        return false;
    }

    @Override
    public Edge getEdge(int source, int dest) {
        return null;
    }

    public Vertex getVertex (int vertexID){

        if (vertexID>graph.length){

            System.out.println("Wrong index");
        }

        else {

            return graph[vertexID].get(0);
        }

        return new Vertex(null,0);
    }


}
