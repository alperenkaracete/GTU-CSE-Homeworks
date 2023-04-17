public interface DynamicGraph extends Graph {


    public Vertex newVertex (String label, double weight);

    /**
     *
     * @param newVertex new vertex
     * @return true or false
     */
    public boolean addVertex (Vertex newVertex);

    /**
     *
     * @param vertexID1 first vertex id
     * @param vertexID2 second vertex id
     * @param weight weight of edge
     */
    public void addEdge (int vertexID1, int vertexID2, double weight);

    /**
     *
     * @param vertexID1 first vertex id
     * @param vertexID2 second vertex id
     */
    public void removeEdge (int vertexID1, int vertexID2);

    /**
     *
     * @param vertexID vertex id to remove
     */
    public void removeVertex (int vertexID);

    /**
     *
     * @param label vertex label to remove
     */
    public void removeVertex (String label);

    /**
     *
     * @param key key for filter
     * @param filter value for filter
     * @return return sub graph whic contains key and value
     */
    public MyGraph filterVertices (String key, String filter);

    public void exportMatrix();

    public void printGraph();
}
