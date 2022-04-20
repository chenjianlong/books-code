package com.soundsystem;

import org.springframework.beans.factory.annotation.Value;

public class BlankDisc {

    private final String title;
    private final String artist;

    public BlankDisc(
            @Value("${disc.title}") String title,
            @Value("${disc.artist}") String artist) {
        this.title = title;
        this.artist = artist;
    }

    public String getTitle() {
        return title;
    }

    public String getArtist() {
        return artist;
    }

}
