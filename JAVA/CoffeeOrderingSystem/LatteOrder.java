 /**
 *The LatteOrder class respresents an order of lattes. 
 */
public class LatteOrder{
    private Latte[] order; //array of base type Latte named "order"
    private int numLattes; //how many lattes in order
     
    /**
     * Creates a defeault constructor with a single latte in the order.  
     */
    public LatteOrder(){ //default constructor with one latte in order
        order = new Latte[1];
        numLattes = 0;
    }

     /**
     * Creates an overloaded constructor with a specific size for the order.
     * 
     * @param size The size for the order.
     */
    public LatteOrder(int size){ //overloaded constructor
        order = new Latte[size]; // size of order array(number of lattes)
        numLattes = 0;
    }
    
     /**
     * Adds a latte to the order.
     *
     * @param latte The latte to add to the order.
     * @return 1 if successfully added, -1 if the order is full.
     * @see Latte The Latte class contains information on latte attributes.
     */
    public int addLatte(Latte latte){  // adds latte to order
        if (numLattes < order.length){ //check if current number of lattes less than total capacity
            order[numLattes] = latte;
            numLattes++; //adds a latte to order 
            return 1; // succesfully added or order is full -1
        }
        else{
            return -1;
        }
    }

     /**
     * Caculates the total cost of the order with all elements/add ons.
     * 
     * @return The total cost of the order.
     */
    public double calcTotal(){ // calculate the order total 
        double totalCost = 0.0;
        for ( int i = 0; i < numLattes; i++){
            totalCost += order[i].calcCost(); //calculate cost of each latte object in order array
        }
        return totalCost;
    }

     /**
     * Converts the order information to a string.
     * 
     * @return The string form of the order.
     */
    public String toString(){  // string for entire order
        
        double totalCost = calcTotal();
        String orderSummary = "Order:\n";
        orderSummary += "Total Cost: $" + totalCost +"\n";

        for (int i = 0; i < numLattes; i++){ // Loop through each latte in the order and update orderSumm for each attribute
            orderSummary += "Latte " + i + "\n";
            orderSummary += "   Cost: $" + order[i].calcCost() + "\n"; // append order details within order array using get methods
            orderSummary += "   Size: " + order[i].getSize() + "\n";
            orderSummary += "   Pumpkin Sauce Pumps: " + order[i].getPumpkinSaucePumps() + "\n";
            orderSummary += "   Milk Type: " + order[i].getMilkType() + "\n";
            orderSummary += "   Espresso Shots: " + order[i].getEspressoShots() + "\n";
            orderSummary += "   Whipped Cream: " + (order[i].hasWhippedCream() ? "true" : "false")+ "\n";
            
        }
        
        return orderSummary;
    }

}