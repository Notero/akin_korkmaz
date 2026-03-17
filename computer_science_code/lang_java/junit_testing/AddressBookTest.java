import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

public class AddressBookTest {

    AddressBook ledger;
    String fullName = "akin korkmaz";
    Address address = new Address(1,"test name","test city","test state",2);



    @BeforeEach
    void AddressBookinit(){
        ledger = new AddressBook();
    }

    @Test
    public void putAddressTest(){
        Assertions.assertEquals(1,ledger.putAddress(fullName,address));
    }

    @Test
    public void removeAddressTest(){
        ledger.putAddress(fullName,address);
        Assertions.assertEquals(1,ledger.removeAddress(fullName));
    }

    @Test
    public void PutandRemoveAdressTest(){
        Assertions.assertEquals(1,ledger.putAddress(fullName,address));
        Assertions.assertEquals(1,ledger.removeAddress(fullName));
    }

    @Test
    public void findAddressTest(){
        ledger.putAddress(fullName,address);
        Assertions.assertTrue(ledger.findAddress(fullName));
    }
    @Test
    public void countAdressTest(){
        ledger.putAddress(fullName,address);
        Assertions.assertEquals(1,ledger.getCount());
    }
}
