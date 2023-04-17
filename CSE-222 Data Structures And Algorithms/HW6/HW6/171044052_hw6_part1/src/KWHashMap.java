public interface KWHashMap<K, V>{

    int size();
    V get(Object key);
    boolean isEmpty();
    V put(K key, V value);
    V remove (K key);

}