import java.util.*;

public class Main {

    public static void main(String[] args) {


        driverFunction();
        Scanner sc= new Scanner(System.in);

        char choice; //for choice options
        int count=0,
        loopValue,
         addOrDelete, //add or delete choice
         streetLength,
         side, //determining which side to add or delete buildings
         buildingType,
        side1buildingNumber=0, //side1 total buildings
        side2buildingNumber=0, //side2 total buildings
        totalRemainingLength1, //in side 1 remaining length
        totalRemainingLength2;//in side 2 remaining length
        boolean control;
        LinkedList<Building> side1Buildings = new LinkedList<>(), //allocating both sides building list
                side2Buildings = new LinkedList<>();
        System.out.println("Please enter street length");
        while (!sc.hasNextInt()){ //controlling if input is integer

            System.out.println("Please enter a valid integer!");
            sc.next();
        }
        streetLength=sc.nextInt();
        sc.nextLine();
        totalRemainingLength1=streetLength+1;
        totalRemainingLength2=streetLength+1;
        LinkedList<List<Character>> streetSide1List = new LinkedList<>(), //total height=50
                streetSide2List = new LinkedList<>();
        for (int i=0;i<=52;i++){ //refilling list with spaces

            for (int j=0;j<=streetLength;j++){

                streetSide1List.add(new LinkedList<>());
                streetSide2List.add(new LinkedList<>());
                streetSide1List.get(j).add(i,' ');
                streetSide2List.get(j).add(i,' ');
            }
        }

        do{
            do {

                if (count > 0) {
                    System.out.println("You entered wrong input!Please enter a valid input");
                } else if (count == 0) {
                    System.out.println("Which mode do you want to use for program,Edit or view?");
                    System.out.println("For Edit press 'E',for View press 'V'.");
                }
                choice = sc.next().charAt(0);
                count++;
                if ((choice == 'E' || choice == 'e' || choice == 'V' || choice == 'v')) { //for edit or view mode
                    count = -1;
                }
            } while (!(choice == 'E' || choice == 'e' || choice == 'V' || choice == 'v'));

            if (choice == 'E' || choice == 'e') {

                count = 0;
                do {

                    if (count > 0) {
                        System.out.println("Wrong input!Please enter  1 or 2!");
                    } else if (count == 0) {

                        System.out.println("Do you want to add building or delete building?");
                        System.out.println("For add press 1,for delete press 2");
                    }
                    while (!sc.hasNextInt()) {

                        System.out.println("Wrong input!Please enter  1 or 2!");
                        sc.next();
                    }
                    addOrDelete = sc.nextInt();
                    count++;
                    if (addOrDelete == 1 || addOrDelete == 2) {

                        count = -1;
                    }
                } while (addOrDelete != 1 && addOrDelete != 2); //controlling inputs
                count = 0;
                sc.nextLine();
                if (addOrDelete == 1) {
                    do {

                        if (count == 0) {
                            System.out.println("Which side do you want to add?,Please enter 1 to side1,enter 2 to side 2");
                        } else if (count > 0) {

                            System.out.println("Wrong input!Please enter 1 or 2");
                        }
                        while (!sc.hasNextInt()) {
                            System.out.println("Wrong input!Please enter 1 or 2");
                            sc.next();
                        }
                        side = sc.nextInt();
                        count++;
                        if (side == 1 || side == 2) {

                            count = -1;
                        }
                    } while (side >= 3 || side <= 0); //selecting side to add or delete
                    count = 0;
                    if (side == 1) {

                        do {

                            if (count == 0) {

                                System.out.println("Which building do you want to add to street?"); //for add which building select
                                System.out.println("For house press 1");
                                System.out.println("For office press 2");
                                System.out.println("For playground press 3");
                                System.out.println("For market press 4");
                            } else if (count > 0) {

                                System.out.println("Please enter 1 or 2 or 3 or 4");
                            }
                            while (!sc.hasNextInt()) {
                                System.out.println("Please enter 1 or 2 or 3 or 4");
                                sc.next();
                            }
                            buildingType = sc.nextInt();
                            count++;
                            if (buildingType > 0 && buildingType < 5) {

                                count = -1;
                            }
                        } while (buildingType < 0 || buildingType > 5);
                        count = 0;
                        if (buildingType == 1) {

                            int position = 0, length = 0, height = 0, roomNumber = 0;
                            String color, owner;
                            do {
                                if (count == 0) {
                                    System.out.println("Please enter position it must be smaller than street size"); // if value bigger than street size retake value from user
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    position = sc.nextInt();
                                    if (position < streetLength)
                                        count++;
                                } else if (count == 1) {
                                    System.out.println("Please enter length, length + position must not be larger than street length"); // if length + position bigger than street retake length
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    length = sc.nextInt();
                                    if (length + position <= streetLength)
                                        count++;
                                } else if (count == 2) {
                                    System.out.println("Please enter height of building,height must be less than 51"); //height can't be bigger than 50
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    height = sc.nextInt();
                                    if (height <= 50) {
                                        count++;
                                    }
                                } else if (count == 3) {
                                    System.out.println("Please enter room number of house");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    roomNumber = sc.nextInt();
                                    count++;
                                }

                            } while (count < 4);
                            System.out.println("Please enter house's color");
                            sc.nextLine();
                            color = sc.nextLine();
                            System.out.println("Please enter house's owner");
                            owner = sc.nextLine();
                            House tempHouse = new House(position, length, height, 1, roomNumber, color, owner);
                            side1Buildings.add(tempHouse);
                            control = makeStreet(side1Buildings, tempHouse, side1buildingNumber);
                            if (control) {
                                side1buildingNumber++;
                                totalRemainingLength1 -= length;
                                drawStreet(streetSide1List, side1Buildings, streetLength,side1buildingNumber-1);
                            }
                        }
                        if (buildingType == 2) {

                            int position = 0, length = 0, height = 0;
                            String jobType, owner;
                            do {
                                if (count == 0) {
                                    System.out.println("Please enter position it must be smaller than street size");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    position = sc.nextInt();
                                    if (position < streetLength)
                                        count++;
                                } else if (count == 1) {
                                    System.out.println("Please enter length, length + position must not be larger than street length");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    length = sc.nextInt();
                                    if (length + position <= streetLength)
                                        count++;
                                } else if (count == 2) {
                                    System.out.println("Please enter height of building,height must be less than 51");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    height = sc.nextInt();
                                    if (height <= 51) {
                                        count++;
                                    }
                                }
                            } while (count < 3);
                            System.out.println("Please enter job types in office");
                            sc.nextLine();
                            jobType = sc.nextLine();
                            System.out.println("Please enter office's owner");
                            owner = sc.nextLine();
                            Office tempOffice = new Office(position, length, height, 2, jobType, owner);
                            side1Buildings.add(tempOffice);
                            control = makeStreet(side1Buildings, tempOffice, side1buildingNumber);
                            if (control) {

                                side1buildingNumber++;
                                totalRemainingLength1 -=  length;
                                drawStreet(streetSide1List, side1Buildings, streetLength,side1buildingNumber-1);
                            }
                        }
                        if (buildingType == 3) {

                            int position = 0, length = 0, height = 0;
                            do {
                                if (count == 0) {
                                    System.out.println("Please enter position it must be smaller than street size");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    position = sc.nextInt();
                                    if (position < streetLength)
                                        count++;
                                } else if (count == 1) {
                                    System.out.println("Please enter length, length + position must not be larger than street length");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    length = sc.nextInt();
                                    if (length + position <= streetLength)
                                        count++;
                                } else if (count == 2) {
                                    System.out.println("Please enter height of playground,height must be less than 51");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    height = sc.nextInt();
                                    if (height <= 50) {
                                        count++;
                                    }
                                }
                            } while (count < 3);
                            Playground tempPlayground = new Playground(position, length, height, 3);
                            side1Buildings.add(tempPlayground);
                            control = makeStreet(side1Buildings, tempPlayground, side1buildingNumber);
                            if (control) {
                                side1buildingNumber++;
                                totalRemainingLength1 -= length;
                                drawStreet(streetSide1List, side1Buildings, streetLength, side1buildingNumber-1);
                            }
                        }
                        if (buildingType == 4) {

                            int position = 0, length = 0, height = 0;
                            String owner, openTime, closeTime;
                            do {
                                if (count == 0) {
                                    System.out.println("Please enter position it must be smaller than street size");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    position = sc.nextInt();
                                    if (position < streetLength)
                                        count++;
                                } else if (count == 1) {
                                    System.out.println("Please enter length, length + position must not be larger than street length");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    length = sc.nextInt();
                                    if (length + position <= streetLength)
                                        count++;
                                } else if (count == 2) {
                                    System.out.println("Please enter height of market,height must be less than 51");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    height = sc.nextInt();
                                    if (height <= 50) {
                                        count++;
                                    }
                                }
                            } while (count < 3);
                            System.out.println("Please enter owner of market");
                            sc.nextLine();
                            owner = sc.nextLine();
                            System.out.println("Please enter markets open time");
                            openTime = sc.nextLine();
                            System.out.println("Please enter markets close time");
                            closeTime = sc.nextLine();
                            Market tempMarket = new Market(position, length, height, 4, owner, openTime, closeTime);
                            side1Buildings.add(tempMarket);
                            control = makeStreet(side1Buildings, tempMarket, side1buildingNumber); // if building can be placed that location then increases building number on that side and draw it to street
                            if (control) {
                                side1buildingNumber++;
                                totalRemainingLength1 -= length;
                                drawStreet(streetSide1List, side1Buildings, streetLength, side1buildingNumber-1);
                            }
                        }
                    }

                    if (side == 2) { //for second side same processes

                        do {

                            if (count == 0) {

                                System.out.println("Which building do you want to add to street?");
                                System.out.println("For house press 1");
                                System.out.println("For office press 2");
                                System.out.println("For playground press 3");
                                System.out.println("For market press 4");
                            } else if (count > 0) {

                                System.out.println("Please enter 1 or 2 or 3 or 4");
                            }
                            while (!sc.hasNextInt()) {
                                System.out.println("Please enter 1 or 2 or 3 or 4");
                                sc.next();
                            }
                            buildingType = sc.nextInt();
                            count++;
                            if (buildingType > 0 && buildingType < 5) {

                                count = -1;
                            }
                        } while (buildingType < 0 || buildingType > 5);
                        count = 0;
                        if (buildingType == 1) {

                            int position = 0, length = 0, height = 0, roomNumber = 0;
                            String color, owner;
                            do {
                                if (count == 0) {
                                    System.out.println("Please enter position it must be smaller than street size");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    position = sc.nextInt();
                                    if (position < streetLength)
                                        count++;
                                } else if (count == 1) {
                                    System.out.println("Please enter length, length + position must not be larger than street length");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    length = sc.nextInt();
                                    if (length + position <= streetLength)
                                        count++;
                                } else if (count == 2) {
                                    System.out.println("Please enter height of building,height must be less than 51");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    height = sc.nextInt();
                                    if (height <= 50) {
                                        count++;
                                    }
                                } else if (count == 3) {
                                    System.out.println("Please enter room number of house");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    roomNumber = sc.nextInt();
                                    count++;
                                }
                            } while (count < 4);
                            System.out.println("Please enter house's color");
                            sc.nextLine();
                            color = sc.nextLine();
                            System.out.println("Please enter house's owner");
                            owner = sc.nextLine();
                            House tempHouse = new House(position, length, height, 1, roomNumber, color, owner);
                            side2Buildings.add(tempHouse);
                            control = makeStreet(side2Buildings, tempHouse, side2buildingNumber);
                            if (control) {
                                side2buildingNumber++;
                                totalRemainingLength2 -= length;
                                drawStreet(streetSide2List, side2Buildings, streetLength, side2buildingNumber-1);
                            }
                        }
                        if (buildingType == 2) {

                            int position = 0, length = 0, height = 0;
                            String jobType, owner;
                            do {
                                if (count == 0) {
                                    System.out.println("Please enter position it must be smaller than street size");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    position = sc.nextInt();
                                    if (position < streetLength)
                                        count++;
                                } else if (count == 1) {
                                    System.out.println("Please enter length, length + position must not be larger than street length");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    length = sc.nextInt();
                                    if (length + position <= streetLength)
                                        count++;
                                } else if (count == 2) {
                                    System.out.println("Please enter height of building,height must be less than 51");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    height = sc.nextInt();
                                    if (height <= 50) {
                                        count++;
                                    }
                                }
                            } while (count < 3);
                            System.out.println("Please enter job types in office");
                            sc.nextLine();
                            jobType = sc.nextLine();
                            System.out.println("Please enter office's owner");
                            owner = sc.nextLine();
                            Office tempOffice = new Office(position, length, height, 2, jobType, owner);
                            side2Buildings.add(tempOffice);
                            control = makeStreet(side2Buildings, tempOffice, side2buildingNumber);
                            if (control) {
                                side2buildingNumber++;
                                totalRemainingLength2 -= length;
                                drawStreet(streetSide2List, side2Buildings, streetLength, side2buildingNumber-1);
                            }
                        }
                        if (buildingType == 3) {

                            int position = 0, length = 0, height = 0;
                            do {
                                if (count == 0) {
                                    System.out.println("Please enter position it must be smaller than street size");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    position = sc.nextInt();
                                    if (position < streetLength)
                                        count++;
                                } else if (count == 1) {
                                    System.out.println("Please enter length, length + position must not be larger than street length");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    length = sc.nextInt();
                                    if (length + position <= streetLength)
                                        count++;
                                } else if (count == 2) {
                                    System.out.println("Please enter height of playground,height must be less than 51");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    height = sc.nextInt();
                                    if (height <= 50) {
                                        count++;
                                    }
                                }
                            } while (count < 3);
                            Playground tempPlayground = new Playground(position, length, height, 3);
                            side2Buildings.add(tempPlayground);
                            control = makeStreet(side2Buildings, tempPlayground, side2buildingNumber);
                            if (control) {
                                side2buildingNumber++;
                                totalRemainingLength2 -= length;
                                drawStreet(streetSide2List, side2Buildings, streetLength,side2buildingNumber-1);
                            }
                        }
                        if (buildingType == 4) {

                            int position = 0, length = 0, height = 0;
                            String owner, openTime, closeTime;
                            do {
                                if (count == 0) {
                                    System.out.println("Please enter position it must be smaller than street size");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    position = sc.nextInt();
                                    if (position < streetLength)
                                        count++;
                                } else if (count == 1) {
                                    System.out.println("Please enter length, length + position must not be larger than street length");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    length = sc.nextInt();
                                    if (length + position <= streetLength)
                                        count++;
                                } else if (count == 2) {
                                    System.out.println("Please enter height of market,height must be less than 51");
                                    while (!sc.hasNextInt()) {
                                        System.out.println("Please enter a valid integer");
                                        sc.next();
                                    }
                                    height = sc.nextInt();
                                    if (height <= 50) {
                                        count++;
                                    }
                                }
                            } while (count < 3);
                            System.out.println("Please enter owner of market");
                            sc.nextLine();
                            owner = sc.nextLine();
                            System.out.println("Please enter market's open time");
                            openTime = sc.nextLine();
                            System.out.println("Please enter market's close time");
                            closeTime = sc.nextLine();
                            Market tempMarket = new Market(position, length, height, 4, owner, openTime, closeTime);
                            side2Buildings.add(tempMarket);
                            control = makeStreet(side2Buildings, tempMarket, side2buildingNumber);
                            if (control) {
                                side2buildingNumber++;
                                totalRemainingLength2 -= length;
                                drawStreet(streetSide2List, side2Buildings, streetLength, side2buildingNumber-1);
                            }
                        }
                    }
                } else {
                    int intChoice;
                    System.out.println("Which side dou you want to delete?");
                    do {

                        System.out.println("1 or 2?");
                        while (!sc.hasNextInt()) {
                            System.out.println("Please enter a valid integer");
                            sc.next();
                        }
                        intChoice = sc.nextInt();
                    } while (intChoice <= 0 || intChoice > 2);

                    if (intChoice == 1) {

                        int choice2 = 0;
                        System.out.println("Which building do you want to delete?");
                        for (int i = 0; i < side1buildingNumber; i++) {

                            if (side1Buildings.get(i).getType() == 1) {

                                System.out.println(i + "." + "House");
                            }
                            if (side1Buildings.get(i).getType() == 2) {

                                System.out.println(i + "." + "Office");
                            }
                            if (side1Buildings.get(i).getType() == 3) {

                                System.out.println(i + "." + "Playground");
                            }
                            if (side1Buildings.get(i).getType() == 4) {

                                System.out.println(i + "." + "Market");
                            }
                            do {

                                System.out.println("Choice one!");
                                while (!sc.hasNextInt()) {
                                    System.out.println("Please enter a valid integer");
                                    sc.next();
                                }
                                choice2 = sc.nextInt();
                            } while (choice2 <= 0 || choice2 > side1buildingNumber);
                        }
                        deleteBuilding(streetSide1List, side1Buildings.get(choice2));
                    }

                    if (intChoice == 2) {

                        int choice2 = 0;
                        System.out.println("Which building do you want to delete?");
                        for (int i = 0; i < side2buildingNumber; i++) {

                            if (side2Buildings.get(i).getType() == 1) {

                                System.out.println(i + "." + "House");
                            }
                            if (side2Buildings.get(i).getType() == 2) {

                                System.out.println(i + "." + "Office");
                            }
                            if (side2Buildings.get(i).getType() == 3) {

                                System.out.println(i + "." + "Playground");
                            }
                            if (side2Buildings.get(i).getType() == 4) {

                                System.out.println(i + "." + "Market");
                            }
                            do {

                                System.out.println("Choice one!");
                                while (!sc.hasNextInt()) {
                                    System.out.println("Please enter a valid integer");
                                    sc.next();
                                }
                                choice2 = sc.nextInt();
                            } while (choice2 <= 0 || choice2 > side2buildingNumber);
                        }
                        deleteBuilding(streetSide2List, side2Buildings.get(choice2));
                    }
                }
            } else { //for viewing part
                int intChoice;
                do {
                    System.out.println("1)Display the total remaining length of lands on the street");
                    System.out.println("2)Display the list of buildings on the street.");
                    System.out.println("3)Display the the number and ratio of length of playgrounds in the street");
                    System.out.println("4)Calculate the total length of street occupied by the markets, houses or offices");
                    System.out.println("5)Display the skyline silhouette of the street (Please see the figure below)");
                    count++;
                    if (count > 0) {
                        System.out.println("You entered wrong number.Please enter a valid number.");
                    }
                    while (!sc.hasNextInt()) {
                        System.out.println("Please enter a valid integer");
                        sc.next();
                    }
                    intChoice = sc.nextInt();
                } while (intChoice <= 0 || intChoice > 5);

                if (intChoice == 1) { //calculates remaining lands for both sides

                    System.out.println("For side 1 remaining length of lands on the street");
                    System.out.println(totalRemainingLength1);
                    System.out.println("For side 2 remaining length of lands on the street");
                    System.out.println(totalRemainingLength2);
                }

                if (intChoice == 2) { //print list of buildings

                    int countOfMarkets = 0,
                            countOfHouses = 0,
                            countOfOffices = 0;
                    System.out.println("List of buildings on two sides:");
                    for (int i = 0; i < side1buildingNumber; i++) {

                        if (side1Buildings.get(i).getType() == 1) {
                            countOfHouses++;
                        }
                        if (side1Buildings.get(i).getType() == 2) {
                            countOfOffices++;
                        }
                        if (side1Buildings.get(i).getType() == 4) {
                            countOfMarkets++;
                        }
                    }
                    for (int i = 0; i < side2buildingNumber; i++) {

                        if (side2Buildings.get(i).getType() == 1) {
                            countOfHouses++;
                        }
                        if (side2Buildings.get(i).getType() == 2) {
                            countOfOffices++;
                        }
                        if (side2Buildings.get(i).getType() == 4) {
                            countOfMarkets++;
                        }
                    }
                    System.out.println("Total Houses: " + countOfHouses);
                    System.out.println("Total Offices: " + countOfOffices);
                    System.out.println("Total Markets: " + countOfMarkets);
                }

                if (intChoice == 3) { //prints about playgrounds

                    System.out.println("For 2 sides number and ratio of length of playgrounds in the street:");
                    int totalPlaygroundNumber = 0,
                            totalLengthOfPlayground = 0;
                    for (int i = 0; i < side1buildingNumber; i++) {

                        if (side1Buildings.get(i).getType() == 3) {
                            totalPlaygroundNumber++;
                            totalLengthOfPlayground += side1Buildings.get(i).getLength();
                        }
                    }
                    for (int i = 0; i < side2buildingNumber; i++) {

                        if (side2Buildings.get(i).getType() == 3) {
                            totalPlaygroundNumber++;
                            totalLengthOfPlayground += side2Buildings.get(i).getLength();
                        }
                    }
                    System.out.println("Number: " + totalPlaygroundNumber);
                    System.out.println("Ratio: " + (double) totalLengthOfPlayground / (2*streetLength));

                }

                if (intChoice == 4) {

                    int totalLengthOfBuildings = 0;
                    for (int i = 0; i < side1buildingNumber; i++) {

                        if (side1Buildings.get(i).getType() != 3)
                            totalLengthOfBuildings += side1Buildings.get(i).getLength();
                    }
                    for (int i = 0; i < side2buildingNumber; i++) {

                        if (side2Buildings.get(i).getType() != 3) {
                            totalLengthOfBuildings += side2Buildings.get(i).getLength();
                        }
                    }
                    System.out.println("For 2 sides total length of houses,offices and markets in the street: " + totalLengthOfBuildings);
                }

                if (intChoice == 5){

                    for (int i=51;i>=0;i--){

                        for (int j=0;j<=streetLength-1;j++){

                            System.out.print(streetSide1List.get(j).get(i));
                        }
                    }
                }
            }
            System.out.println("Do you want to continue?If you want to continue press 0");
            loopValue=sc.nextInt();
            count=0;
        }while (loopValue==0);
    }
    public static boolean makeStreet (LinkedList<Building> building, Building temp, int buildingNumber){ //looks building if it can be replaced to street

        int buildingStartPosition,
        buildingTotalLength;

        if (buildingNumber!=0){
            for (int i = 0; i < buildingNumber; i++) {
                buildingStartPosition = building.get(i).getPosition();
                buildingTotalLength = building.get(i).getPosition() + building.get(i).getLength();
                if ((temp.getPosition() >= buildingStartPosition && temp.getPosition() <= buildingTotalLength)
                        || (temp.getLength() >= buildingStartPosition && temp.getLength() <= buildingTotalLength))

                    return false;
            }
        }
        return true;
    }

