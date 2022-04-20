package kitchen;

import org.springframework.beans.factory.annotation.Qualifier;
import org.springframework.context.annotation.Primary;
import org.springframework.stereotype.Component;

@Component
@Primary
@Cold
@Fruity
public class Popsicle implements Dessert {
}
