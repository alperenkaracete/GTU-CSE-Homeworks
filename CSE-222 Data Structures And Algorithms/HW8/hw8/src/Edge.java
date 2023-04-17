import java.util.Iterator;

public class Edge {

    public int source;
    public int destination;

    /***
     * Constructor of edge class.
     * @param source    int source
     * @param destination   int destination
     */
    /**
     *
     * @param source source of edge
     * @param destination destination between vertex
     * @param weight weight of edge
     */
    public Edge(int source, int destination,double weight)
    {
        this.source = source;
        this.destination = destination;
    }

}