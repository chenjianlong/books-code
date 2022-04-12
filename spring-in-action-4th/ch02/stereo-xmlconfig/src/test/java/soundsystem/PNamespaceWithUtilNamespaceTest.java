package soundsystem;

import static org.junit.Assert.*;

import org.junit.Rule;
import org.junit.Test;
import org.junit.contrib.java.lang.system.StandardOutputStreamLog;
import org.junit.contrib.java.lang.system.SystemOutRule;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration
public class PNamespaceWithUtilNamespaceTest {

    @Rule
    public final SystemOutRule log = new SystemOutRule().enableLog();

    @Autowired
    private MediaPlayer player;

    @Test
    public void play() {
        player.play();
        String ls = System.lineSeparator();
        assertEquals(
                "Playing Sgt. Pepper's Lonely Hearts Club Band by The Beatles" + ls +
                        "-Track: Sgt. Pepper's Lonely Hearts Club Band" + ls +
                        "-Track: With a Little Help from My Friends" + ls +
                        "-Track: Lucy in the Sky with Diamonds" + ls +
                        "-Track: Getting Better" + ls +
                        "-Track: Fixing a Hole" + ls +
                        "-Track: She's Leaving Home" + ls +
                        "-Track: Being for the Benefit of Mr. Kite!" + ls +
                        "-Track: Within You Without You" + ls +
                        "-Track: When I'm Sixty-Four" + ls +
                        "-Track: Lovely Rita" + ls +
                        "-Track: Good Morning Good Morning" + ls +
                        "-Track: Sgt. Pepper's Lonely Hearts Club Band (Reprise)" + ls +
                        "-Track: A Day in the Life" + ls,
                log.getLog());
    }

}