    public static void drawStreet (LinkedList<List<Character>> street, LinkedList<Building> building, int streetLength, int buildingCount){ // if building can be replaceable on street prints it on street

        for (int i=51;i>=0;i--){

            for (int j=streetLength;j>=0;j--){

                if (j> building.get(buildingCount).getPosition() && j<= (building.get(buildingCount).getLength()+ building.get(buildingCount).getPosition()) && i==building.get(buildingCount).getHeight()){
                    street.get(j).add(i,'-');

                }
                else if((j== building.get(buildingCount).getPosition() || j== building.get(buildingCount).getLength()+ building.get(buildingCount).getPosition()) && i< building.get(buildingCount).getHeight()){
                    street.get(j).add(i,'|');

                }
                else if (j> building.get(buildingCount).getPosition() && j< (building.get(buildingCount).getLength()+ building.get(buildingCount).getPosition()) && i< building.get(buildingCount).getHeight()) {
                    street.get(j).add(i, ' ');

                }
            }
            street.get(streetLength-1).add(i,'\n');
        }

        System.out.print('\n');
    }

    public static void deleteBuilding (LinkedList<List<Character>> street, Building building){ // delete building from street

        for (int i= building.getHeight();i>=0;i--){

            for (int j= building.getLength()+ building.getPosition();j>= building.getPosition();j--){

                street.get(j).set(i,' ');
            }
        }

    }

