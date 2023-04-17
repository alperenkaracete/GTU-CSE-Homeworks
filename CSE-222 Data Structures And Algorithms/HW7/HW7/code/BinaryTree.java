import java.io.Serializable;

/**
 * Class for a binary tree that stores type E objects.
 * @param <E> Generic type
 */
public class BinaryTree<E> implements Serializable {
    /**
     * The root of the binary tree
     */
    protected Node<E> root;
    static int index;
    static final int COUNT = 5;

    /**
     * Default constructor, assign null to root
     */
    public BinaryTree() {
        root = null;
    }

    /**
     * The constructor that takes a Node as a parameter is a protected constructor.
     * @param root The node as a root
     */
    protected BinaryTree(Node<E> root) {
        this.root = root;
    }


    /**
     *
     * @param data data to insert
     * @param leftTree left subtree of binary tree
     * @param rightTree right subtree of binary tree
     */
    public BinaryTree(E data, BinaryTree<E> leftTree, BinaryTree<E> rightTree) {
        root = new Node<>(data);
        if (leftTree != null) {
            root.left = leftTree.root;
        } else {
            root.left = null;
        }
        if (rightTree != null) {
            root.right = rightTree.root;
        } else {
            root.right = null;
        }
    }

    /** Class to encapsulate a tree node. */
    protected static class Node<E> implements Serializable {
        /** The information stored in this node. */
        protected E data;
        /** Reference to the left child. */
        protected Node<E> left;
        /** Reference to the right child. */
        protected Node<E> right;

        /** Depth of node */
        protected int depth;
        /**
         * Construct a node with given data and no children.
         * @param data The data to store in this node
         */
        public Node(E data) {
            this.data = data;
            left = null;
            right = null;
        }


    }

    /**
     *
     * @param arr sorted elements to insert binary tree
     * @param root root of binary tree
     */
    public static void makeBinaryTreeBinarySearchTreeWithArray(Integer[] arr, Node root) //I used inorder traversal method sorting to make binary tree to binary search tree with sorted array.
    {
        // Base Case
        if (root == null)
            return;

        /* first update the left subtree */
        makeBinaryTreeBinarySearchTreeWithArray(arr, root.left);

        /* Now update root's data and increment index */
        root.data = arr[index];

        index++;

        /* finally update the right subtree */
        makeBinaryTreeBinarySearchTreeWithArray(arr, root.right);
    }

    /**
     *
     * @param node root of binary tree to copy binary search tree
     * @param binarySearchTree binary search tree which copied from binary tree
     */
    public static void binaryTreeToBinarySearchTree(Node node, BinarySearchTree binarySearchTree) { //Then I used preorder traversal method to copy binary tree to binary search tree
        if (node == null) {
            return;

        }
        binarySearchTree.add((Integer) node.data);
        binaryTreeToBinarySearchTree(node.left,binarySearchTree);
        binaryTreeToBinarySearchTree(node.right,binarySearchTree);

    }

    /**
     *
     * @param root root of binary tree
     * @param spaceBetweenNodes space between nodes
     */
    public void printBinaryTree(Node root, int spaceBetweenNodes){
        if (root == null) {
            return;
        }

        spaceBetweenNodes += COUNT;

        printBinaryTree(root.right, spaceBetweenNodes);
        System.out.println();

        for (int i = COUNT; i < spaceBetweenNodes; i++) {
            System.out.print(' ');
        }

        System.out.print(root.data);

        printBinaryTree(root.left, spaceBetweenNodes);
    }
}