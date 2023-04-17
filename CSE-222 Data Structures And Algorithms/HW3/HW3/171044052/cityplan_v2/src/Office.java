public class Office extends Building{

    String owner;
    String jobTypes;

    /**
     * office class inherits from building class
     * focusOnBuilding prints jobTypes in office
     */

    Office(){

        this(0,0,0,-1,"","");
    }

    /**
     *
     * @param position hides buildings start position
     * @param length hides buildings length
     * @param height hides buildings height
     * @param type hides type of building
     * @param jobType hides job types in office
     * @param owner hides offices owner
     */

    Office(int position,int length,int height,int type,String jobType,String owner){

        super(position,length,height,type);
        this.jobTypes=jobType;
        this.owner=owner;
    }

    @Override
    public void focusOnBuilding (){

        System.out.println("The office's job types are: " +jobTypes);
    }
}