    public static void driverFunction () { //driver function makes objects and processes automatically

        int streetLength = 120,
                side1TotalRemainingSpace=streetLength,
                side2TotalRemainingSpace=streetLength,
                side1buildingNumber = 0,
                side2buildingNumber = 0;
        LinkedList<Building> side1Buildings = new LinkedList<>(), //allocating both sides building list
                side2Buildings = new LinkedList<>();

        LinkedList<List<Character>> streetSide1List = new LinkedList<List<Character>>(), //total height=50
                streetSide2List = new LinkedList<List<Character>>();
        LinkedList<Character> side1BuildingsOneDimension = new LinkedList<>(),
                side2BuildingsOneDimension = new LinkedList<>();

        for (int j = 0; j <= 52; j++) {
            side1BuildingsOneDimension.add(' ');
            side2BuildingsOneDimension.add(' ');
        }
        for (int i=0;i<=streetLength;i++) {
            streetSide1List.add(side1BuildingsOneDimension);
            streetSide2List.add(side1BuildingsOneDimension);
        }


        side1Buildings.add(new House(0,10,20,1,3,"blue","alp")); //creates buildings and draw them
        side1buildingNumber++;
        side1TotalRemainingSpace-= side1Buildings.get(side1buildingNumber - 1).getLength();
        drawStreet(streetSide1List, side1Buildings,streetLength,side1buildingNumber-1);

        side1Buildings.add(new Office(10, 20, 30, 2, "cook", "alp"));
        side1buildingNumber++;
        side1TotalRemainingSpace-= side1Buildings.get(side1buildingNumber - 1).getLength();
        drawStreet(streetSide1List, side1Buildings,streetLength,side1buildingNumber-1);

        side1Buildings.add(new Playground(35, 10, 20, 3));
        side1buildingNumber++;
        side1TotalRemainingSpace-= side1Buildings.get(side1buildingNumber - 1).getLength();
        drawStreet(streetSide1List,side1Buildings,streetLength,side1buildingNumber-1);

        side1Buildings.add(new Market(50, 5, 33, 4, "alp", "8.00", "17.00"));
        side1buildingNumber++;
        side1TotalRemainingSpace-= side1Buildings.get(side1buildingNumber - 1).getLength();
        drawStreet(streetSide1List,side1Buildings,streetLength,side1buildingNumber-1);

        side1Buildings.add(new House(60, 10, 20, 1, 4, "red", "alp"));
        side1buildingNumber++;
        side1TotalRemainingSpace-= side1Buildings.get(side1buildingNumber - 1).getLength();
        drawStreet(streetSide1List,side1Buildings,streetLength,side1buildingNumber-1);

        side1Buildings.add(new House(70, 5, 23, 1, 3, "gray", "alp"));
        side1buildingNumber++;
        side1TotalRemainingSpace-= side1Buildings.get(side1buildingNumber - 1).getLength();
        drawStreet(streetSide1List,side1Buildings,streetLength,side1buildingNumber-1);

        side1Buildings.add(new Market(80, 7, 42, 4, "alp", "8.00", "17.00"));
        side1buildingNumber++;
        side1TotalRemainingSpace-= side1Buildings.get(side1buildingNumber - 1).getLength();
        drawStreet(streetSide1List,side1Buildings,streetLength,side1buildingNumber-1);

        side2Buildings.add(new House(0, 13, 20, 1, 3, "blue", "alp"));
        side2buildingNumber++;
        side2TotalRemainingSpace-= side2Buildings.get(side2buildingNumber - 1).getLength();
        drawStreet(streetSide2List,side2Buildings,streetLength,side2buildingNumber-1);

        side2Buildings.add(new Office(15, 20, 30, 2, "cook", "alp"));
        side2buildingNumber++;
        side2TotalRemainingSpace-= side2Buildings.get(side2buildingNumber - 1).getLength();
        drawStreet(streetSide2List,side2Buildings,streetLength,side2buildingNumber-1);

        side2Buildings.add(new Playground(40, 10, 20, 3));
        side2buildingNumber++;
        side2TotalRemainingSpace-= side2Buildings.get(side2buildingNumber - 1).getLength();
        drawStreet(streetSide2List,side2Buildings,streetLength,side2buildingNumber-1);

        side2Buildings.add(new Market(53, 5, 33, 4, "alp", "8.00", "17.00"));
        side2buildingNumber++;
        side2TotalRemainingSpace-= side2Buildings.get(side2buildingNumber - 1).getLength();
        drawStreet(streetSide2List,side2Buildings,streetLength,side2buildingNumber-1);

        side2Buildings.add(new House(60, 10, 20, 1, 4, "red", "alp"));
        side2buildingNumber++;
        side2TotalRemainingSpace-= side2Buildings.get(side2buildingNumber - 1).getLength();
        drawStreet(streetSide2List,side2Buildings,streetLength,side2buildingNumber-1);

        side2Buildings.add(new House(75, 5, 23, 1, 3, "gray", "alp"));
        side2buildingNumber++;
        side2TotalRemainingSpace-= side2Buildings.get(side2buildingNumber - 1).getLength();
        drawStreet(streetSide2List,side2Buildings,streetLength,side2buildingNumber-1);

        side2Buildings.add(new Market(80, 7, 42, 4, "alp", "8.00", "17.00"));
        side2buildingNumber++;
        side2TotalRemainingSpace-= side2Buildings.get(side2buildingNumber - 1).getLength();
        drawStreet(streetSide2List,side2Buildings,streetLength,side2buildingNumber-1);

        side2Buildings.add(new Playground(90, 3, 20, 3));
        side2buildingNumber++;
        side2TotalRemainingSpace-= side2Buildings.get(side2buildingNumber - 1).getLength();
        drawStreet(streetSide2List,side2Buildings,streetLength,side2buildingNumber-1);


        System.out.println("1)Display the total remaining length of lands on the street"); //makes view processes
        System.out.println("For side 1 remaining length of lands on the street");
        System.out.println(side1TotalRemainingSpace);
        System.out.println("For side 2 remaining length of lands on the street");
        System.out.println(side2TotalRemainingSpace);

        System.out.println("2)Display the list of buildings on the street.");
        int countOfMarkets = 0,
                countOfHouses = 0,
                countOfOffices = 0;
        System.out.println("List of buildings on two sides:");
        for (int i = 0; i < side1buildingNumber; i++) {

            if (side1Buildings.get(i).getType() == 1) {
                countOfHouses++;
            }
            if (side1Buildings.get(i).getType() == 2) {
                countOfOffices++;
            }
            if (side1Buildings.get(i).getType() == 4) {
                countOfMarkets++;
            }
        }
        for (int i = 0; i < side2buildingNumber; i++) {

            if (side2Buildings.get(i).getType() == 1) {
                countOfHouses++;
            }
            if (side2Buildings.get(i).getType() == 2) {
                countOfOffices++;
            }
            if (side2Buildings.get(i).getType() == 4) {
                countOfMarkets++;
            }
        }
        System.out.println("Total Houses: " + countOfHouses);
        System.out.println("Total Offices: " + countOfOffices);
        System.out.println("Total Markets: " + countOfMarkets);

        System.out.println("3)Display the the number and ratio of length of playgrounds in the street");
        System.out.println("For 2 sides number and ratio of length of playgrounds in the street:");
        int totalPlaygroundNumber = 0,
                totalLengthOfPlayground = 0;
        for (int i = 0; i < side1buildingNumber; i++) {

            if (side1Buildings.get(i).getType() == 3) {
                totalPlaygroundNumber++;
                totalLengthOfPlayground += side1Buildings.get(i).getLength();
            }
        }
        for (int i = 0; i < side2buildingNumber; i++) {

            if (side2Buildings.get(i).getType() == 3) {
                totalPlaygroundNumber++;
                totalLengthOfPlayground += side2Buildings.get(i).getLength();
            }
        }
        System.out.println("Number: " + totalPlaygroundNumber);
        System.out.println("Ratio: " + (double) totalLengthOfPlayground / (2*streetLength));
        System.out.println("4)Calculate the total length of street occupied by the markets, houses or offices");
        int totalLengthOfBuildings = 0;
        for (int i = 0; i < side1buildingNumber; i++) {

            if (side1Buildings.get(i).getType() != 3)
                totalLengthOfBuildings += side1Buildings.get(i).getLength();
        }
        for (int i = 0; i < side2buildingNumber; i++) {

            if (side2Buildings.get(i).getType() != 3) {
                totalLengthOfBuildings += side2Buildings.get(i).getLength();
            }
        }
        System.out.println("For 2 sides total length of houses,offices and markets in the street: " + totalLengthOfBuildings); // prints silhouette

        System.out.println("5)Display the skyline silhouette of the street");
        System.out.println("5)Cannot made this part");



    }
}








