public class Main {

    public static void main(String[] args) {


        driverFunction();
    }

    public static void driverFunction (){

        Integer[] a= {3,6,2,7,5,1,4};
        BinarySearchTree firstBinarySearchTree,
        secondBinarySearchTree;
        AVLTree firstAVLTree,
        secondAVLTree;

        BinaryTree firstBinaryTree = new BinaryTree(new BinaryTree.Node(10));
        firstBinaryTree.root.right=new BinaryTree.Node(11);
        firstBinaryTree.root.right.right=new BinaryTree.Node(12);
        firstBinaryTree.root.right.right.right=new BinaryTree.Node(13);
        firstBinaryTree.root.right.right.right.right=new BinaryTree.Node(14);;
        firstBinaryTree.root.right.right.right.right.right=new BinaryTree.Node(15);
        firstBinaryTree.root.right.right.right.right.right.right=new BinaryTree.Node(16);

        BinaryTree secondBinaryTree = new BinaryTree(new BinaryTree.Node(10));
        secondBinaryTree.root.left=new BinaryTree.Node(11);
        secondBinaryTree.root.right=new BinaryTree.Node(12);
        secondBinaryTree.root.right.left=new BinaryTree.Node(13);
        secondBinaryTree.root.right.right=new BinaryTree.Node(14);;
        secondBinaryTree.root.right.right.left=new BinaryTree.Node(15);
        secondBinaryTree.root.right.right.right=new BinaryTree.Node(16);

        System.out.println("First Binary Tree Structure");
        firstBinaryTree.printBinaryTree(firstBinaryTree.root,0);

        firstBinarySearchTree=binaryTreeToBinarySearchTree(firstBinaryTree,a);
        System.out.println();

        System.out.println("First Binary Search Tree ");
        firstBinarySearchTree.printBinarySearchTree(firstBinarySearchTree.root,0);
        System.out.println();

        System.out.println("First AVL Tree ");
        firstAVLTree=binarySearchTreeToAVLTree(firstBinarySearchTree);
        firstAVLTree.printAVLTree(firstAVLTree.root, 0);
        System.out.println();

        System.out.println("Second Binary Tree Structure");
        secondBinaryTree.printBinaryTree(secondBinaryTree.root,0);
        System.out.println();


        secondBinarySearchTree=binaryTreeToBinarySearchTree(secondBinaryTree,a);
        System.out.println("Second Binary Search Tree ");

        secondBinarySearchTree.printBinarySearchTree(secondBinarySearchTree.root,0);
        System.out.println();

        System.out.println("Second AVL Tree ");
        secondAVLTree=binarySearchTreeToAVLTree(secondBinarySearchTree);
        secondAVLTree.printAVLTree(secondAVLTree.root, 0);
        System.out.println();



    }

    public static BinarySearchTree binaryTreeToBinarySearchTree(BinaryTree binaryTree,Integer[] elements){

        BinarySearchTree binarySearchTree = new BinarySearchTree();

        MergeSort.mergeSort(elements,elements.length); //Firstly I sorted array with merge sort

        BinaryTree.index=0;

        BinaryTree.makeBinaryTreeBinarySearchTreeWithArray(elements,binaryTree.root);
        BinaryTree.binaryTreeToBinarySearchTree(binaryTree.root,binarySearchTree);

        return binarySearchTree;
    }

    public static AVLTree binarySearchTreeToAVLTree(BinarySearchTree binarySearchTree){

        AVLTree avlTree = new AVLTree();
        int[] elements = new int[7];

        binarySearchTree.copyTheTree(binarySearchTree.root,elements);

        BinarySearchTree.index=0;

        for (int i=0;i<7;i++){

            avlTree.root=avlTree.insert(avlTree.root,elements[i]);
        }

        return avlTree;
    }
}
