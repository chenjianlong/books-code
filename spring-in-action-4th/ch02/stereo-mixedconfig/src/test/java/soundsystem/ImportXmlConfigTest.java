package soundsystem;

import static org.junit.Assert.assertEquals;

import org.junit.Rule;
import org.junit.Test;
import org.junit.contrib.java.lang.system.SystemOutRule;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.test.context.ContextConfiguration;
import org.springframework.test.context.junit4.SpringJUnit4ClassRunner;

@RunWith(SpringJUnit4ClassRunner.class)
@ContextConfiguration(classes=SoundSystemConfig.class)
public class ImportXmlConfigTest {

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
                        "-Track: Fixing a Hole" + ls,
                log.getLog());
    }

}
