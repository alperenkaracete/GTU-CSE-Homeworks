import java.util.LinkedList;

/**
 *
 * @param <K> Key
 * @param <V> Value
 */
public class HashMapChain<K, V> implements KWHashMap<K, V> {


    private BinarySearchTree[] table;
    private static final int CAPACITY = 10;
    private double LOAD_THRESHOLD = 3.0;
    private int numKeys;

    public HashMapChain(){
        table = new BinarySearchTree[CAPACITY];
    }

    /**
     *
     * @param <K> Key
     * @param <V> Value
     */
    static class Entry<K, V>{

        private final K key;
        private V value;

        public Entry(K entryKey, V entryValue){
            this.key = entryKey;
            this.value = entryValue;
        }

        public K getKey(){
            return key;
        }

        public V getValue(){
            return value;
        }

        public V setValue(V val){
            V oldVal = value;
            value = val;
            return oldVal;
        }
    }

    /**
     *
     * @param key key
     * @return key objects value
     */
    public V get(Object key){
        int index = key.hashCode() % CAPACITY;
        V temp = null;
        BinarySearchTree tempTree = table[index];

        if(index < 0)
            index += CAPACITY;
        if(table[index].root.kv.getKey() == key)
            return (V) table[index].root.kv.getValue();

        while (tempTree.root.kv.getKey().hashCode() != key.hashCode() && tempTree.root!=null){

            if (tempTree.root.kv.getKey().hashCode()<key.hashCode() && tempTree.root!=null){

                if (tempTree.root.right!=null) {
                    tempTree.root = tempTree.root.right;
                    temp = (V) tempTree.root.kv.getValue();
                }

                else {
                    tempTree.root = tempTree.root.left;
                    temp = (V) tempTree.root.kv.getValue();
                }

            }
            if (tempTree.root.kv.getKey().hashCode()>key.hashCode() && tempTree.root!=null){

                if (tempTree.root.left!=null) {
                    tempTree.root = tempTree.root.left;
                    temp = (V) tempTree.root.kv.getValue();
                }

                else {
                    tempTree.root = tempTree.root.right;
                    temp = (V) tempTree.root.kv.getValue();
                }
            }
        }

        return temp;

        //return null;
    }

    /**
     * Puts  key and value to hash map
     * @param key key
     * @param value value
     * @return
     */
    public V put(K key, V value){
        int index = key.hashCode() % CAPACITY;

        Entry<K,V> temp = new Entry<K,V>(key,value);
        if(index < 0)
            index += table.length;

        if(table[index] == null){
            table[index] = new BinarySearchTree();
        }
        table[index].insert(temp);

        return null;
    }

    public V remove (K key){

        return null;
    }

    public boolean isEmpty (){

        return true;
    }

    /**
     * @return table length
     */
    public int size() {
        return table.length;
    }

    public void printTree(){

        for (int i=0; i < table.length ; i++){

            System.out.print(i + " ");
            if (table[i]!=null) {
                table[i].inorder();

            }
            else {

                System.out.print("null");
            }
            System.out.println("\n");
        }


    }
}