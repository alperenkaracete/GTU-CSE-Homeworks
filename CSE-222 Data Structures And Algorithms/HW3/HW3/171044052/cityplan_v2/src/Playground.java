public class Playground extends Building{

    Playground(){

        this(0,0,0,-1);
    }

    /**
     *
     * @param position hides building start position
     * @param length hides buildings length
     * @param height hides buildings height
     * @param type hides buildings type
     *             focusOnBuilding prints length
     */

    Playground(int position,int length,int height,int type){

        super(position, length, height,type);
    }

    @Override
    public void focusOnBuilding() {

        System.out.println("Length of playground is: " + this.getLength());
    }
}
