package concert;

import org.junit.Rule;
import org.junit.Test;
import org.junit.contrib.java.lang.system.SystemOutRule;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

import static org.junit.Assert.assertEquals;

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration("classpath:concert.xml")
public class ConcertTest {
    @Rule
    public final SystemOutRule log = new SystemOutRule().enableLog();

    @Autowired
    private Performance performance;

    @Test
    public void testPerformance() {
        performance.perform();
        final String ls = System.lineSeparator();
        assertEquals("Silencing cell phones" + ls +
                "Taking seats" + ls +
                "Piano Solo" + ls +
                "CLAP CLAP CLAP!!!" + ls, log.getLog());
    }
}
