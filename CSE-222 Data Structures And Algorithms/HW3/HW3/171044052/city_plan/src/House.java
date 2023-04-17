public class House extends Building{

    private int roomNumber;
    private String color;
    private String owner;

    /**
     * house class inherits from building class
     * focusOnBuilding prints owner
     */

    House(){

        this(0,0,0,-1,0,"","");
    }

    /**
     *
     * @param position hides buildings start position
     * @param length hides buildings length
     * @param height hides buildings height
     * @param type hides type of building
     * @param roomNumber hides room amount
     * @param color hides house's color
     * @param owner hides house's owner
     */

    House(int position,int length,int height,int type,int roomNumber,String color,String owner){

        super(position, length, height,type);
        this.roomNumber=roomNumber;
        this.color=color;
        this.owner=owner;

    }

    @Override
    public void focusOnBuilding (){

        System.out.println("The house's owner is: " +owner);
    }

}
