package com.springinaction.knights;

import org.springframework.context.annotation.AnnotationConfigApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class KnightMain {
    public static void main(String[] args) {
        DamselRescuingKnight knight1 = new DamselRescuingKnight();
        knight1.embarkOnQuest();

        BraveKnight knight2 = new BraveKnight(new RescueDamselQuest());
        knight2.embarkOnQuest();

        AnnotationConfigApplicationContext context1 = new AnnotationConfigApplicationContext(
                com.springinaction.knights.config.KnightConfig.class);
        Knight knight3 = context1.getBean(Knight.class);
        knight3.embarkOnQuest();
        context1.close();

        ClassPathXmlApplicationContext context2 =
                new ClassPathXmlApplicationContext("META-INF/spring/knights.xml");
        Knight knight4 = context2.getBean(Knight.class);
        knight4.embarkOnQuest();
        context2.close();

        ClassPathXmlApplicationContext context3 =
                new ClassPathXmlApplicationContext("META-INF/spring/minstrel.xml");
        Knight knight5 = context3.getBean(Knight.class);
        knight5.embarkOnQuest();
        context3.close();
    }
}
