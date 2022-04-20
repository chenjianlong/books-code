package kitchen;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import static org.junit.Assert.assertNotNull;

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(classes= DessertConfig.class)
public class DessertTest {
    @Autowired
    @Cold
    @Fruity
    private Dessert dessert;

    @Test
    public void dessertShouldNotBeNull() {
        assertNotNull(dessert);
    }
}
