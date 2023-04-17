public class Main {

    public static void main(String[] args) {

        driverFunction();
    }

    public static void driverFunction(){

        MyGraph graph = new MyGraph();

        graph.addVertex(new Vertex("berke",5));
        graph.addVertex(new Vertex("alperen",5));
        graph.addVertex(new Vertex("abdullah",5));
        graph.addVertex(new Vertex("fazıl",5));
        graph.addVertex(new Vertex("burak",5));

        Vertex tempVertex;
        tempVertex = graph.getVertex(0);
        tempVertex.setVertexKeyValue("alp","1");
        tempVertex = graph.getVertex(1);
        tempVertex.setVertexKeyValue("kalp","2");
        tempVertex = graph.getVertex(2);
        tempVertex.setVertexKeyValue("lalp","3");
        graph.getVertex(0);
        tempVertex.setVertexKeyValue("alp","1");
        graph.getVertex(0);
        tempVertex.setVertexKeyValue("alp","1");
        graph.printGraph();
        graph.addEdge(0,1,5);
        graph.addEdge(0,2,5);
        graph.addEdge(1,2,5);
        graph.printGraph();

        graph.removeEdge(0,1);
        graph.removeVertex(2);
        graph.removeVertex("tura");

        graph.exportMatrix();

        MyGraph temp = graph.filterVertices("kalp","2");
        temp.printGraph();
        System.out.println(graph.toString());


        graph.printGraph();


    }
}
