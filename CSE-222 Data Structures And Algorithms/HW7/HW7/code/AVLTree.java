public class AVLTree {

    class Node {

        int data,
        height;

        Node left,
        right;

        Node(int data) {
            this.data = data;
            height = 1;
        }
    }

    static final int COUNT = 5; //for printing tree

    Node root;

    // for getting height of node
    int getNodeHeight(Node node) {
        if (node == null)
            return 0;

        return node.height;
    }

    // for finding bigger number

    /**
     *
     * @param firstNumber first number to compare
     * @param secondNumber second number to compare
     * @return returns bigger number
     */
    int findBigger(int firstNumber, int secondNumber) {
        return Math.max(firstNumber, secondNumber);
    }

    /**
     *
     * @param node node we want to rotate
     * @return returns rotated node
     */
    Node rightRotate(Node node) { //Make node'sleftside root, node become the right side of node'sleft.nodesleft's right side becomes nodes left side.
        Node tempNodesLeftSide = node.left;
        Node tempNodesLeftsRightSide = tempNodesLeftSide.right;

        // Perform rotation
        tempNodesLeftSide.right = node;
        node.left = tempNodesLeftsRightSide;

        // Update heights
        node.height = findBigger(getNodeHeight(node.left), getNodeHeight(node.right)) + 1;
        tempNodesLeftSide.height = findBigger(getNodeHeight(tempNodesLeftSide.left), getNodeHeight(tempNodesLeftSide.right)) + 1;

        // Return new root
        return tempNodesLeftSide;
    }

    /**
     *
     * @param node node we want to rotate
     * @return returns rotated node
     */
    Node leftRotate(Node node) { //Makes node'srightside root, node becomes the left side of node'sright.node'sright'sleft becomes nodesright side.

        Node tempNodesRightSide = node.right; // hiding nodes in temp variables
        Node tempNodesRightSideLeftSide = tempNodesRightSide.left;

        //make rotating
        tempNodesRightSide.left = node;
        node.right = tempNodesRightSideLeftSide;

        //  update height of nodes
        node.height = findBigger(getNodeHeight(node.left), getNodeHeight(node.right)) + 1;
        tempNodesRightSide.height = findBigger(getNodeHeight(tempNodesRightSide.left), getNodeHeight(tempNodesRightSide.right)) + 1;

        // return new root
        return tempNodesRightSide;
    }

    // calculating balance factor for node with subtracting from nodes left height to nodes right height.
    int getBalance(Node node) { // if balance -1,0 or 1 there is no problem.But if it is smaller than -1 then right side's height bigger than left side
        if (node == null)  //so we must rotate to left.If balance bigger than 1 then left side's height bigger than right side.So we must rotate tree to right.
            return 0;

        return getNodeHeight(node.left) - getNodeHeight(node.right);
    }

    /**
     *
     * @param node we want to insert data
     * @param data data value
     * @return returns node
     */
    Node insert(Node node, int data) {

        //* insert elements like binary search tree
        if (node == null)
            return (new Node(data));

        if (data < node.data)
            node.left = insert(node.left, data);
        else if (data > node.data)
            node.right = insert(node.right, data);
        else // Duplicate keys not allowed
            return node;

        /* Update height of ancestor node */
        node.height = 1 + findBigger(getNodeHeight(node.left),
                getNodeHeight(node.right));

        /* 3. Get the balance factor ancestor
              node to check if node became
              unbalanced */
        int balance = getBalance(node); //check balance

        // If node becomes unbalanced, then there are 4 cases.These are

        //Left Left Case
        if (balance > 1 && data < node.left.data) // if balance -1,0 or 1 there is no problem. If balance bigger than 1 then left side's height bigger than right side.
            return rightRotate(node); //So we must rotate tree to right.

        // Right Right Case
        if (balance < -1 && data > node.right.data) // if balance -1,0 or 1 there is no problem.But if it is smaller then -1 then right side's height bigger than left side
            return leftRotate(node); //so we must rotate to left.

        // Left Right Case //In this case we first rotate left then rotate right
        if (balance > 1 && data > node.left.data) {
            node.left = leftRotate(node.left);
            return rightRotate(node);
        }

        // Right Left Case
        if (balance < -1 && data < node.right.data) {   //In this case we first rotate right then rotate left
            node.right = rightRotate(node.right);
            return leftRotate(node);
        }

        /* return the unchanged node pointer */
        return node;
    }

    public void printAVLTree(Node root, int spaceBetweenNodes){

        if (root == null) {
            return;
        }

        spaceBetweenNodes += COUNT;

        printAVLTree(root.right, spaceBetweenNodes);
        System.out.println();

        for (int i = COUNT; i < spaceBetweenNodes; i++) {
            System.out.print(' ');
        }

        System.out.print(root.data);

        printAVLTree(root.left, spaceBetweenNodes);
    }
}
