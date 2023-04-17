public class Market extends Building{

    String owner;
    String openTime;
    String closeTime;

    /**
     * market class inherits from building class
     * focusOnBuilding prints close time
     */

    Market(){

        this(0,0,0,-1,"","","");
    }

    /**
     *
     * @param position hides buildings start position
     * @param length hides buildings length
     * @param height hides buildings height
     * @param type hides type of building
     * @param owner hides markets owner
     * @param openTime hides markets open time
     * @param closeTime hides markets close time
     */

    Market(int position,int length,int height,int type,String owner,String openTime, String closeTime){

        super(position, length, height,type);
        this.owner=owner;
        this.openTime=openTime;
        this.closeTime=closeTime;
    }

    @Override
    public void focusOnBuilding (){

        System.out.println("The market is closing at: " +closeTime + "o'clock");
    }
}
