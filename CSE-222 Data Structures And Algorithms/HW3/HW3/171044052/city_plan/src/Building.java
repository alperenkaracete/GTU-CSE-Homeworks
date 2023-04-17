public class Building {

    private int position;
    private int length;
    private int height;
    private int type;

    /**
     * this is the main class,all other classes inherits there
     * getPosition() return position
     * getLength() return length
     * getHeight() return height
     * getType() return type
     * focusOnBuilding() prints an attritubute for a building.It changes in every building
     */


    Building(){
        this(0,0,0,-1);
    };

    /**
     *
     * @param position hides buildings start position
     * @param length hides buildings length
     * @param height hides buildings height
     * @param type hides type of building
     */
    Building(int position,int length,int height,int type){

        this.position=position;
        this.length=length;
        this.height=height;
        this.type=type;
    }

    public int getPosition(){

        return position;
    }


    public int getLength(){

        return length;
    }

    public int getHeight(){

        return height;
    }

    public int getType(){

        return type;
    }

    public void focusOnBuilding (){

        System.out.println("Focus on different types of buildings");
    }
}

