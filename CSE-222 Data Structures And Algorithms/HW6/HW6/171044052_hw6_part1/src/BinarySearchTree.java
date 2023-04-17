
/**
 *
 * @param <K> Key
 * @param <V> Value
 */
class BinarySearchTree<K,V> {


    static class Node {
        HashMapChain.Entry kv;
        Node left, right;

        public Node(HashMapChain.Entry item) {
            kv = item;
            left = right = null;
        }
    }

    Node root;


    BinarySearchTree() {
        root = null;
    }

    /**
     *
     * @param value V value
     */
    BinarySearchTree(HashMapChain.Entry value) {
        root = new Node(value);
    }

    /**
     *
     * @param key Key
     */
    void insert(HashMapChain.Entry key) {
        root = insertRec(root, key);
    }


    /**
     *
     * @param root root node
     * @param key Key
     * @return return root
     */
    Node insertRec(Node root, HashMapChain.Entry key) {

        if (root == null) {
            root = new Node(key);
            return root;
        }

        if (key.hashCode() < root.kv.getKey().hashCode())
            root.left = insertRec(root.left, key);
        else if (key.hashCode() > root.kv.getKey().hashCode())
            root.right = insertRec(root.right, key);

        return root;
    }

    /**
     *
     */
    void inorder() {
        inorderRec(root);
    }

    /**
     *
     * @param root root node
     */
    void inorderRec(Node root) {
        if (root != null) {
            inorderRec(root.left);
            System.out.print(root.kv.getValue() + " ");
            inorderRec(root.right);
        }
    }


}