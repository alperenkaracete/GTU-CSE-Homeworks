public class Vertex {

    public String label;
    public double weight;
    String key = null;
    String value = null;


    /**
     *
     * @param label ID of Vertex
     * @param weight Weight of Vertex
     */
    Vertex(String label,double weight){

        this.label = label;
        this.weight = weight;

    }

    void setVertexKeyValue (String key,String value){

        this.key = key;
        this.value = value;
    }
}
