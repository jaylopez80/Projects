/**
 * Latte class to represent coffee drink with different attributes
 * @author Jonathan Lopez
 * @version 1.2
 * @see LatteOrder To expand on how lattes are used in orders.
 */

public class Latte{
    private String size; //member variables for a "latte"
    private String milkType;
    private int espressoShots;
    private int pumpkinSaucePumps;
    private boolean whippedCream;

     /**
     * Default constructor for a default latte
     */
    public Latte() {  //creates default constuctor for a default latte
        size = "grande";
        pumpkinSaucePumps = 4;
        milkType = "2%";
        espressoShots = 2;
        whippedCream = true;
    }

    /**
     * Creates an overloaded constructor for a custom latte.
     * @param size The size of the latte
     * @param pumpkinSaucePumps The number of pumpkin pumps.
     * @param milkType The type of milk used.
     * @param espressoShots The number of espresso shots used.
     * @param whippedCream Does the latte include whipped cream.
     */
    public Latte(String size, int pumpkinSaucePumps, String milkType, int espressoShots, boolean whippedCream){//overloaded constructor
        this.size = size;  //assigns latte attribute paramaters to values for latte object
        this.pumpkinSaucePumps = pumpkinSaucePumps;
        this.milkType = milkType;
        this.espressoShots = espressoShots;
        this.whippedCream = whippedCream;
    }

    /**
     * Create a copy for an existing latte.
     * 
     * @param newLatte The latte to be copied.
     */
    public Latte(Latte newLatte){ // copy constructor of existing latte
        this.size = newLatte.size;
        this.pumpkinSaucePumps = newLatte.pumpkinSaucePumps;
        this.milkType = newLatte.milkType;
        this.espressoShots = newLatte.espressoShots;
        this.whippedCream = newLatte.whippedCream;
    }

     /**
      * Gets the size of latte drink.
     * @return The size of latte.
     */
    public String getSize(){ //Accessors or getters for member vars
        return size;
    }

     /**
     * Gets the milk type.
     * @return The milk type for latte.
     */
    public String getMilkType(){
        return milkType;
    }

     /**
     * Gets the number of pumpkin sauce pumps (PSP).
     * @return The number of PSPs.
     */
    public int getPumpkinSaucePumps(){
        return pumpkinSaucePumps;
    }

     /**
     * Gets the number of espresso shots.
     * @return The number of espresso shots.
     */
    public int getEspressoShots(){
        return espressoShots;
    }

     /**
     * Checks if latte includes whipped cream in it.
     * @return true for including whipped cream, false without.
     */
    public boolean hasWhippedCream(){
        return whippedCream;
    }

     /**
     * Calculats the cost of the latte.
     * 
     * @return The cost of the latte.
     */
    public double calcCost(){ //method to calculate latte cost (size cost and toppings)
        double cost = 0.0;

        switch(size){
            case "tall":
                cost += 2.00;
                break;
            case "grande":
                cost += 2.50;
                break;
            case "venti":
                cost += 3.00;
                break;
        }
        cost += 0.25 * pumpkinSaucePumps;
        cost += 1.00 * espressoShots;

        if (milkType.equals("oat") || milkType.equals("almond")){ //account for non dairy option and whippedcream choice
            cost += .75;
        }
        if (whippedCream){
            cost += .50;
        }
        return cost;
    }

     /**
     * Converts the latte attributes/info to a string.
     * @return The string elements/representation of the latte.
     */
    public String toString(){ // takes individual latte info and converts to string
        return "Size: " + size + ", Pumpkin Sauce Pumps: " + pumpkinSaucePumps + ", Milk Type: " + milkType + ", espessoShots: " + espressoShots
                + ", Whipped Cream: " + whippedCream + ", Cost: $" + calcCost();
    }
     /**
     * Checks if two lattes are equal size and add-ons
     * @param newLatte The latte to be compared with.
     * @return True if the lattes are equal otherwise false.
     */
    public boolean equals(Latte newLatte){ // checks  if two lattes are equal based on size and toppings
        return this.size.equals(newLatte.size) && 
            this.pumpkinSaucePumps == newLatte.pumpkinSaucePumps && 
            this.milkType.equals(newLatte.milkType) &&
            this.espressoShots == newLatte.espressoShots && 
            this.whippedCream == newLatte.whippedCream;
    }
}