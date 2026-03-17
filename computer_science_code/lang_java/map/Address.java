public class Address {

    final private int streetNumber;
    final private String streetName;
    final private String cityName;
    final private String state;
    final private int zipCode;

    //constructor for Address class
    public Address(int streetNumber, String streetName,String cityName,String state, int zipCode)
    {
    this.streetNumber = streetNumber;
    this.streetName = streetName;
    this.cityName = cityName;
    this.state = state;
    this.zipCode = zipCode;
    }

    //gets the address as a string
    @Override
    public String toString() {
        return "Address ==>  " + streetNumber + " " + streetName + " " + cityName + " " + state + " " + zipCode;
    }
}
