
public class Main{

    public static void main(String[] args) {

        driverFunc();
    }

    public static void driverFunc(){


        HashMapChain<String, Integer> hash = new HashMapChain<String, Integer>();
        hash.put("Alp",5);
        hash.put("pAl",7);
        hash.put("Apl",9);
        hash.put("ppP",10);
        hash.put("pPp",1);
        hash.put("ppl",21);

        hash.printTree();

        System.out.println("Get func:");
        System.out.println(hash.get("ppP"));
    }
}