class BinarySearchTree {

    static final int COUNT = 5;

    /* contains data,left and right*/
    class Node {
        int data;
        Node left, right;

        public Node(int item) {
            data = item;
            left = right = null;
        }
    }

    // Root of binary search tree
    Node root;
    static int index; //for array index

    // Constructor
    BinarySearchTree() {
        root = null;
    }

    BinarySearchTree(int value) {
        root = new Node(value);
    }

    // cals recursive insert method
    void add(int key) {
        root = insertRecursive(root, key);
    }

    /* A recursive function to insert a new data in binary search tree */

    /**
     *
     * @param root root of binary search tree
     * @param data data value to insert
     * @return
     */
    Node insertRecursive(Node root, int data) {

        /* If the tree is empty,
           return a new node */
        if (root == null) {
            root = new Node(data);
            return root;
        }

        /* Otherwise, go left if data smaller root data, else go right */
        if (data < root.data)
            root.left = insertRecursive(root.left, data);
        else if (data > root.data)
            root.right = insertRecursive(root.right, data);

        /* return the (unchanged) node pointer */
        return root;
    }

    /**
     *
     * @param root root of binary search tree
     * @param spaceBetweenNodes space between nodes
     */
    public void printBinarySearchTree(Node root, int spaceBetweenNodes){
        if (root == null) {
            return;
        }

        spaceBetweenNodes += COUNT;

        printBinarySearchTree(root.right, spaceBetweenNodes);
        System.out.println();

        for (int i = COUNT; i < spaceBetweenNodes; i++) {
            System.out.print(' ');
        }

        System.out.print(root.data);

        printBinarySearchTree(root.left, spaceBetweenNodes);
    }

    /**
     *
     * @param root tree we want to copy
     * @param elements array we want to insert tree's elements
     */
    public void copyTheTree(Node root,int[] elements) //for copy tree from beginning the root with preorder traversal
    {
        if (root == null)
        {
            return;
        }
        elements[index]=root.data;
        index++;
        copyTheTree(root.left,elements);
        copyTheTree(root.right,elements);

    }
}